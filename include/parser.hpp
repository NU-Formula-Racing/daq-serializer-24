#ifndef __PARSER_H__
#define __PARSER_H__

#include <vector>
#include <string>
#include <memory>
#include <map>

#include "datatype_factory.hpp"
#include "frame.hpp"

struct Token;

struct Schema
{
    std::string schemaName;
    int *versionNumber;
    std::shared_ptr<FrameTemplate> frameTemplate;
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

        static ParsingResult invalidDataType(TokenType token, int index, std::string description)
        {
            ParsingResult result(token, index);
            result.message << "Invalid data type: " << description << std::endl;
            result.isValid = false;
            return result;
        }

        static ParsingResult missingMetaInformation(std::vector<std::string> missingFields)
        {
            ParsingResult result;
            result.isValid = false;
            result.message << "Missing meta information: " << std::endl;
            for (auto field : missingFields)
            {
                result.message << field << std::endl;
            }
            return result;
        }

        static ParsingResult missingMeta()
        {
            ParsingResult result;
            result.isValid = false;
            result.message << "Missing meta information" << std::endl;
            return result;
        }

        static ParsingResult missingFrame()
        {
            ParsingResult result;
            result.isValid = false;
            result.message << "Missing frame information" << std::endl;
            return result;
        }

        static ParsingResult duplicateDefinition(TokenType token, int index)
        {
            ParsingResult result(token, index);
            result.message << "Duplicate definition: " << Tokenizer::tokenTypeToString(token) << std::endl;
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
            else
            {
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

    ParsingResult buildSchema(const std::vector<Token> &tokens, Schema &out);
    ParsingResult isValidSequence(const std::vector<Token> &tokens);

private:
    const std::map<std::string, TokenType> _EXPECTED_META_FIELDS = {
        {".schema", STRING_LITERAL},
        {".version", VERSION_LITERAL}};

    std::map<std::string, DataType> _dataTypes;

    bool _isScopeClosed(const std::vector<Token> &tokens, int openingScopeIndex) const;
    int _levensteinDistance(const std::string &word1, const std::string &word2) const;
    ParsingResult _validateMetaFields(std::map<std::string, Token> &metaFields) const;

    int* _parseVersion(const std::string &versionString) const;

};

#endif // __PARSER_H__