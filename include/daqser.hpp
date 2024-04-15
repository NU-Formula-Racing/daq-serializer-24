#ifndef __DAQSER_H__
#define __DAQSER_H__

#include <string>
#include <vector>

#include "parser.hpp"
#include "tokenizer.hpp"
#include "registry.hpp"
#include "datatype_factory.hpp"

using namespace daqser::impl;

#define VERSION(major, minor, patch) {major, minor, patch}

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
            std::cerr << "No schemas registered. Make sure to call daqser::initialize() first!" << std::endl;
            return;
        }

        int version[] = VERSION(major, minor, patch);

        Schema schema = g_registry.getSchema(schemaName, version);

        if (schema.frameTemplate == nullptr)
        {
            std::cerr << "Schema not found: " << schemaName << " ";
            std::cerr << version[0] << "." << version[1] << "." << version[2] << std::endl;
            std::cerr << "Make that the schema is registered in the registry" << std::endl;
            return;
        }

        g_activeSchema = std::make_shared<Schema>(schema);
    }

    bool _validateRequest()
    {
        if (g_activeSchema == nullptr)
        {
            std::cerr << "daqser::No active schema." << std::endl;
            std::cerr << "Please ensure that you call daqser::initalize(), then set a schema before making any daqser method calls!" << std::endl;
            return false;
        }

        if (g_activeSchema->frameTemplate == NULL)
        {
            std::cerr << "daqser::Something went wrong when parsing your schema!" << std::endl;
            std::cerr << "Please correct your schema file!" << std::endl;
            return false;
        }

        return true;
    }

    void printSchema()
    {
        bool valid = _validateRequest();
        if (!valid) return;

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
}

#endif // __DAQSER_H__