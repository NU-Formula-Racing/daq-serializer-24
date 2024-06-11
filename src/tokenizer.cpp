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
#define SPIFFS LITTLEFS
#include <LittleFS.h>
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

std::vector<Token> Tokenizer::tokenizeFile()
{
    std::string fileContents = openFile(_source);
    std::vector<Token> tokens =  buildTokenList(fileContents);

    return tokens;
}

std::vector<Token> Tokenizer::tokenizeContent()
{
    return buildTokenList(_source);
}

std::vector<Token> Tokenizer::buildTokenList(const std::string &file)
{
    // std::cout << "Building token list..." << std::endl;
    std::vector<Token> tokens;
    char c;
    int index = 0;

    while (index < file.size())
    {
        Token currentToken;
        std::string word;
        while (index < file.size())
        {
            c = file[index];
            index++;

            // check for comments, that start with #
            if (c == '#')
            {
                if (!word.empty())
                {
                    index--;
                    break;
                }

                while (index < file.size() && c != '\n')
                {
                    c = file[index++];
                }
                continue;
            }

            if (std::isspace(c))
            {
                if (!word.empty())
                {
                    break;
                }
                continue;
            }

            if (c == '{' || c == '}' || c == ';' || c == '(' || c == ')' || c == ':')
            {
                if (!word.empty())
                {
                    index--;
                    break;
                }

                word = c;
                break;
            }

            word += c;
        }

        if (word.empty())
        {
            currentToken.type = TOKEN_END_OF_FILE;
            currentToken.value = "EOF";
            tokens.emplace_back(currentToken);
            continue;
        }

        if (isKeyword(word, currentToken.type) ||
            isSymbol(word, currentToken.type) ||
            isLiteral(word, currentToken.type))
        {
            if (currentToken.type == TOKEN_STRING_LITERAL)
            {
                // remove the quotes from the string
                currentToken.value = word.substr(1, word.size() - 2);
                tokens.push_back(currentToken);
                continue;
            }

            currentToken.value = word;
            tokens.push_back(currentToken);
            continue;
        }

        // if it is not a literal, then we are going to assume that it is an identifier, given that it's a valid name
        if (isValidIdentifier(word))
        {
            currentToken.type = TOKEN_IDENTIFIER;
            currentToken.value = word;
            tokens.push_back(currentToken);
            continue;
        }

        currentToken.type = TOKEN_INVALID;
        currentToken.value = word;
        tokens.push_back(currentToken);
    }

    return tokens;
}

std::string Tokenizer::openFile(std::string filename)
{
#ifdef USE_LITTLEFS_ESP32
    if (!SPIFFS.begin(true))
    {
        std::cout << "Error mounting SPIFFS" << std::endl;
        std::stringstream err;
        err << "Error mounting SPIFFS" << std::endl;
        return err;
    }

    // also modify the _source for spiffs mounting, which is under the /spiffs directory
    filename = "/" + filename;
#endif

#ifdef USE_LITTLEFS_TEENSY
    if (!g_littleFS.begin(chipSelect))
    {
        std::cout << "Error mounting LITTLEFS" << std::endl;
        std::stringstream err;
        err << "Error mounting LITTLEFS" << std::endl;
        return err.str();
    }

    g_littleFS.quickFormat();

#endif

#ifdef USE_LITTLEFS_ESP32
    fs::File driveFile = SPIFFS.open(filename.c_str(), "r");
    if (!driveFile.available())
    {
        std::stringstream err;
        err << "Error opening file: " << filename << std::endl;
        std::cout << err.str();
        return err.str();
    }

    // put the file content into a stringstream
    std::string file = driveFile.readString().c_str();
    driveFile.close();

#elif defined(USE_LITTLEFS_TEENSY)
    File f = g_littleFS.open(filename.c_str(), FILE_READ);
    if (!f)
    {
        std::cout << "Error opening file: " << filename << std::endl;
        std::stringstream err;
        err << "Error opening file: " << filename << std::endl;
        return err.str();
    }
    std::string file = f.readString().c_str();
#else
    std::ifstream fileStream(filename);
    if (!fileStream.is_open())
    {
        std::cout << "Error opening file: " << filename << std::endl;
        std::stringstream err;
        err << "Error opening file: " << filename << std::endl;
        return err.str();
    }

    std::string file;
    for (std::string line; std::getline(fileStream, line);)
    {
        file += line + "\n";
    }
#endif
    // std::cout << "File content: " << file << std::endl;
    return file;
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
    if (std::regex_match(word, std::regex("^\".*\"$")) || std::regex_match(word, std::regex("^'.*'$")))
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
