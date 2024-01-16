#ifndef __PARSER_H__
#define __PARSER_H__

#include <vector>
#include <string>
#include <memory>
#include <map>

#include "datatype_factory.hpp"

struct Token;

struct Schema
{
    SchemaMeta meta;
    std::map<std::string, DataType> dataTypes;
};

class Parser
{
public:
    enum ParserScope
    {
        GLOBAL_SCOPE,
        DATA_TYPE_SCOPE,
        META_SCOPE,
        FRAME_SCOPE,
        POST_FRAME_SCOPE
    };

    class ParsingResult
    {
    public:
        bool isValid;
        std::stringstream message;

        static ParsingResult invalidToken(TokenType token, int index)
        {
            ParsingResult result(token, index);
            result.message << "Invalid token: " << token << std::endl;
            result.isValid = false;
            return result;
        }

        static ParsingResult invalidSequence(TokenType token, int index, std::string description)
        {
            ParsingResult result(token, index);
            result.message << "Invalid sequence : " << description << std::endl;
            result.isValid = false;
            return result;
        }

        static ParsingResult unclosedScope(TokenType token, int index)
        {
            ParsingResult result(token, index);
            result.isValid = false;
            if (token == L_BRACE)
                result.message << "Unclosed scope (Brace): " << token << std::endl;
            else if (token == L_PARENTHESES)
                result.message << "Unclosed scope (Parentheses): " << token << std::endl;
            else
                result.message << "Unclosed scope (Unknown): " << token << std::endl;
            return result;
        }

        static ParsingResult ok(std::string message = "")
        {
            ParsingResult result;
            result.isValid = true;
            if (message != "")
                result.message << message << std::endl;
            else {
                result.message << "Parsing Successful" << std::endl;
            }
            return result;
        }

    private:
        ParsingResult() : message() {}

        ParsingResult(TokenType token, int index)
        {
            std::string tokenString = Tokenizer::tokenTypeToString(token);
            message << "** Parsing Result at index " << index << "(TOKEN TYPE: " << tokenString << ") **" << std::endl;
        }
    };

    Schema buildSchema(const std::vector<Token> &tokens);
    ParsingResult isValidSequence(const std::vector<Token> &tokens);

private:
    std::map<std::string, DataType> _dataTypes;

    bool isScopeClosed(const std::vector<Token> &tokens, int openingScopeIndex);
};

#endif // __PARSER_H__