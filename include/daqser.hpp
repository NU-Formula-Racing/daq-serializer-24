#ifndef __DAQSER_H__
#define __DAQSER_H__

#include <string>

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

    void printSchema()
    {
        if (g_activeSchema == nullptr)
        {
            std::cerr << "No active schema" << std::endl;
            return;
        }

        std::cout << "Active schema: " << g_activeSchema->schemaName << " ";
        std::cout << g_activeSchema->versionNumber[0] << ".";
        std::cout << g_activeSchema->versionNumber[1] << ".";
        std::cout << g_activeSchema->versionNumber[2] << std::endl;
    }
}

#endif // __DAQSER_H__