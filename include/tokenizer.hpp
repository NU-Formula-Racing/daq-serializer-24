#ifndef __TOKENIZER_H__
#define __TOKENIZER_H__

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <variant>

namespace daqser::impl
{
    enum TokenType
    {
        // Inavlid
        TOKEN_INVALID,

        // Keywords
        TOKEN_META,
        TOKEN_DEF,
        TOKEN_FRAME,

        // Symbols
        TOKEN_L_BRACE,
        TOKEN_R_BRACE,
        TOKEN_L_PARENTHESES,
        TOKEN_R_PARENTHESES,
        TOKEN_COLON,
        TOKEN_SEMICOLON,
        TOKEN_END_OF_FILE,

        // Identifiers
        TOKEN_DATA_TYPE,  // data type names -- this is actually not used lol
        TOKEN_IDENTIFIER, // variable names

        // Literals
        TOKEN_INT_LITERAL,
        TOKEN_FLOAT_LITERAL,
        TOKEN_BOOL_LITERAL,
        TOKEN_STRING_LITERAL,
        TOKEN_VERSION_LITERAL,
    };

    struct Token
    {
        TokenType type;
        std::string value;
    };

    class Tokenizer
    {
    public:
        Tokenizer() : _source("")
        {
            // nothing
        }

        Tokenizer(const std::string &target) : _source(target)
        {
            // nothing
        }

        Tokenizer(const Tokenizer &other) : _source(other._source)
        {
            // nothing
        }

        static std::string tokenTypeToString(const TokenType &tokenType)
        {
            static std::map<int, std::string> tokenMap{
                {TOKEN_INVALID, "INVALID"},
                {TOKEN_META, "META"},
                {TOKEN_DEF, "DEF"},
                {TOKEN_FRAME, "FRAME"},
                {TOKEN_L_BRACE, "L_BRACE"},
                {TOKEN_R_BRACE, "R_BRACE"},
                {TOKEN_L_PARENTHESES, "L_PARENTHESES"},
                {TOKEN_R_PARENTHESES, "R_PARENTHESES"},
                {TOKEN_COLON, "COLON"},
                {TOKEN_SEMICOLON, "SEMICOLON"},
                {TOKEN_END_OF_FILE, "END_OF_FILE"},
                {TOKEN_DATA_TYPE, "DATA_TYPE"},
                {TOKEN_IDENTIFIER, "IDENTIFIER"},
                {TOKEN_INT_LITERAL, "INT_LITERAL"},
                {TOKEN_FLOAT_LITERAL, "FLOAT_LITERAL"},
                {TOKEN_BOOL_LITERAL, "BOOL_LITERAL"},
                {TOKEN_STRING_LITERAL, "STRING_LITERAL"},
                {TOKEN_VERSION_LITERAL, "VERSION_LITERAL"}};

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

        /// @brief Tokenizes the content passed to the constructor, treating it as a file name
        /// @return A vector of tokens
        std::vector<Token> tokenizeFile();

        /// @brief Tokenizes the content passed to the constructor, treating it the source code
        /// @return A vector of tokens
        std::vector<Token> tokenizeContent();
        bool isSymbol(const std::string &word, TokenType &type);
        bool isKeyword(const std::string &word, TokenType &type);
        bool isLiteral(const std::string &word, TokenType &type);
        bool isValidIdentifier(const std::string &word);

    private:
        std::string _source;

        Token getNextToken(std::istream &file);
    };

} // namespace daqser::impl
#endif // __TOKENIZER_H__