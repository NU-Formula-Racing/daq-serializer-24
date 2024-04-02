#ifndef __FRAME_H__
#define __FRAME_H__

/// @brief
/// A binary frame is the base unit of the daq serial stream
/// After parsing the .drive file, a FrameTemplate is created, which is used to create Frames
/// A frame template is uses a DataType to define the structure of the frame

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <stdexcept>
#include <iostream>
#include <string.h>
#include <type_traits>
#include <sstream>
#include <algorithm>

#include "datatype_factory.hpp"

namespace daq::impl
{

#pragma region Frame

    /// @brief A binary frame is the base unit of the daq serial stream
    struct Frame
    {
        std::vector<std::uint8_t> data;
    };

    /// @brief A frame template is uses a DataType to define the structure of the frame
    class FrameTemplate
    {
    public:
        FrameTemplate() {}
        FrameTemplate(const DataType &type) : _baseType(std::make_shared<DataType>(type))
        {
            // std::cout << "Building frame template" << std::endl;
            // std::cout << "Type: " << _baseType->toString() << std::endl;
            this->_buildTemplate();
        }

        /// @brief Sets a value in the frame template so that it can be used to build frames
        /// @tparam T The type of the value to set
        /// @param fieldName The name of the field to set -- to access nested fields, use dot notation, for example: "innerField.field"
        template <typename T>
        void set(std::string fieldName, T value)
        {
            // Check if the field exists
            if (std::find(this->_fieldNames.begin(), this->_fieldNames.end(), fieldName) == this->_fieldNames.end())
            {
                std::stringstream err;
                err << "Field does not exist in frame template: " << fieldName;
                throw std::invalid_argument(err.str());
            }

            // Get the index of the field
            auto index = std::distance(this->_fieldNames.begin(), std::find(this->_fieldNames.begin(), this->_fieldNames.end(), fieldName));

            // Set the value
            this->_values[index] = value;
        }

        /// @brief Gets a value from the frame template
        /// @tparam T The type of the value to get
        /// @param fieldName The name of the field to get -- to access nested fields, use dot notation, for example: "innerField.field"
        /// @return The value of the field
        template <typename T>
        T get(std::string fieldName) const
        {
            // Get the value
            std::cout << "Getting value " << fieldName << std::endl;
            // Check if the field exists
            if (std::find(this->_fieldNames.begin(), this->_fieldNames.end(), fieldName) == this->_fieldNames.end())
            {
                std::stringstream err;
                err << "Field does not exist in frame template: " << fieldName;
                throw std::invalid_argument(err.str());
            }

            std::cout << "Field exists" << std::endl;
            // Get the index of the field
            auto index = std::distance(this->_fieldNames.begin(), std::find(this->_fieldNames.begin(), this->_fieldNames.end(), fieldName));
            std::cout << "Index: " << index << std::endl;
            return this->_values[index].get<T>();
        }

        std::vector<std::uint8_t> buildFrame() const
        {
            std::vector<std::uint8_t> frame;

            // Iterate through the fields and add them to the frame
            for (auto &value : this->_values)
            {
                std::vector<std::uint8_t> fieldBytes = value.toBinary();
                frame.insert(frame.end(), fieldBytes.begin(), fieldBytes.end());
            }

            return frame;
        }

        std::vector<std::string> getFieldNames() const
        {
            return this->_fieldNames;
        }

        bool isField(std::string fieldName) const
        {
            // find the field name in the vector of field names
            return std::find(this->_fieldNames.begin(), this->_fieldNames.end(), fieldName) != this->_fieldNames.end();
        }

        Field getField(std::string fieldName) const
        {
            // Check if the field exists
            if (std::find(this->_fieldNames.begin(), this->_fieldNames.end(), fieldName) == this->_fieldNames.end())
            {
                std::stringstream err;
                err << "Field does not exist in frame template: " << fieldName;
                throw std::invalid_argument(err.str());
            }
            
            return _baseType->getMember(fieldName).getField();
        }

    private:
        std::shared_ptr<DataType> _baseType;

        // Map of field names to values
        // Split into two vectors to ensure that the order of the fields is preserved
        // The fields will be ordered by alphabetical order of the field names
        std::vector<Value> _values;
        std::vector<std::string> _fieldNames;

        /// @brief Builds the template from the dataType
        /// @details This method is called when the template is created
        void _buildTemplate()
        {
            std::map<std::string, Field> flattenedFields = this->_baseType->flattenFull();
            // std::cout << "Flattening from:" << std::endl;
            std::cout << this->_baseType->toString() << std::endl;
            for (auto &field : flattenedFields)
            {
                // std::cout << "field: " << field.first << std::endl;
                this->_fieldNames.push_back(field.first);
                this->_values.push_back(field.second.value);
            }
        }
    };

#pragma endregion

} // namespace daq::impl

#endif // __FRAME_H__