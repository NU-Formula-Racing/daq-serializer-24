#ifndef __DAQSER_H__
#define __DAQSER_H__

#include <string>

#include "parser.hpp"
#include "tokenizer.hpp"
#include "registry.hpp"
#include "datatype_factory.hpp"

using namespace daqser::impl;

namespace daqser
{
    // global state variables
    std::shared_ptr<Schema> g_activeSchema;
    Registry g_registry;
    Parser g_parser;

    void Initialize()
    {
        g_registry = Registry();
        g_parser = Parser();

        g_registry.Initialize();
    }

    void SetSchema(std::string schemaName, int *version)
    {
        // Schema 
    }
}

#endif // __DAQSER_H__