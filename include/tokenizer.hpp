#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <variant>

enum TokenType
{
    // Inavlid
    INVALID,

    // Keywords
    META,
    DEF,
    FRAME,

    // Symbols
    L_BRACE,
    R_BRACE,
    SEMICOLON,
    END_OF_FILE, 

    // Identifiers
    DATA_TYPE,  // data type names
    IDENTIFIER, // variable names

    // Literals
    INT_LITERAL,
    FLOAT_LITERAL,
    DOUBLE_LITERAL,
    BOOL_LITERAL,
    STRING_LITERAL,
    VERSION_LITERAL,
};

struct Token
{
    TokenType type;
    std::string value;
};

class Tokenizer
{
public:
    Tokenizer() : _fileName("")
    {
        // nothing
    }

    Tokenizer(const std::string &target) : _fileName(target)
    {
        // nothing
    }

    Tokenizer(const Tokenizer &other) : _fileName(other._fileName)
    {
        // nothing
    }

    std::vector<Token> tokenize();

private:
    std::string _fileName;

    Token getNextToken(std::ifstream &file);
    bool isSymbol(const std::string &word, TokenType &type);
    bool isKeyword(const std::string &word, TokenType &type);
    bool isLiteral(const std::string &word, TokenType &type);
};

#endif // TOKENIZER_H