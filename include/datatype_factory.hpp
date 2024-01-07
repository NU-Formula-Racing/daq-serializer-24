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

struct Value
{
    // stores the value of the field
    // if this a heap allocated value, then the buffer holds a pointer to the heap
    // there, the value is laid out as follows:
    // SIZE (2 bytes -- as short), VALUE (SIZE bytes -- unsigned char array)
    // The maximum size of a value is 256 bytes (not including the size of the short)
    // otherwise, the buffer holds the valus
    unsigned char buffer[16];
    bool heapAllocated = false;

    Value()
    {
        memset(buffer, 0, sizeof(buffer));
        this->heapAllocated = false;
    }

    template <typename T>
    Value &operator=(const T &primative)
    {
        if (sizeof(T) > 16)
        {
            // we should refer to the special case of strings -- call that version of the operator=
            const unsigned char *valueBuffer = (unsigned char *)(&primative);
            this->operator=(valueBuffer);
            return *this;
        }

        unsigned char *valueBuffer = (unsigned char *)(&primative);
        for (int i = 0; i < sizeof(T); i++)
        {
            buffer[i] = valueBuffer[i];
        }

        this->heapAllocated = false;
        return *this;
    };

    // Value var = "hello";
    // Value var = 10;
    Value &operator=(const unsigned char *primative)
    {
        // we need to malloc the string
        // but we need to know the size of the string
        // so we need to iterate through the string to find the size
        short maxSize = 256;
        short size = 0;
        const unsigned char *valueBuffer = primative;
        for (int i = 0; i < maxSize; i++)
        {
            std::cout << (unsigned char)valueBuffer[i] << std::endl;
            if (valueBuffer[i] == '\0')
            {
                size = i;
                break;
            }
        }

        std::cout << "\nSize of string: " << size << std::endl;

        if (size <= 0)
        {
            throw std::invalid_argument("Invalid string -- must be null terminated");
        }

        // we need to malloc the string
        // we will be using run-length encoding to store the string
        int bufferSize = sizeof(short) + size;
        unsigned char *buffer = (unsigned char *)malloc(bufferSize);
        std::cout << "Allocated buffer of size " << bufferSize << std::endl;
        // copy the size into the buffer
        memcpy(buffer, &size, sizeof(short));
        int startIndex = sizeof(short);
        // copy the string into the buffer
        for (int i = 0; i < size; i++)
        {
            std::cout << "Copying byte " << i << " : " << valueBuffer[i] << std::endl;
            buffer[startIndex + i] = valueBuffer[i];
        }

        // set the buffer
        this->heapAllocated = true;
        // copy the pointer to the buffer into the value buffer
        memcpy(this->buffer, &buffer, sizeof(unsigned char *));
    };


    // Value var = 10;
    // bool equal = var == 10;
    template <typename T>
    bool operator==(const T &other) const
    {
        const unsigned char *valueBuffer;
        const unsigned char *otherBuffer = (unsigned char *)(&other);
        short size = 0;

        if (this->heapAllocated)
        {
            std::cout << "Comparing heap allocated value" << std::endl;
            // grab the value buffer from the run-length encoded string
            size = *(short *)buffer;
            std::cout << "Size of string: " << size << std::endl;
            valueBuffer = buffer + sizeof(short);
        }
        else
        {
            std::cout << "Comparing non-heap allocated value" << std::endl;
            if (sizeof(T) > sizeof(Value))
            {
                // we are trying to compare a value that is larger than our buffer size
                // ordinarily, this would have been heap allocated in our assignment operator
                std::cout << "Comparing a value that is larger than our buffer size" << std::endl;
                std::cout << "Other size: " << sizeof(T) << std::endl;
                return false;
            }
            valueBuffer = buffer;
            size = sizeof(T);
        }

        bool result = true;
        // now we can compare the two buffers
        for (int i = 0; i < size; i++)
        {
            const unsigned char value = valueBuffer[i];
            const unsigned char otherValue = otherBuffer[i];
            std::cout << "Comparing byte " << i << " : " << value << " == " << otherValue << std::endl;
            if (value != otherValue)
            {
                result = false;
            }
        }

        return result;
    };

    ~Value()
    {
        if (this->heapAllocated)
        {
            free((void *)buffer);
        }
    }
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
            field.size = sizeof(unsigned char *);
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