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

    void initialize()
    {
        g_registry = Registry();
        g_parser = Parser();

        g_registry.initialize();
    }

    void setSchema(std::string schemaName, int major, int minor, int patch)
    {
        if (g_registry.numSchemas() == 0)
        {
            std::cout << "No schemas registered. Make sure to call daqser::initialize() first!" << std::endl;
            return;
        }

        int version[] = VERSION(major, minor, patch);

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

    Schema getSchema()
    {
        if (!_validateRequest())
            return Schema();
        return *g_activeSchema;
    }

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

    void set(std::string field, std::string value)
    {
        bool valid = _validateRequest();
        if (!valid)
            return;

        g_activeSchema->frameTemplate->set(field, value);
    }

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

    void deserializeFrame(std::vector<std::uint8_t> frame)
    {
        bool valid = _validateRequest();
        if (!valid)
            return;

        g_activeSchema->frameTemplate->deserializeFrame(frame);
    }
}

#endif // __DAQSER_H__