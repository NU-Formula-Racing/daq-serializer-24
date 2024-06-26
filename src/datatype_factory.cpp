#include <string>
#include <map>
#include <memory>
#include <stdexcept>
#include <iostream>
#include <string.h>
#include <type_traits>

#include "datatype_factory.hpp"

using namespace daqser::impl;

#pragma region Field

// STATIC METHODS
Field Field::emptyField(const std::string &name, FieldType type)
{
    Field field;
    field.name = name;
    field.predefined = false;
    field.type = type;

    // get the size of the field
    switch (type)
    {
    case FieldType::INT:
        field.value = 0;
        field.size = sizeof(int);
        break;
    case FieldType::FLOAT:
        field.value = 0.0f;
        field.size = sizeof(float);
        break;
    case FieldType::BOOL:
        field.value = false;
        field.size = sizeof(bool);
        break;
    case FieldType::STRING:
        field.value = std::string("");
        field.size = 1; // default size of string
        break;
    case FieldType::VERSION:
        field.value = Value(new int[3]{0, 0, 0});
        field.size = sizeof(int[3]);
        break;
    case FieldType::LONG:
        field.value = 0L;
        field.size = sizeof(long);
        break;
    case FieldType::BYTE:
        field.value = (uint8_t)0;
        field.size = sizeof(uint8_t);
        break;
    default:
        // throw std::invalid_argument("Invalid type for field -- must be int, float, bool, string, version or custom");
        field.size = 0;
        std::cout << "Invalid type for field -- must be int, float, bool, string, version or custom" << std::endl;
    }

    field.value.valueSize = field.size;
    return field;
}

std::string Field::fieldTypeToString(FieldType type)
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
    case FieldType::LONG:
        return "long";
    case FieldType::BYTE:
        return "byte";
    default:
        // throw std::invalid_argument("Invalid type for field -- must be int, float, bool, string, version or custom");
        std::cout << "Invalid type for field -- must be int, float, bool, string, version or custom" << std::endl;
        return "invalid";
    }
}

// CONSTRUCTORS
Field::Field(const Field &other)
{
    this->name = other.name;
    this->predefined = other.predefined;
    this->type = other.type;
    this->size = other.size;
    // copy the value over
    this->value = Value(other.value);
    // std::cout << "Copied field with type " << fieldTypeToString(this->type) << " and size " << this->size << std::endl;
}

Field &Field::operator=(const Field &other)
{
    this->name = other.name;
    this->predefined = other.predefined;
    this->type = other.type;
    this->size = other.size;
    // copy the value over
    this->value = Value(other.value);
    // std::cout << "Copied field with type " << fieldTypeToString(this->type) << " and size " << this->size << std::endl;
    return *this;
}

bool Field::operator==(const Field &other) const
{
    return this->name == other.name &&
           this->predefined == other.predefined &&
           this->type == other.type &&
           this->size == other.size &&
           this->value == other.value;
}

std::string Field::toString() const
{
    std::stringstream ss;
    ss << "Field: " << name << std::endl;
    ss << "  Predefined: " << predefined << std::endl;
    ss << "  Type: " << fieldTypeToString(type) << std::endl;
    ss << "  Size: " << size << std::endl;
    // print value as hex for the given size
    ss << value.toString() << std::endl;

    return ss.str();
}

std::vector<std::uint8_t> Field::toBinary() const
{
    // convert the value to binary
    return value.toBinary();
}

std::string Field::toHumanReadable() const
{
    if (value.isValid() == false)
    {
        return "ERROR";
    }

    switch (type)
    {
    case FieldType::INT:
        return std::to_string(value.get<int>());
    case FieldType::FLOAT:
        return std::to_string(value.get<float>());
    case FieldType::BOOL:
        return value.get<bool>() ? "true" : "false";
    case FieldType::STRING:
        return "\""  + value.get<std::string>() + "\"";
    case FieldType::VERSION:
    {
        int *version = value.get<int *>();
        return std::to_string(version[0]) + "." + std::to_string(version[1]) + "." + std::to_string(version[2]);
    }
    case FieldType::LONG:
        return std::to_string(value.get<long>());
    case FieldType::BYTE:
        return std::to_string(value.get<uint8_t>());
    default:
        // throw std::invalid_argument("Invalid type for field -- must be int, float, bool, string, version or custom");
        std::cout << "Invalid type for field -- must be int, float, bool, string, version or custom" << std::endl;
        return "invalid";
    }
}

