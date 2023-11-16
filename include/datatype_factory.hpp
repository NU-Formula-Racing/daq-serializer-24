#ifndef __DATATYPE_FACTORY_H__
#define __DATATYPE_FACTORY_H__

#include <string>
#include <map>
#include <memory>
#include <stdexcept>
#include <iostream>
#include <string.h>

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

struct Field;

struct DataType
{
    std::string name;
    std::size_t size;
    std::map<std::string, Field> fields; // map of field name to field
};

struct Value
{
    char buffer[16]; // 16 bytes is the max size of a value

    Value() = default;

    template <typename T>
    Value &operator=(const T &other)
    {
        if (sizeof(T) > sizeof(Value))
        {
            throw std::invalid_argument("Invalid type for value comparision field -- must be int, float, bool, string or version");
        }

        char *valueBuffer = (char*)(&other);
        for (int i = 0; i < sizeof(T); i++)
        {
            buffer[i] = valueBuffer[i];
        }

        return *this;
    };
    
    Value &operator=(const char* other)
    {
        // we need to malloc the string
        // but we need to know the size of the string
        // so we need to iterate through the string to find the size
        short maxSize = 256;
        short size = 0;
        char *valueBuffer = (char*)(&other);
        for (int i = 0; i < maxSize; i++)
        {
            if (valueBuffer[i] == '\0')
            {
                size = i;
                break;
            }
        }

        if (size == 0)
        {
            throw std::invalid_argument("Invalid string -- must be null terminated");
        }

        // now we know the size of the string
        // we can malloc the string
        char *stringPtr = (char*)malloc(size);
        // copy the string into the malloc'd string
        for (int i = 0; i < size; i++)
        {
            stringPtr[i] = valueBuffer[i];
        }

        // now we can set the value
        strncpy(buffer, stringPtr, 8);
        return *this;
    };

    template <typename T>
    bool operator==(const T &other) const
    {
        if (sizeof(T) > sizeof(Value))
        {
            throw std::invalid_argument("Invalid type for value comparision -- must be int, float, bool, string or version");
        }

        const char *valueBuffer = this->buffer;
        const char *otherBytes = (char*)(&other);
        for (int i = 0; i < sizeof(T); i++)
        {
            if (valueBuffer[i] != otherBytes[i])
            {
                return false;
            }
        }
        return true;
    };
};

struct Field
{
    std::string name;
    bool predefined;
    Value value; // only if this is a predefined field
    FieldType type;
    std::size_t size;

    // constructor for creating a predefined field
    template <typename T>
    static Field predfinedField(std::string name, T value)
    {
        Field field;
        field.name = name;
        field.predefined = true;
        if (sizeof(T) > sizeof(Value))
        {
            throw std::invalid_argument("Invalid type for predefined field (value is larger than 16 bytes) -- must be int, float, bool, string or version");
        }
    
        field.size = sizeof(T);
        field.value = value;

        // get the type of the field
        if (std::is_same<T, int>::value)
        {
            field.type = FieldType::INT;
        }
        else if (std::is_same<T, float>::value)
        {
            field.type = FieldType::FLOAT;
        }
        else if (std::is_same<T, bool>::value)
        {
            field.type = FieldType::BOOL;
        }
        else if (std::is_same<T, char *>::value)
        {
            field.type = FieldType::STRING;
        }
        else if (std::is_same<T, int[3]>::value)
        {
            field.type = FieldType::VERSION;
        }
        else
        {
            throw std::invalid_argument("Invalid type for predefined field -- must be int, float, bool, string or version");
        }

        return field;
    };

    // constructor for creating a custom field, not predefined
    static Field emptyField(std::string name, FieldType type)
    {
        Field field;
        field.name = name;
        field.predefined = false;
        field.type = type;

        // get the size of the field
        switch (type)
        {
        case FieldType::INT:
            field.size = sizeof(int);
            break;
        case FieldType::FLOAT:
            field.size = sizeof(float);
            break;
        case FieldType::BOOL:
            field.size = sizeof(bool);
            break;
        case FieldType::STRING:
            field.size = sizeof(char *);
            break;
        case FieldType::VERSION:
            field.size = sizeof(int[3]);
            break;
        case FieldType::CUSTOM:
            field.size = sizeof(DataType *);
        default:
            throw std::invalid_argument("Invalid type for field -- must be int, float, bool, string, version or custom");
        }

        return field;
    };

    // empty constructor
    Field() = default;

    // copy constructor
    Field(const Field &other)
    {
        this->name = other.name;
        this->predefined = other.predefined;
        this->type = other.type;
        this->size = other.size;
        this->value = other.value;
    };
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
    DataTypeFactory() = default;

    // DataType buildDataType(std::string name, std::map<std::string, Field> fields)
    // {

    // };

    // template <typename T>
    // Value buildValue(T value)
    // {

    // };

    // template <typename T>
    // FieldType getFieldType()
    // {

    // };
};
#endif // __DATATYPE_FACTORY_H__