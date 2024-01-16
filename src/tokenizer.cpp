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

std::vector<Token> Tokenizer::tokenize()
{
    std::vector<Token> tokens;
    std::ifstream file(_fileName);
    if (!file.is_open())
    {
        std::stringstream err;
        err << "Error opening file: " << _fileName << std::endl;
        throw std::invalid_argument(err.str());
    }

    while (file.good())
    {
        Token token = getNextToken(file);
        tokens.push_back(token);
        if (token.type == END_OF_FILE)
            break;
    }

    file.close();
    return tokens;
}

Token Tokenizer::getNextToken(std::ifstream &file)
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
        { // Handle symbols
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
        token.type = END_OF_FILE;
        token.value = "EOF";
        return token;
    }

    if (isKeyword(word, token.type) ||
        isSymbol(word, token.type) ||
        isLiteral(word, token.type))
    {
        token.value = word;
        return token;
    }
       
    // if it is not a literal, then we are going to assume that it is an identifier, given that it's a valid name
    if (isValidIdentifier(word))
    {
        token.type = IDENTIFIER;
        token.value = word;
        return token;
    }
    
    token.type = INVALID;
    token.value = word;
    return token;
}

bool Tokenizer::isKeyword(const std::string &word, TokenType &type)
{
    static std::map<std::string, TokenType> keywords{
        {"meta", META},
        {"def", DEF},
        {"frame", FRAME},
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
        {"{", L_BRACE},
        {"}", R_BRACE},
        {":", COLON},
        {";", SEMICOLON},
        {"(", L_PARENTHESES},
        {")", R_PARENTHESES},
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
        type = INT_LITERAL;
        return true;
    }

    // Float/Double Literal
    if (std::regex_match(word, std::regex("^-?[0-9]*\\.[0-9]+([eE][-+]?[0-9]+)?$")))
    {
        type = FLOAT_LITERAL; // or DOUBLE_LITERAL depending on your requirement
        return true;
    }

    // Boolean Literal
    if (word == "true" || word == "false")
    {
        type = BOOL_LITERAL;
        return true;
    }

    // String Literal
    if (std::regex_match(word, std::regex("^\".*\"$")))
    {
        type = STRING_LITERAL;
        return true;
    }

    // Version Literal
    if (std::regex_match(word, std::regex("^[0-9]+\\.[0-9]+\\.[0-9]+$")))
    {
        type = VERSION_LITERAL;
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
    
    if (word.empty()) {
        return false;
    }
    
    if (!isalpha(word[0]) && word[0] != '_' && word[0] != '.') {
        return false;
    }
    
    for (size_t i = 1; i < word.size(); i++) {
        if (!isalnum(word[i]) && word[i] != '_') {
            return false;
        }      
    }
    
    return true;
}
