#ifndef __DATATYPE_FACTORY_H__
#define __DATATYPE_FACTORY_H__

#include <string>
#include <map>
#include <memory>
#include <stdexcept>
#include <iostream>
#include <string.h>
#include <type_traits>
#include <sstream>
#include <vector>

namespace daq::impl
{
    /// @brief
    // DataTypes have a name, size and a map of fields from fieldName to field values
    // Each field has a name, a variable type and a possible predfefined value
    // The field may be a custom DataType, in this case, we must recursively search for primative
    // Thinking about DataTypes as a forest of trees is the best way to think of it,
    // with the rule that the bottom leaf of all trees will be a primative (NOT custom) datatype, with a possible predefined definition
    //

    enum FieldType
    {
        INT,
        FLOAT,
        BOOL,
        STRING,
        VERSION,
    };

#pragma region Node types

    struct Field;
    struct Value;

    /// @brief A Value is a container for any type of value
    /// @details The value is stored as a void pointer, and the type is stored as a FieldType
    /// @details The size of the value is stored as well, so that we can do type checking
    /// @details The actual "value" struct lives on the stack, whilst the valuePtr points to a malloc'd value on the heap
    /// @details This is so that we can copy the valuePtr without worrying about the lifetime of the value
    struct Value
    {
        std::shared_ptr<void> valuePtr = nullptr;
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
            if (std::is_same<T, Value>::value)
            {
                throw std::invalid_argument("Cannot create a Value from a Value");
            }

            this->valuePtr = std::make_shared<T>(value);
            this->valueSize = sizeof(T);
        };

        /// @brief Copy constructor for Value
        /// @details The value is stored as a void pointer, as well as the size of the value
        /// @details The size of the value is stored as well, so that we can do type checking
        Value(const Value &other)
        {
            this->valuePtr = other.valuePtr;
            this->valueSize = other.valueSize;
        };

        /// @brief Assignment operator for Value
        /// @details The value is stored as a void pointer, as well as the size of the value
        /// @details The size of the value is stored as well, so that we can do type checking
        template <typename T>
        Value &operator=(T value)
        {
            // std::cout << "Value::operator=(T value)" << std::endl;
            this->valuePtr = std::make_shared<T>(value);
            this->valueSize = sizeof(T);
            return *this;
        };

        /// @brief Assignment operator for Value
        /// @details The value is stored as a void pointer, as well as the size of the value
        /// @details The size of the value is stored as well, so that we can do type checking
        Value &operator=(const Value &other)
        {
            // std::cout << "Value::operator=(const Value &other)" << std::endl;
            this->valuePtr = other.valuePtr;
            this->valueSize = other.valueSize;
            return *this;
        };

