#ifndef __DAQSER_H__
#define __DAQSER_H__

#include <string>
#include <vector>
#include <tuple>

#include "parser.hpp"
#include "tokenizer.hpp"
#include "registry.hpp"
#include "datatype_factory.hpp"

using namespace daqser::impl;

#define VERSION(major, minor, patch) \
    {                                \
        major, minor, patch          \
    }

namespace daqser
{
    // global state variables
    std::shared_ptr<Schema> g_activeSchema;
    Registry g_registry;
    Parser g_parser;

    /// @brief Initializes the daqser library, must be called before any other daqser method
    void initialize()
    {
        g_registry = Registry();
        g_parser = Parser();

        g_registry.initialize();
    }

    /// @brief Sets the active schema to the schema with the given name and version 
    void setSchema(std::string schemaName, int major, int minor, int patch)
    {
        if (g_registry.numSchemas() == 0)
        {
            std::cout << "No schemas registered. Make sure to call daqser::initialize() first!" << std::endl;
            return;
        }

        int version[] = VERSION(major, minor, patch);

        std::cout << "Setting schema: " << schemaName << " ";
        std::cout << version[0] << "." << version[1] << "." << version[2] << std::endl;

        Schema schema = g_registry.getSchema(schemaName, version);

        if (schema.schemaName == "")
        {
            std::cout << "Schema not found: " << schemaName << " ";
            std::cout << version[0] << "." << version[1] << "." << version[2] << std::endl;
            std::cout << "Make that the schema is registered in the registry" << std::endl;
            return;
        }

        g_activeSchema = std::make_shared<Schema>(schema);
    }

    /// @brief Sets the active schema from a serialized version of the schema metadata
    /// @param serializedSchemaMeta The serialized schema metadata
    void setSchemaFromSerializedMeta(std::vector<std::uint8_t> serializedSchemaMeta)
    {
        std::tuple<std::string, int *> deserialize = Schema::deserialize(serializedSchemaMeta);
        std::string schemaName = std::get<0>(deserialize);
        int *version = std::get<1>(deserialize);

        if (schemaName == "" || version == nullptr)
        {
            std::cout << "Error deserializing schema metadata" << std::endl;
            return;
        }

        setSchema(schemaName, version[0], version[1], version[2]);
    }

    /// @brief Sets the active schema to the latest schema registered in the registry (set by an environment variable)
    void setSchemaToCur()
    {
        if (g_registry.numSchemas() == 0)
        {
            std::cout << "No schemas registered. Make sure to call daqser::initialize() first!" << std::endl;
            return;
        }

        Schema schema = g_registry.curSchema();

        if (schema.schemaName == "")
        {
            std::cout << "Schema not found: " << schema.schemaName << " ";
            std::cout << schema.versionNumber[0] << "." << schema.versionNumber[1] << "." << schema.versionNumber[2] << std::endl;
            std::cout << "Make that the schema is registered in the registry" << std::endl;
            return;
        }

        g_activeSchema = std::make_shared<Schema>(schema);
    }

    /// @brief Sets the active schema from the contents of a schema file
    /// @param driveFile The contents of the schema file, so drive code
    void setSchema(const std::string &driveFile)
    {
        Tokenizer tokenizer(driveFile);
        std::vector<Token> tokens = tokenizer.tokenizeFile();
        Schema schema;
        Parser::ParsingResult res = g_parser.buildSchema(tokens, schema, false);

        if (res.isValid)
        {
            g_activeSchema = std::make_shared<Schema>(schema);
        }
        else
        {
            std::cout << "Error parsing schema file: " << driveFile << std::endl;
            std::cout << res.message.str() << std::endl;
        }
    }

    /// @brief PRIVATE: Validates that the request is valid
    /// @return True if the request is valid, false otherwise
    bool _validateRequest()
    {
        if (g_activeSchema == nullptr)
        {
            std::cout << "daqser::No active schema." << std::endl;
            std::cout << "Please ensure that you call daqser::initalize(), then set a schema before making any daqser method calls!" << std::endl;
            return false;
        }

        if (g_activeSchema->schemaName == "")
        {
            std::cout << "daqser::Something went wrong when parsing your schema!" << std::endl;
            std::cout << "Please correct your schema file!" << std::endl;
            return false;
        }

        return true;
    }

