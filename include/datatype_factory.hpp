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
    // stores the value of the field
    // if this a heap allocated value, then the buffer holds a pointer to the heap
    // there, the value is laid out as follows:
    // SIZE (2 bytes -- as short), VALUE (SIZE bytes -- char array)
    // The maximum size of a value is 256 bytes (not including the size of the short)
    // otherwise, the buffer holds the valus
    char buffer[16];
    bool heapAllocated = false;

    Value() = default;

    template <typename T>
    Value &operator=(const T &primative)
    {
        if (sizeof(T) > sizeof(Value))
        {
            // we should refer to the special case of strings -- call that version of the operator=
            const char *valueBuffer = (char *)(&primative);
            this->operator=(valueBuffer);
            return *this;
        }

        char *valueBuffer = (char *)(&primative);
        for (int i = 0; i < sizeof(T); i++)
        {
            buffer[i] = valueBuffer[i];
        }

        this->heapAllocated = false;
        return *this;
    };

    // Value var = "hello";
    // Value var = 10;
    Value &operator=(const char *primative)
    {
        // we need to malloc the string
        // but we need to know the size of the string
        // so we need to iterate through the string to find the size
        short maxSize = 256;
        short size = 0;
        const char *valueBuffer = primative;
        for (int i = 0; i < maxSize; i++)
        {
            std::cout << (char)valueBuffer[i] << std::endl;
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

        // now we know the size of the string
        // we can malloc the string
        // LENGTH (2 bytes) | REST_SRC (LENGTH bytes)
        char *stringPtr = (char *)malloc((size + sizeof(short) * sizeof(char)));

        std::cout << "Mallocing string of size " << size << " original : " << primative << std::endl;
        // prepend the size of the string to the string
        strncpy(stringPtr, (char *)(&size), sizeof(short));
        // copy the string into the malloc'd string, offset by the size of the short
        stringPtr += sizeof(short);
        strncpy(stringPtr, primative, size);
        // reset the pointer
        stringPtr -= sizeof(short);
        // as a sanity check, we can print the string
        std::cout << "Saved value:\n";
        for (int i = 0; i < size + sizeof(short); i++)
        {
            std::cout << "byte (" << i << "): " << stringPtr[i];
            std::cout << "\n";
        }
        std::cout << std::endl;

        this->heapAllocated = true;
        // copy the address of the string into our buffer
        strncpy(buffer, stringPtr, sizeof(char *));
        return *this;
    };


    // Value var = 10;
    // bool equal = var == 10;
    template <typename T>
    bool operator==(const T &other) const
    {
        if (sizeof(T) > sizeof(Value))
        {
            throw std::invalid_argument("Invalid type for value comparision (other is too big) -- must be int, float, bool, string or version");
        }

        if (this->heapAllocated)
        {
            std::cout << "Grabbing value from heap" << std::endl;
            char *valueBuffer = (char *)(&this->buffer);
            // we should check the size of the value
            short valueSize = (short)(*valueBuffer);
            std::cout << "Value: " << valueBuffer << std::endl;
            // now we can compare the value to the other
            const char *otherBytes = (const char *)(std::addressof(other));
            std::cout << "Value size: " << valueSize << std::endl;
            bool result = false;
            int valueOffset = sizeof(short);
            for (int i = 0; i < valueSize; i++)
            {
                const char value = valueBuffer[i + valueOffset];
                const char other = otherBytes[i];
                std::cout << "comparing " << value << " to " << other << std::endl;
                result = result || (value == other);
            }
            return result;
        }
        else
        {
            const char *valueBuffer = this->buffer;
            const char *otherBytes = (char *)(&other);
            bool result = false;
            for (int i = 0; i < sizeof(T); i++)
            {
                std::cout << "comparing " << valueBuffer[i] << " to " << otherBytes[i] << std::endl;
                result = result || (valueBuffer[i] == otherBytes[i]);
            }
            return result;
        }
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