        /// @brief Equality operator for Value
        /// @details The value is stored as a void pointer, as well as the size of the value
        /// @details The size of the value is stored as well, so that we can do type checking
        template <typename T>
        bool operator==(const T value) const
        {
            // if the valuePtr is nullptr, then consider it to be equal to a bit pattern of all zeros
            if (valuePtr == nullptr || valueSize == 0)
            {
                if (std::is_same<T, int>::value || std::is_same<T, float>::value || std::is_same<T, bool>::value)
                {
                    return value == 0;
                }
                else if (std::is_same<T, const char *>::value || std::is_same<T, char *>::value)
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

            // compare the values
            // cast the valuePtr to a pointer of type T
            std::cout << "Comparing valuePtr: " << std::hex << *(int *)(this->valuePtr.get()) << " to value: " << value << std::endl;
            T valueComp = this->get<T>();
            return valueComp == value;
        };

        /// @brief Equality operator for Value
        /// @details The value is stored as a void pointer, as well as the size of the value
        /// @details The size of the value is stored as well, so that we can do type checking
        bool operator==(const Value &other) const
        {
            if (this->valueSize != other.valueSize)
            {
                return false;
            }

            // if both values are null, then they are equal
            if (this->valuePtr == nullptr)
            {
                return other.valuePtr == nullptr;
            }

            // compare the values as bytes
            return memcmp(this->valuePtr.get(), other.valuePtr.get(), this->valueSize) == 0;
        }

        /// @brief Inequality operator for Value
        /// @details The value is stored as a void pointer, as well as the size of the value
        /// @details The size of the value is stored as well, so that we can do type checking
        template <typename T>
        bool operator!=(T value)
        {
            return !(*this == value);
        };

        /// @brief Checks if this value is not null or empty
        bool isValid() const
        {
            return valuePtr != nullptr && valueSize > 0;
        };

        /// @brief Returns the value as a casted type
        /// @tparam T The type to cast the value to
        /// @return T
        template <typename T>
        T get() const
        {
            std::cout << "Value::get<T>()" << std::endl;
            return *(T *)(this->valuePtr.get());
        }

        /// @brief Returns a string representation of the value
        /// @return std::string
        std::string toString() const
        {
            std::stringstream ss;
            ss << "Value: " << std::endl;
            if (this->valuePtr.get() == nullptr)
            {
                ss << "  ValuePtr: null" << std::endl;
            }
            else
            {
                ss << "  ValuePtr: " << std::hex << *(int *)(this->valuePtr.get()) << std::endl;
            }

            ss << "  ValueSize: " << std::dec << this->valueSize << std::endl;
            return ss.str();
        }

        /// @brief Returns the binary representation of the value
        /// @return std::vector<std::uint8_t>
        std::vector<std::uint8_t> toBinary() const
        {
            std::vector<std::uint8_t> binary;
            if (this->valuePtr.get() == nullptr)
            {
                return binary;
            }

            // copy the valuePtr into the binary vector
            binary.resize(this->valueSize);
            memcpy(binary.data(), this->valuePtr.get(), this->valueSize);
            return binary;
        }
    };

    /// @brief Explicit specialization of the get method for std::string to cope
    /// with the fact that std::string and char* can be implicitly converted to
    /// @return std::string
    template <>
    inline std::string Value::get<std::string>() const
    {
        std::cout << "Value::get<std::string>()" << std::endl;
        if (this->valueSize == sizeof(char *))
        {
            // this is probably a c-style string
            std::cout << "Value is a c-string" << std::endl;
            char *cString = *(char **)(this->valuePtr.get());
            return std::string(cString);
        }

        std::cout << "Value is a std::string" << std::endl;
        // this is probably a std::string
        return *(std::string *)(this->valuePtr.get());
    }

    struct Field
    {
        std::string name;
        bool predefined;
        Value value;
        FieldType type;
        std::size_t size;

        /// @brief Creates a field with a predefined value
        /// @tparam T The type of the value
        /// @param name The name of the field
        /// @param value The value of the field
        /// @return A field that is predefined with the given value
        template <typename T>
        static Field predfinedField(const std::string &name, T value)
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

            return field;
        };

        /// @brief Creates an empty field
        /// @param name The name of the field
        /// @param type The type of the field
        /// @return A field that is not predefined
        static Field emptyField(const std::string &name, FieldType type);

        /// @brief Returns a string representation of the FieldType
        /// @param type the type to convert to a string
        /// @return the string representation of the FieldType
        static std::string fieldTypeToString(FieldType type);

        ///@brief Empty Constructor
        ///@details Creates an empty field with no name, type or value
        Field() = default;

        /// @brief Copy Constructor for Field
        /// @details Creates a shallow copy of the field -- most notably, the Value that the field holds is a pointer to the same value
        /// @param other The field to copy
        Field(const Field &other);

        /// @brief assignment operator
        Field &operator=(const Field &other);

        /// @brief Equality operator for Field
        /// @details Two fields are equal if they have the same name, type and value
        /// @param other The field to compare to
        /// @return bool
        bool operator==(const Field &other) const;

        /// @brief Returns a string representation of the Field
        /// @return A string representation of the Field
        std::string toString() const;
    };