    /// @brief Gets the active schema
    Schema getSchema()
    {
        if (!_validateRequest())
            return Schema();
        return *g_activeSchema;
    }

    /// @brief Prints the active schema to the console
    void printSchema()
    {
        bool valid = _validateRequest();
        if (!valid)
            return;

        std::cout << "Active schema: " << g_activeSchema->schemaName << " ";
        std::cout << g_activeSchema->versionNumber[0] << ".";
        std::cout << g_activeSchema->versionNumber[1] << ".";
        std::cout << g_activeSchema->versionNumber[2] << std::endl;
    }

    /// @brief Serializes the active schema to a byte array
    std::vector<std::uint8_t> serializeSchema()
    {
        bool valid = _validateRequest();
        if (!valid)
        {
            std::vector<std::uint8_t> nothing;
            return nothing;
        }

        return g_activeSchema->serialize();
    }

    /// @brief Sets the value of a field in the active schema
    /// @param field The field to set
    /// @param value The value to set the field to
    void set(std::string field, std::string value)
    {
        bool valid = _validateRequest();
        if (!valid)
            return;

        g_activeSchema->frameTemplate->set(field, value);
    }

    /// @brief Sets the value of a field in the active schema
    /// @param field The field to set
    template <typename T>
    void set(std::string field, T value)
    {
        bool valid = _validateRequest();
        if (!valid)
            return;

        // make sure that the field exists
        if (!g_activeSchema->frameTemplate->isField(field))
        {
            std::cout << "Field does not exist: " << field << std::endl;
            return;
        }

        g_activeSchema->frameTemplate->set(field, value);
    }

    /// @brief Gets the value of a field in the active schema
    /// @param field The field to get
    template <typename T>
    T get(std::string field)
    {
        bool valid = _validateRequest();
        if (!valid)
            return T();

        // make sure that the field exists
        if (!g_activeSchema->frameTemplate->isField(field))
        {
            std::cout << "Field does not exist: " << field << std::endl;
            return T();
        }

        return g_activeSchema->frameTemplate->get<T>(field);
    }

    /// @brief Serializes the active schema into the standard, compact binary format
    std::vector<std::uint8_t> serializeFrame()
    {
        bool valid = _validateRequest();
        if (!valid)
        {
            std::vector<std::uint8_t> nothing;
            return nothing;
        }

        return g_activeSchema->frameTemplate->serializeFrame();
    }

    /// @brief Serializes the active schema into a JSON string
    /// @param includeFieldNames Whether to include field names in the JSON string
    /// @param includeTypeNames Whether to include type names in the JSON string
    std::string serializeFrameToJson(bool includeFieldNames = true, bool includeTypeNames = true)
    {
        bool valid = _validateRequest();
        if (!valid)
            return "";

        return g_activeSchema->frameTemplate->serializeFrameToJson(includeFieldNames, includeTypeNames);
    }

    /// @brief Deserializes the frame, and stors the result in the active schema
    /// @param frame The serialized frame, in the standard, compact binary format
    void deserializeFrame(std::vector<std::uint8_t> frame)
    {
        bool valid = _validateRequest();
        if (!valid)
            return;

        g_activeSchema->frameTemplate->deserializeFrame(frame);
    }

    /// @brief Checks if a schema with the given name and version exists in the registry
    bool hasSchema(std::string name, int major, int minor, int patch)
    {
        if (!_validateRequest()) return false;
        return g_registry.hasSchema(name, major, minor, patch);
    }

    /// @brief Gets the drive file contents of the current schema
    std::string getDriveContents()
    {
        if (!_validateRequest()) return "";
        return g_registry.getDriveContents(g_activeSchema->schemaName, g_activeSchema->versionNumber);
    }
}

#endif // __DAQSER_H__