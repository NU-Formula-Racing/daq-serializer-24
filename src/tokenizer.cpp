#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <variant>
#include <sstream>
#include <exception>
#include <regex>

#include "tokenizer.hpp"

#ifdef ARDUINO_ARCH_ESP32
#define USE_LITTLEFS_ESP32
#include <FS.h>
#ifdef USE_LITTLEFS_ESP32
#define SPIFFS LittleFS
#include <LITTLEFS.h>
#else
#include <SPIFFS.h>
#endif
#endif

#if defined(ARDUINO_TEENSY40) || defined(ARDUINO_TEENSY41)
#define USE_LITTLEFS_TEENSY
#include <LITTLEFS.h>
LittleFS_Program g_littleFS;
#define chipSelect 6

#endif

using namespace daqser::impl;

std::vector<Token> Tokenizer::tokenize()
{
#ifdef USE_LITTLEFS_ESP32
    if (!SPIFFS.begin(true))
    {
        std::cout << "Error mounting SPIFFS" << std::endl;
        return {};
    }

    // also modify the _fileName for spiffs mounting, which is under the /spiffs directory
    _fileName = "/spiffs/" + _fileName;
#endif

#ifdef USE_LITTLEFS_TEENSY
    if (!g_littleFS.begin(chipSelect))
    {
        std::cout << "Error mounting LITTLEFS" << std::endl;
        return {};
    }

    g_littleFS.quickFormat();

#endif

    std::vector<Token> tokens;
#ifndef USE_LITTLEFS_TEENSY
    std::ifstream file(_fileName);
    if (!file.is_open())
    {
        std::stringstream err;
        err << "Error opening file: " << _fileName << std::endl;
        // throw std::invalid_argument(err.str());
        std::cout << err.str();
        return {};
    }
#else
    File f = g_littleFS.open(_fileName.c_str(), FILE_READ);
    if (!f)
    {
        std::cout << "Error opening file: " << _fileName << std::endl;
        return {};
    }
    std::stringstream ss;
    ss << f.readString();
    std::string fileContent = ss.str();
    std::istringstream file(fileContent);
#endif

    while (file.good())
    {
        Token token = getNextToken(file);
        tokens.push_back(token);
        if (token.type == TOKEN_END_OF_FILE)
            break;
    }

#ifndef USE_LITTLEFS_TEENSY
    file.close();
#else
    f.close();
#endif
    return tokens;
}

Token Tokenizer::getNextToken(std::istream &file)
{
    Token token;
    char c;
    std::string word;

    while (file.get(c))
    {
        if (c == '#')
        { // Handle comments
            while (file.get(c) && c != '\n')
                ; // ignore the rest of the line
            continue;
        }

        if (std::isspace(c))
        { // If a whitespace character is encountered, then we consider the token as complete
            if (!word.empty())
                break; // only break if we've started forming a word
            continue;  // ignore leading whitespace
        }

        if (c == '{' || c == '}' || c == ';' || c == '(' || c == ')' || c == ':') // code smelly
        {                                                                         // Handle symbols
            if (!word.empty())
            {
                file.unget(); // Push back the symbol to the stream to be able to read it in the next call
                break;
            }
            word.push_back(c);
            break;
        }

        word.push_back(c);
    }

    if (file.eof() && word.empty())
    {
        token.type = TOKEN_END_OF_FILE;
        token.value = "EOF";
        return token;
    }

    if (isKeyword(word, token.type) ||
        isSymbol(word, token.type) ||
        isLiteral(word, token.type))
    {
        if (token.type == TOKEN_STRING_LITERAL)
        {
            // remove the quotes from the string
            token.value = word.substr(1, word.size() - 2);
            return token;
        }

        token.value = word;
        return token;
    }

    // if it is not a literal, then we are going to assume that it is an identifier, given that it's a valid name
    if (isValidIdentifier(word))
    {
        token.type = TOKEN_IDENTIFIER;
        token.value = word;
        return token;
    }

    token.type = TOKEN_INVALID;
    token.value = word;
    return token;
}

bool Tokenizer::isKeyword(const std::string &word, TokenType &type)
{
    static std::map<std::string, TokenType> keywords{
        {"meta", TOKEN_META},
        {"def", TOKEN_DEF},
        {"frame", TOKEN_FRAME},
    };

    auto it = keywords.find(word);
    if (it != keywords.end())
    {
        type = it->second;
        return true;
    }
    return false;
}

bool Tokenizer::isSymbol(const std::string &word, TokenType &type)
{
    static std::map<std::string, TokenType> symbols{
        {"{", TOKEN_L_BRACE},
        {"}", TOKEN_R_BRACE},
        {":", TOKEN_COLON},
        {";", TOKEN_SEMICOLON},
        {"(", TOKEN_L_PARENTHESES},
        {")", TOKEN_R_PARENTHESES},
    };

    auto it = symbols.find(word);
    if (it != symbols.end())
    {
        type = it->second;
        return true;
    }
    return false;
}

bool Tokenizer::isLiteral(const std::string &word, TokenType &type)
{
    // Integer Literal
    if (std::regex_match(word, std::regex("^-?[0-9]+$")))
    {
        type = TOKEN_INT_LITERAL;
        return true;
    }

    // Float/Double Literal
    if (std::regex_match(word, std::regex("^-?[0-9]*\\.[0-9]+([eE][-+]?[0-9]+)?$")))
    {
        type = TOKEN_FLOAT_LITERAL; // or DOUBLE_LITERAL depending on your requirement
        return true;
    }

    // Boolean Literal
    if (word == "true" || word == "false")
    {
        type = TOKEN_BOOL_LITERAL;
        return true;
    }

    // String Literal
    if (std::regex_match(word, std::regex("^\".*\"$")))
    {
        type = TOKEN_STRING_LITERAL;
        return true;
    }

    // Version Literal
    if (std::regex_match(word, std::regex("^[0-9]+\\.[0-9]+\\.[0-9]+$")))
    {
        type = TOKEN_VERSION_LITERAL;
        return true;
    }

    return false;
}

bool Tokenizer::isValidIdentifier(const std::string &word)
{
    // check that all characters in the word are alphanumeric or underscore
    // the first number cannot be a digit, but it can be a period
    // the only character allowed to be a period is the first character
    // the last character cannot be a period

    if (word.empty())
    {
        return false;
    }

    if (!isalpha(word[0]) && word[0] != '_' && word[0] != '.')
    {
        return false;
    }

    for (size_t i = 1; i < word.size(); i++)
    {
        if (!isalnum(word[i]) && word[i] != '_')
        {
            return false;
        }
    }

    return true;
}