#pragma endregion Node Types

    struct DataType;

    /// @brief Contiains either a field or a custom DataType
    struct DataMember
    {
        void *memberPtr = nullptr;
        bool isDataType = false; // if this is true, then the memberPtr is a pointer to a DataType, otherwise it is a pointer to a Field

        /// @brief Empty constructor for DataMember
        DataMember() = default;

        /// @brief Constructor for DataMember
        /// @param field The field to store
        DataMember(const Field &field);

        /// @brief Constructor for DataMember
        /// @param dataType The custom DataType to store
        DataMember(const DataType &dataType);

        /// @brief Copy constructor for DataMember
        /// @param other The DataMember to copy
        DataMember(const DataMember &other);

        /// @brief Assignment operator for DataMember
        /// @param other The DataMember to copy
        DataMember &operator=(const DataMember &other);

        /// @brief String indexing operator for DataMember
        /// @details If the DataMember is not a DataType, then this will throw an exception
        /// @param fieldName The name of the field to get
        /// @return DataMember
        DataMember operator[](const std::string &fieldName);

        /// @brief Gets the field from the DataMember
        /// @return The field
        /// @exception std::invalid_argument Thrown if the DataMember is a DataType, or if the DataMember is null
        Field getField();

        /// @brief Gets the DataType from the DataMember
        /// @return The DataType
        /// @exception std::invalid_argument Thrown if the DataMember is a Field, or if the DataMember is null
        DataType getDataType();

        /// @brief Gets a string representation of the DataMember
        /// @return std::string
        std::string toString() const;
    };

    /// @brief A datatype is a contianer for a set of fields, and may be nested
    /// @details A datatype may be nested, and may contain other datatypes
    /// @details A datatype may also contain predefined fields, which are fields that have a predefined value
    struct DataType
    {
        std::string name;
        std::size_t size = 0;
        std::map<std::string, Field> fields;             // map of field name to field
        std::map<std::string, DataType> customDataTypes; // map of custom data type name to custom data type

        /// @brief Empty constructor for DataType
        DataType() = default;

        DataType(std::string name) : name(name), size(0){};

        /// @brief Copy constructor for DataType
        /// @param other The DataType to copy
        DataType(const DataType &other);

        /// @brief Assignment operator for DataType
        /// @param other The DataType to copy
        DataType &operator=(const DataType &other);

        /// @brief Equality operator for DataType
        /// @param other The DataType to compare to
        /// @return bool
        bool operator==(const DataType &other) const;

        /// @brief String indexing operator for DataType
        /// @details If the DataType does not contain a field with the given name, then this will throw an exception
        /// @param fieldName The name of the field to get
        /// @return DataMember
        DataMember operator[](const std::string &fieldName) const;

        /// @brief Adds a field to the DataType
        /// @details The field must be a primative type, and not a custom DataType
        /// @param field The field to add
        void addField(const Field &field);

        /// @brief Removes a field from the DataType
        /// @param fieldName The name of the field to remove
        void removeField(const std::string &fieldName);

        /// @brief Adds a custom DataType field to the DataType
        /// @param dataType The custom DataType to add
        void addCustomField(const std::string &fieldName, const DataType &dataType);

        /// @brief Removes a custom DataType field from the DataType
        /// @param fieldName The name of the custom DataType field to remove
        void removeCustomField(const std::string &fieldName);

        /// @brief Gets the size of the DataType
        /// @return std::size_t
        std::size_t getSize() const
        {
            return this->size;
        };

        /// @brief Gets a data member from the DataType
        /// @param fieldName The name of the field to get
        /// @return Field
        DataMember getMember(const std::string &fieldName) const;

        /// @brief Flattens the DataType into a map of field name to value
        /// @details If there are any custom DataTypes held in the fields, they will be recursively flattened
        /// @details This flattening process will result in a map that is accessible with map["fieldName"]["fieldName"]...
        /// @return std::map<std::string, Value>
        std::map<std::string, DataMember> flatten() const;

        /// @brief Flattens the DataType into a map of field name to fields
        /// @details If there are any custom DataTypes held in the fields, they will be recursively flattened, but will not create a map of maps
        /// @details This flattening process will result in a map that is accessible with map["fieldName"]
        /// @details However, if the field is within an internal datatype, it will be accessible with map["dataTypeFieldName_fieldName"]
        std::map<std::string, Field> flattenFull() const;

        /// @brief Returns a treestyle string representation of the DataType
        /// @details This is useful for debugging
        /// @return std::string
        std::string toString();
    };
} // namespace daq::impl
#endif // __DATATYPE_FACTORY_H__