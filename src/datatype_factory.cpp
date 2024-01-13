#include <string>
#include <map>
#include <memory>
#include <stdexcept>
#include <iostream>
#include <string.h>
#include <type_traits>

#include "datatype_factory.hpp"

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
        throw std::invalid_argument("DataMember is a Field, not a DataType");
    }

    DataType DataType = this->getDataType();
    return DataType.getMember(fieldName);
}

Field DataMember::getField()
{
    if (memberPtr == nullptr)
    {
        throw std::invalid_argument("DataMember is null");
    }

    if (isDataType)
    {
        DataType DataType = this->getDataType();
        std::stringstream ss;
        ss << "DataMember is a DataType, not a Field. DataType is: " << DataType.name;
        throw std::invalid_argument(ss.str());
    }

    Field field = *(Field *)memberPtr;
    return field;
}

DataType DataMember::getDataType()
{
    if (memberPtr == nullptr)
    {
        throw std::invalid_argument("DataMember is null");
    }

    if (!isDataType)
    {
        Field field = *(Field *)memberPtr;
        std::stringstream ss;
        ss << "DataMember is a Field, not a DataType. Field is: " << field.name;
        throw std::invalid_argument(ss.str());
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
