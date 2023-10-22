#ifndef __PARSER_H__
#define __PARSER_H__

#include <vector>
#include <string>
#include <memory>
#include <map>

struct Token;

enum FieldType
{
    INT,
    FLOAT,
    BOOL,
    STRING,
    VERSION,
    CUSTOM
};

/// <summary>
// DataTypes have a name, size and a map of fields from fieldName to field values
// Each field has a name, a variable type and a possible predfefined value
// The field may be a custom DataType, in this case, we must recursively search for primative
// Thinking about DataTypes as a forest of trees is the best way to think of it,
// with the rule that the bottom leaf of all trees will be a primative (NOT custom) datatype, with a possible predefined definition
// </summary>

#pragma region Node types
struct DataType
{
    std::string name;
    std::size_t size;
    std::map<std::string, DataType> fields;
};

union Value
{
    int intVal;
    float floatValue;
    bool boolValue;
    std::string strVal;
    int versionValue[3];
    std::shared_ptr<DataType> customValue;
};

struct Field
{
    std::string name;
    FieldType type;
    Value value;
    bool predefined;
};
#pragma endregion Node Types

struct SchemaMeta
{
    std::string schemaName;
    int versionNumber[3];
    std::map<std::string, DataType> additionalFields;
};

struct Schema
{
    SchemaMeta meta;
    std::map<std::string, DataType> dataTypes;
};

class Parser
{
public:
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

        static ParsingResult ok()
        {
            ParsingResult result;
            result.isValid = true;
            result.message << "Parsing successful" << std::endl;
            return result;
        }

    private:
        ParsingResult() : message() {}

        ParsingResult(TokenType token, int index)
        {
            message << "** Parsing Result at index " << index << "(TOKEN TYPE: " << token << ") **" << std::endl;
        }
    };

    Schema buildSchema(const std::vector<Token> &tokens);
    ParsingResult isValidSequence(const std::vector<Token> &tokens);

private:
    std::map<std::string, DataType> _dataTypes;

    template <typename T>
    DataType buildDataType(std::string name, T value);

    template <typename T>
    Value buildValue(T value);

    template <typename T>
    FieldType getFieldType();

    bool isScopeClosed(const std::vector<Token> &tokens, int openingScopeIndex);
};

#endif // __PARSER_H__