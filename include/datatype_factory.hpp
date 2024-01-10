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
struct DataType;

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
        // copy the value over
        Value valueCopy(other.value);
        this->value = valueCopy;
    };

    /// @brief Equality operator for Field
    bool operator==(const Field &other)
    {
        return this->name == other.name && this->predefined == other.predefined && this->type == other.type && this->size == other.size && this->value == other.value;
    };

};

#pragma endregion Node Types

struct SchemaMeta
{
    std::string schemaName;
    int versionNumber[3];
    std::map<std::string, DataType> additionalFields;
};

/// @brief Contiains either a field or a custom DataType
struct DataMember
{
    void *memberPtr = nullptr;
    bool isDataType = false; // if this is true, then the memberPtr is a pointer to a DataType, otherwise it is a pointer to a Field

    /// @brief Empty constructor for DataMember
    DataMember() = default;

    /// @brief Constructor for DataMember
    /// @param field The field to store
    DataMember(const Field &field)
    {
        // malloc the field and copy it over
        this->memberPtr = malloc(sizeof(Field));
        memcpy(memberPtr, &field, sizeof(Field));
        this->isDataType = false;
    };

    /// @brief Constructor for DataMember
    /// @param dataType The custom DataType to store
    DataMember(const DataType &dataType)
    {
        // malloc the field and copy it over
        this->memberPtr = malloc(sizeof(DataType));
        memcpy(memberPtr, &dataType, sizeof(DataType));
        this->isDataType = true;
    };

    /// @brief Copy constructor for DataMember
    /// @param other The DataMember to copy
    DataMember(const DataMember &other)
    {
        this->memberPtr = other.memberPtr;
        this->isDataType = other.isDataType;
    };

    /// @brief Assignment operator for DataMember
    /// @param other The DataMember to copy
    DataMember &operator=(const DataMember &other)
    {
        this->memberPtr = other.memberPtr;
        this->isDataType = other.isDataType;
        return *this;
    };

    /// @brief String indexing operator for DataMember
    /// @details If the DataMember is not a DataType, then this will throw an exception
    /// @param fieldName The name of the field to get
    /// @return DataMember
    DataMember operator[](const std::string &fieldName)
    {
        if (!isDataType)
        {
            throw std::invalid_argument("DataMember is a Field, not a DataType");
        }

        DataType DataType = this->getDataType();
        return DataType.getMember(fieldName);
    };

    /// @brief Indexing operator for DataMember
    Field getField()
    {
        if (this->isDataType)
        {
            throw std::invalid_argument("DataMember is a DataType, not a Field");
        }

        Field field = *(Field *)this->memberPtr;
        return field;
    };

    DataType getDataType()
    {
        if (!this->isDataType)
        {
            throw std::invalid_argument("DataMember is a Field, not a DataType");
        }

        DataType dataType = *(DataType *)this->memberPtr;
        return dataType;
    };
};

/// @brief A datatype is a contianer for a set of fields, and may be nested
/// @details A datatype may be nested, and may contain other datatypes
/// @details A datatype may also contain predefined fields, which are fields that have a predefined value
struct DataType
{
    std::string name;
    std::size_t size;
    std::map<std::string, Field> fields;             // map of field name to field
    std::map<std::string, DataType> customDataTypes; // map of custom data type name to custom data type

    /// @brief Empty constructor for DataType
    DataType() = default;

    /// @brief Copy constructor for DataType
    DataType(const DataType &other)
    {
        this->name = other.name;
        this->size = other.size;
        // copy fields and values over
        for (auto &field : other.fields)
        {
            Field fieldCopy(field.second);
            this->fields[field.first] = fieldCopy;
        }
    };

    /// @brief Assignment operator for DataType
    DataType &operator=(const DataType &other)
    {
        this->name = other.name;
        this->size = other.size;
        // copy fields and values over
        for (auto &field : other.fields)
        {
            Field fieldCopy(field.second);
            this->fields[field.first] = fieldCopy;
        }
        return *this;
    };