#pragma endregion

#pragma region DataMember

DataMember::DataMember(const Field &field)
{
    // malloc the field and copy it over
    this->memberPtr = malloc(sizeof(Field));
    memcpy(memberPtr, &field, sizeof(Field));
    this->isDataType = false;
};

DataMember::DataMember(const DataType &dataType)
{
    // malloc the field and copy it over
    this->memberPtr = malloc(sizeof(DataType));
    memcpy(memberPtr, &dataType, sizeof(DataType));
    this->isDataType = true;
};

DataMember::DataMember(const DataMember &other)
{
    this->memberPtr = other.memberPtr;
    this->isDataType = other.isDataType;
}

DataMember &DataMember::operator=(const DataMember &other)
{
    this->memberPtr = other.memberPtr;
    this->isDataType = other.isDataType;
    return *this;
}

DataMember DataMember::operator[](const std::string &fieldName)
{
    if (!isDataType)
    {
        // throw std::invalid_argument("DataMember is a Field, not a DataType");
        std::cout << "DataMember is a Field, not a DataType" << std::endl;
        return DataMember();
    }

    DataType DataType = this->getDataType();
    return DataType.getMember(fieldName);
}

Field DataMember::getField()
{

    if (memberPtr == nullptr)
    {
        // throw std::invalid_argument("DataMember is null");
        std::cout << "DataMember is null" << std::endl;
        return Field();
    }

    if (isDataType)
    {
        DataType DataType = this->getDataType();
        std::stringstream ss;
        ss << "DataMember is a DataType, not a Field. DataType is: " << DataType.name;
        // throw std::invalid_argument(ss.str());
        std::cout << ss.str() << std::endl;
        return Field();
    }

    Field field = *(Field *)memberPtr;
    return field;
}

DataType DataMember::getDataType()
{
    if (memberPtr == nullptr)
    {
        // throw std::invalid_argument("DataMember is null");
        std::cout << "DataMember is null" << std::endl;
        return DataType();
    }

    if (!isDataType)
    {
        Field field = *(Field *)memberPtr;
        std::stringstream ss;
        ss << "DataMember is a Field, not a DataType. Field is: " << field.name;
        // throw std::invalid_argument(ss.str());
        std::cout << ss.str() << std::endl;
        return DataType();
    }

    return *(DataType *)memberPtr;
}

std::string DataMember::toString() const
{
    std::stringstream ss;
    if (isDataType)
    {
        ss << "DataType";
    }
    else
    {
        ss << "Field";
    }
    ss << " at " << memberPtr;

    return ss.str();
}

#pragma endregion

#pragma region DataType

DataType::DataType(const DataType &other)
{
    // std::cout << "DataType::DataType(const DataType &other)" << std::endl;
    this->name = other.name;
    this->size = other.size;
    this->fields = other.fields;
    this->customDataTypes = other.customDataTypes;
}

DataType &DataType::operator=(const DataType &other)
{
    // std::cout << "DataType::operator=(const DataType &other)" << std::endl;
    this->name = other.name;
    this->size = other.size;
    this->fields = other.fields;
    this->customDataTypes = other.customDataTypes;
    return *this;
}

bool DataType::operator==(const DataType &other) const
{
    return this->name == other.name &&
           this->size == other.size &&
           this->fields == other.fields &&
           this->customDataTypes == other.customDataTypes;
}

DataMember DataType::operator[](const std::string &fieldName) const
{
    return this->getMember(fieldName);
}

void DataType::addField(const Field &field)
{
    // copy the field over
    Field newField(field);
    this->fields[field.name] = newField;
    this->size += field.size;
};

