#ifndef __PARSER_H__
#define __PARSER_H__

#include <vector>
#include <string>
#include <memory>
#include <map>
#include <set>
#include <functional>

#include "datatype_factory.hpp"
#include "frame.hpp"
#include "tokenizer.hpp"

namespace daq::impl
{
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

            static ParsingResult duplicateTypeDefinition(std::string typeName)
            {
                ParsingResult result;
                result.isValid = false;
                result.message << "Duplicate type definition: " << typeName << std::endl;
                return result;
            }

            static ParsingResult undefinedTypes(std::vector<std::string> undefinedTypes)
            {
                ParsingResult result;
                result.isValid = false;
                result.message << "Undefined types: " << std::endl;
                for (auto type : undefinedTypes)
                {
                    result.message << type << std::endl;
                }
                return result;
            }

            static ParsingResult undefinedType(std::string type)
            {
                ParsingResult result;
                result.isValid = false;
                result.message << "Undefined type: " << type << std::endl;
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

            static ParsingResult cyclicDependency(std::vector<std::string> types)
            {
                ParsingResult result;
                result.isValid = false;
                result.message << "Cyclic dependency, types could not be resolved: " << std::endl;
                for (auto type : types)
                {
                    result.message << type << ", ";
                }
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

        ParsingResult buildSchema(const std::vector<Token> &tokens, Schema &out, bool onlyMeta = false);
        ParsingResult isValidSequence(const std::vector<Token> &tokens);

    private:
        const std::map<std::string, TokenType> _EXPECTED_META_FIELDS = {
            {".schema", STRING_LITERAL},
            {".version", VERSION_LITERAL}};

        // const std::set<std::string> _SUPPORTED_PRIMATIVES_FIELD = {
        //     "float", "bool", "long", "string", "int", "version"};

        const std::map<std::string, std::function<Field(std::string)>> _SUPPORTED_PRIMATIVES_FIELD = {
            {"float", [](std::string name)
             { return Field::emptyField(name, FieldType::FLOAT); }},
            {"bool", [](std::string name)
             { return Field::emptyField(name, FieldType::BOOL); }},
            {"string", [](std::string name)
             { return Field::emptyField(name, FieldType::STRING); }},
            {"int", [](std::string name)
             { return Field::emptyField(name, FieldType::INT); }},
            {"long", [](std::string name)
             { return Field::emptyField(name, FieldType::LONG); }},
            {"version", [](std::string name)
             { return Field::emptyField(name, FieldType::VERSION); }}};

        std::map<std::string, DataType> _dataTypes;

        bool _isScopeClosed(const std::vector<Token> &tokens, int openingScopeIndex) const;
        int _levensteinDistance(const std::string &word1, const std::string &word2) const;
        ParsingResult _validateMetaFields(std::map<std::string, Token> &metaFields) const;
        inline bool _isPrimative(const std::string &word) const { return _SUPPORTED_PRIMATIVES_FIELD.find(word) != _SUPPORTED_PRIMATIVES_FIELD.end(); }
        inline Field _createPrimativeField(const std::string &type, const std::string &name) const { return _SUPPORTED_PRIMATIVES_FIELD.at(type)(name); }

        int *_parseVersion(const std::string &versionString) const;
    };

} // namespace daq::impl

#endif // __PARSER_H__