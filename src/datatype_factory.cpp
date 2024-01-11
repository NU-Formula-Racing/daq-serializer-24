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
    if (isDataType)
    {
        throw std::invalid_argument("DataMember is a DataType, not a Field");
    }

    Field field;
    memcpy(&field, memberPtr, sizeof(Field));
    return field;
}

DataType DataMember::getDataType()
{
    if (!isDataType)
    {
        throw std::invalid_argument("DataMember is a Field, not a DataType");
    }

    DataType dataType;
    memcpy(&dataType, memberPtr, sizeof(DataType));
    return dataType;
}
