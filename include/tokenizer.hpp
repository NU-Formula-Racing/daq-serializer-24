#ifndef __TOKENIZER_H__
#define __TOKENIZER_H__

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
    L_PARENTHESES,
    R_PARENTHESES,
    COLON,
    SEMICOLON,
    END_OF_FILE,

    // Identifiers
    DATA_TYPE,  // data type names
    IDENTIFIER, // variable names

    // Literals
    INT_LITERAL,
    FLOAT_LITERAL,
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

    static std::string tokenTypeToString(const TokenType &tokenType)
    {
        static std::map<int, std::string> tokenMap{
            {INVALID, "INVALID"},
            {META, "META"},
            {DEF, "DEF"},
            {FRAME, "FRAME"},
            {L_BRACE, "L_BRACE"},
            {R_BRACE, "R_BRACE"},
            {L_PARENTHESES, "L_PARENTHESES"},
            {R_PARENTHESES, "R_PARENTHESES"},
            {COLON, "COLON"},
            {SEMICOLON, "SEMICOLON"},
            {END_OF_FILE, "END_OF_FILE"},
            {DATA_TYPE, "DATA_TYPE"},
            {IDENTIFIER, "IDENTIFIER"},
            {INT_LITERAL, "INT_LITERAL"},
            {FLOAT_LITERAL, "FLOAT_LITERAL"},
            {BOOL_LITERAL, "BOOL_LITERAL"},
            {STRING_LITERAL, "STRING_LITERAL"},
            {VERSION_LITERAL, "VERSION_LITERAL"}
        };

        auto it = tokenMap.find(tokenType);

        if (it != tokenMap.end())
            return it->second;

        return "UNKNOWN";
    }

    static std::string dumpTokens(const std::vector<Token> &tokens, const std::string &separator = " ")
    {
        std::stringstream ss;
        for (auto token : tokens)
        {
            ss << tokenTypeToString(token.type) << separator;
        }
        return ss.str();
    }

    std::vector<Token> tokenize();
    bool isSymbol(const std::string &word, TokenType &type);
    bool isKeyword(const std::string &word, TokenType &type);
    bool isLiteral(const std::string &word, TokenType &type);
    bool isValidIdentifier(const std::string &word);

private:
    std::string _fileName;

    Token getNextToken(std::ifstream &file);
};

#endif // __TOKENIZER_H__