#ifndef __DATATYPE_FACTORY_H__
#define __DATATYPE_FACTORY_H__

#include <string>
#include <map>
#include <memory>
#include <stdexcept>
#include <iostream>
#include <string.h>
#include <type_traits>

enum FieldType
{
    INT,
    FLOAT,
    BOOL,
    STRING,
    VERSION,
    CUSTOM
};

/// @brief
// DataTypes have a name, size and a map of fields from fieldName to field values
// Each field has a name, a variable type and a possible predfefined value
// The field may be a custom DataType, in this case, we must recursively search for primative
// Thinking about DataTypes as a forest of trees is the best way to think of it,
// with the rule that the bottom leaf of all trees will be a primative (NOT custom) datatype, with a possible predefined definition
//

#pragma region Node types

struct Field;
struct Value;

struct DataType
{
    std::string name;
    std::size_t size;
    std::map<std::string, Field> fields; // map of field name to field

    /// @brief Flattens the DataType into a map of field name to value
    /// @details If there are any custom DataTypes held in the fields, they will be recursively flattened
    /// @details This flattening process will result in a map that is accessible with map["fieldName"]["fieldName"]...
    /// @return std::map<std::string, Value>
    std::map<std::string, Value> flatten();

    /// @brief Flattens the DataType into a map of field name to value
    /// @details If there are any custom DataTypes held in the fields, they will be recursively flattened, but will not create a map of maps
    /// @details This flattening process will result in a map that is accessible with map["fieldName"]
    /// @details However, if the field is within an internal datatype, it will be accessible with map["dataTypeFieldName_fieldName"]
    std::map<std::string, Value> flattenFull();
};

/// @brief A Value is a container for any type of value
/// @details The value is stored as a void pointer, and the type is stored as a FieldType
/// @details The size of the value is stored as well, so that we can do type checking
struct Value
{
    void *valuePtr = nullptr;
    int valueSize = 0;

    /// @brief Empty constructor for Value
    /// @details The value is stored as a void pointer, as well as the size of the value
    /// @details The size of the value is stored as well, so that we can do type checking
    Value() = default;

    /// @brief Constructor for Value
    /// @details The value is stored as a void pointer, as well as the size of the value
    /// @details The size of the value is stored as well, so that we can do type checking
    /// @param value The value to store
    template <typename T>
    Value(T value)
    {
        // malloc the value and copy it over
        this->valuePtr = malloc(sizeof(T));
        memcpy(valuePtr, &value, sizeof(T));
        this->valueSize = sizeof(T);
    };

    /// @brief Copy constructor for Value
    /// @details The value is stored as a void pointer, as well as the size of the value
    /// @details The size of the value is stored as well, so that we can do type checking
    Value(const Value &other)
    {
        void *valueBuffer = malloc(other.valueSize);
        memcpy(valueBuffer, other.valuePtr, other.valueSize);
        this->valuePtr = valueBuffer;
        this->valueSize = other.valueSize;
    };

    /// @brief Assignment operator for Value
    /// @details The value is stored as a void pointer, as well as the size of the value
    /// @details The size of the value is stored as well, so that we can do type checking
    template <typename T>
    Value &operator=(T value)
    {
        // malloc the value and copy it over
        if (valuePtr != nullptr)
        {
            free(valuePtr);
        }

        this->valuePtr = malloc(sizeof(T));
        memcpy(valuePtr, &value, sizeof(T));
        this->valueSize = sizeof(T);
        return *this;
    };

    /// @brief Assignment operator for Value
    /// @details The value is stored as a void pointer, as well as the size of the value
    /// @details The size of the value is stored as well, so that we can do type checking
    Value &operator=(const Value &other)
    {
        this->valuePtr = other.valuePtr;
        this->valueSize = other.valueSize;
        return *this;
    };

    /// @brief Equality operator for Value
    /// @details The value is stored as a void pointer, as well as the size of the value
    /// @details The size of the value is stored as well, so that we can do type checking
    template <typename T>
    bool operator==(T value)
    {
        // if the valuePtr is nullptr, then consider it to be equal to a bit pattern of all zeros
        if (valuePtr == nullptr || valuePtr == NULL || valueSize == 0)
        {
            if (std::is_same<T, int>::value || std::is_same<T, float>::value || std::is_same<T, bool>::value)
            {
                return value == 0;
            }
            else if (std::is_same<T, const char *>::value || std::is_same<T, std::string>::value || std::is_same<T, char *>::value)
            {
                char *valueComp = (char *)(&value);
                return strcmp(valueComp, "") == 0;
            }
            else if (std::is_same<T, int *>::value)
            {
                int *valueComp = (int *)(&value);
                return valueComp[0] == 0 && valueComp[1] == 0 && valueComp[2] == 0;
            }
            else
            {
                try
                {
                    T empty;
                    return value == empty;
                }
                catch (std::exception e)
                {
                    return false;
                }
            }
        }

        if (sizeof(T) != valueSize)
        {
            return false;
        }

        return *(T *)valuePtr == value;
    };

    /// @brief Inequality operator for Value
    /// @details The value is stored as a void pointer, as well as the size of the value
    /// @details The size of the value is stored as well, so that we can do type checking
    template <typename T>
    bool operator!=(T value)
    {
        return !(*this == value);
    };

    /// @brief Checks if this value is not null or empty
    bool isValid()
    {
        return valuePtr != nullptr && valueSize > 0;
    };

    /// @brief Destructor for Value
    /// @details The value is stored as a void pointer, as well as the size of the value
    /// @details The size of the value is stored as well, so that we can do type checking
    ~Value()
    {
        free(valuePtr);
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

        field.value = value;
        // cannot set the size of the field here, because we don't know the type yet
        // doing sizeof(T) will not work because it will return the size of the pointer

        // get the type of the field
        if (std::is_same<T, int>::value)
        {
            field.type = FieldType::INT;
            field.size = sizeof(int);
        }
        else if (std::is_same<T, float>::value)
        {
            field.type = FieldType::FLOAT;
            field.size = sizeof(float);
        }
        else if (std::is_same<T, bool>::value)
        {
            field.type = FieldType::BOOL;
            field.size = sizeof(bool);
        }
        else if (std::is_same<T, const char *>::value)
        {
            field.type = FieldType::STRING;
            field.size = sizeof(char *);
        }
        else if (std::is_same<T, std::string>::value)
        {
            field.type = FieldType::STRING;
            field.size = sizeof(char *);
        }
        else if (std::is_same<T, int *>::value)
        {
            field.type = FieldType::VERSION;
            field.size = sizeof(int[3]);
        }
        else
        {
            throw std::invalid_argument("Unrecognized type for predefined field -- must be int, float, bool, string or version");
        }

        std::cout << "Created a predefined field with type " << fieldTypeToString(field.type) << " and size " << field.size << std::endl;
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
            field.size = sizeof(uint8_t *);
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

    // mapping from FieldType to string
    static std::string fieldTypeToString(FieldType type)
    {
        switch (type)
        {
        case FieldType::INT:
            return "int";
        case FieldType::FLOAT:
            return "float";
        case FieldType::BOOL:
            return "bool";
        case FieldType::STRING:
            return "string";
        case FieldType::VERSION:
            return "version";
        case FieldType::CUSTOM:
            return "custom";
        default:
            throw std::invalid_argument("Invalid type for field -- must be int, float, bool, string, version or custom");
        }
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