void DataType::removeField(const std::string &fieldName)
{
    if (fields.find(fieldName) == fields.end())
    {
        // throw std::invalid_argument("Field does not exist");
        std::cout << "Field does not exist" << std::endl;
        return;
    }

    this->size -= fields[fieldName].size;
    this->fields.erase(fieldName);
};

void DataType::addCustomField(const std::string &fieldName, const DataType &dataType)
{
    // copy the dataType over
    DataType newDataType(dataType);
    this->customDataTypes[fieldName] = newDataType;
    this->size += dataType.size;
};

void DataType::removeCustomField(const std::string &fieldName)
{
    if (this->customDataTypes.find(fieldName) == this->customDataTypes.end())
    {
        // throw std::invalid_argument("Custom field does not exist");
        std::cout << "Custom field does not exist" << std::endl;
        return;
    }

    this->size -= customDataTypes[fieldName].size;
    this->customDataTypes.erase(fieldName);
};

std::shared_ptr<DataType> DataType::getCustomField(const std::string &fieldName) const
{
    if (this->customDataTypes.find(fieldName) == this->customDataTypes.end())
    {
        // throw std::invalid_argument("Custom field does not exist");
        std::cout << "Custom field does not exist" << std::endl;
        return std::make_shared<DataType>();
    }

    return std::make_shared<DataType>(this->customDataTypes.at(fieldName));
};

bool DataType::hasField(const std::string &fieldName) const
{
    return this->fields.find(fieldName) != this->fields.end() || this->customDataTypes.find(fieldName) != this->customDataTypes.end();
};

DataMember DataType::getMember(const std::string &fieldName) const
{
    // split the field name if it has a dot
    std::size_t dotIndex = fieldName.find(".");
    if (dotIndex != std::string::npos)
    {
        std::string customFieldName = fieldName.substr(0, dotIndex);
        std::string subFieldName = fieldName.substr(dotIndex + 1);
        if (this->customDataTypes.find(customFieldName) != this->customDataTypes.end())
        {
            return this->customDataTypes.at(customFieldName).getMember(subFieldName);
        }
        else
        {
            std::stringstream ss;
            ss << "Custom field " << customFieldName << " does not exist in DataType " << this->name;
            // throw std::invalid_argument(ss.str());
            std::cout << ss.str() << std::endl;
            return DataMember();
        }
    }

    if (this->fields.find(fieldName) != this->fields.end())
    {
        return DataMember(this->fields.at(fieldName));
    }
    else
    {
        std::stringstream ss;
        ss << "Field " << fieldName << " does not exist in DataType " << this->name;
        // throw std::invalid_argument(ss.str());
        std::cout << ss.str() << std::endl;
        return DataMember();
    }
};

std::map<std::string, DataMember> DataType::flatten() const
{
    std::map<std::string, DataMember> flatMembers;
    for (auto const &field : this->fields)
    {
        flatMembers[field.first] = DataMember(field.second);
    }
    for (auto const &customField : this->customDataTypes)
    {
        flatMembers[customField.first] = DataMember(customField.second);
    }

    return flatMembers;
};

std::map<std::string, Field> DataType::flattenFull() const
{
    // flattens the DataType into a map of field name to value
    std::map<std::string, Field> flattened;
    for (auto &field : this->fields)
    {
        flattened[field.first] = field.second;
    }

    // now add the custom data types
    for (auto &customDataType : this->customDataTypes)
    {
        std::map<std::string, Field> flattenedCustomDataType = customDataType.second.flattenFull();
        for (auto &field : flattenedCustomDataType)
        {
            // std::cout << "Adding field " << field.first << std::endl;
            flattened[customDataType.first + "." + field.first] = field.second;
        }
    }

    return flattened;
}

std::string DataType::toString()
{
    std::stringstream ss;
    ss << "DataType: " << this->name << std::endl;
    ss << "Size: " << this->size << std::endl;
    ss << "Fields: " << std::endl;
    std::map<std::string, Field> flattened = this->flattenFull();
    for (auto &field : flattened)
    {
        ss << "\t" << field.first << " : " << Field::fieldTypeToString(field.second.type) << std::endl;
    }

    return ss.str();
}

#pragma endregion