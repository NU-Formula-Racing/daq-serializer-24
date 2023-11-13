#ifndef __DATATYPE_FACTORY_H__
#define __DATATYPE_FACTORY_H__

#include <string>
#include <map>
#include <memory>

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

class DataTypeFactory
{
public:
    template <typename T>
    DataType buildDataType(std::string name, T value)
    {

    };

    template <typename T>
    Value buildValue(T value);
    {

    };

    template <typename T>
    FieldType getFieldType()
    {

    };
};
#endif // __DATATYPE_FACTORY_H__