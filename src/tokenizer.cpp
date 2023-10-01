#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <variant>

#include "tokenizer.hpp"

std::vector<Token> Tokenizer::tokenize()
{
    std::vector<Token> tokens;
    std::ifstream file(_fileName);
    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << _fileName << std::endl;
        return tokens; // return empty vector
    }

    while (file.good())
    {
        Token token = getNextToken(file);
        if (token.type == END_OF_FILE)
            break;
        tokens.push_back(token);
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
        if (std::isspace(c))
        { // If a whitespace character is encountered, then we consider the token as complete
            if (!word.empty())
                break; // only break if we've started forming a word
            continue;  // ignore leading whitespace
        }

        if (c == '{' || c == '}' || c == ';')
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

    token.type = INVALID;
    token.value = word;
    return token;
}

bool Tokenizer::isKeyword(const std::string& word, TokenType& type) {
    static std::map<std::string, TokenType> keywords {
        {"meta", META},
        {"def", DEF},
        {"frame", FRAME},
    };
    
    auto it = keywords.find(word);
    if (it != keywords.end()) {
        type = it->second;
        return true;
    }
    return false;
}