    /// @brief Adds a field to the DataType
    /// @details The field must be a primative type, and not a custom DataType
    /// @param field The field to add
    void addField(const Field &field)
    {
        fields[field.name] = field;
        size += field.size;
    };

    /// @brief Removes a field from the DataType
    /// @param fieldName The name of the field to remove
    void removeField(const std::string &fieldName)
    {
        if (fields.find(fieldName) == fields.end())
        {
            throw std::invalid_argument("Field does not exist");
        }

        size -= fields[fieldName].size;
        fields.erase(fieldName);
    };

    /// @brief Adds a custom DataType field to the DataType
    /// @param dataType The custom DataType to add
    void addCustomField(DataType dataType, const std::string &fieldName)
    {
        customDataTypes[fieldName] = dataType;
        size += dataType.size;
    };

    /// @brief Removes a custom DataType field from the DataType
    /// @param fieldName The name of the custom DataType field to remove
    void removeCustomField(const std::string &fieldName)
    {
        if (customDataTypes.find(fieldName) == customDataTypes.end())
        {
            throw std::invalid_argument("Custom field does not exist");
        }

        size -= customDataTypes[fieldName].size;
        customDataTypes.erase(fieldName);
    };

    /// @brief Gets the size of the DataType
    /// @return std::size_t
    std::size_t getSize() const
    {
        return size;
    };

    /// @brief Gets a data member from the DataType
    /// @param fieldName The name of the field to get
    /// @return Field
    DataMember getMember(const std::string &fieldName) const
    {
        if (fields.find(fieldName) != fields.end())
        {
            return DataMember(fields.at(fieldName));
        }
        else if (customDataTypes.find(fieldName) != customDataTypes.end())
        {
            return DataMember(customDataTypes.at(fieldName));
        }
        else
        {
            throw std::invalid_argument("Field does not exist");
        }
    };

    /// @brief Flattens the DataType into a map of field name to value
    /// @details If there are any custom DataTypes held in the fields, they will be recursively flattened
    /// @details This flattening process will result in a map that is accessible with map["fieldName"]["fieldName"]...
    /// @return std::map<std::string, Value>
    std::map<std::string, DataMember> flatten() const
    {
        // flattens the DataType into a map of field name to value
        std::map<std::string, DataMember> flattened;
        for (auto &field : fields)
        {
            // create a data member for the field
            DataMember member(field.second);
            flattened[field.first] = member;
        }

        // now add the custom data types
        for (auto &customDataType : customDataTypes)
        {
            std::map<std::string, DataMember> flattenedCustomDataType = customDataType.second.flatten();
            for (auto &field : flattenedCustomDataType)
            {
                // create a data member for the field
                DataMember member(field.second);
                flattened[customDataType.first] = member;
            }
        }

        return flattened;
    }

    /// @brief Flattens the DataType into a map of field name to fields
    /// @details If there are any custom DataTypes held in the fields, they will be recursively flattened, but will not create a map of maps
    /// @details This flattening process will result in a map that is accessible with map["fieldName"]
    /// @details However, if the field is within an internal datatype, it will be accessible with map["dataTypeFieldName_fieldName"]
    std::map<std::string, Field> flattenFull() const
    {
        // flattens the DataType into a map of field name to value
        std::map<std::string, Field> flattened;
        for (auto &field : fields)
        {
            flattened[field.first] = field.second;
        }

        // now add the custom data types
        for (auto &customDataType : customDataTypes)
        {
            std::map<std::string, Field> flattenedCustomDataType = customDataType.second.flattenFull();
            for (auto &field : flattenedCustomDataType)
            {
                flattened[customDataType.first + "_" + field.first] = field.second;
            }
        }

        return flattened;
    }
};

#endif // __DATATYPE_FACTORY_H__