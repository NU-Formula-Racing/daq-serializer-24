#ifndef __REGISTRY_H__
#define __REGISTRY_H__

#include <string>
#include <map>
#include <vector>
#include <iostream>

#include "parser.hpp"
#include "tokenizer.hpp"

namespace daqser::impl
{
    class Registry
    {
    public:
#if defined(NATIVE)
        std::string LATEST_SCHEMA_FILE = "./test/static/test_ultimate.drive";
#else
        std::string LATEST_SCHEMA_FILE = "latest_schema.drive";
#endif

#if defined(NATIVE)
        std::vector<std::string> REGISTERED_SCHEMA_FILES = {
            "./test/static/demo.drive",
            "./test/static/test_cyclic_advanced.drive",
            "./test/static/test_ultimate.drive",
        };
#else
        std::vector<std::string> REGISTERED_SCHEMA_FILES = {"schema.drive"};
#endif

        Registry() = default;

        void Initialize()
        {
            schemaRegistry.clear();

            // also add the latest schema file, just in case
            REGISTERED_SCHEMA_FILES.push_back(LATEST_SCHEMA_FILE);

            Parser parser;
            for (std::string schemaFile : REGISTERED_SCHEMA_FILES)
            {
                Tokenizer tokenizer(schemaFile);
                std::vector<Token> tokens = tokenizer.tokenize();
                Schema schema;
                Parser::ParsingResult res = parser.buildSchema(tokens, schema, true);

                if (res.isValid)
                {
                    SchemaMetadata metadata = {schema.schemaName, schema.versionNumber};
                    schemaRegistry[metadata] = schemaFile;
                }
                else
                {
                    std::cerr << "Error parsing schema file: " << schemaFile << std::endl;
                    std::cerr << res.message.str() << std::endl;
                }
            }

            std::cout << "Schema registry initialized with " << schemaRegistry.size() << " schemas" << std::endl;
        }

        Schema getSchema(std::string schemaName, int* versionNumber)
        {
            SchemaMetadata metadata = {schemaName, versionNumber};

            if (schemaRegistry.find(metadata) == schemaRegistry.end())
            {
                std::cerr << "Schema not found: " << schemaName << " v" << versionNumber << std::endl;
                return Schema();
            }

            std::string schemaFile = schemaRegistry[metadata];
            Parser parser;
            Tokenizer tokenizer(schemaFile);
            std::vector<Token> tokens = tokenizer.tokenize();
            Schema schema;
            Parser::ParsingResult res = parser.buildSchema(tokens, schema, false);

            if (res.isValid)
            {
                return schema;
            }
            else
            {
                std::cerr << "Error parsing schema file: " << schemaFile << std::endl;
                std::cerr << res.message.str() << std::endl;
                return Schema();
            }
        }

        Schema curSchema()
        {
            Tokenizer tokenizer(LATEST_SCHEMA_FILE);
            std::vector<Token> tokens = tokenizer.tokenize();
            Schema schema;
            Parser parser;
            Parser::ParsingResult res = parser.buildSchema(tokens, schema, false);

            if (res.isValid)
            {
                return schema;
            }
            else
            {
                std::cerr << "Error parsing schema file: " << LATEST_SCHEMA_FILE << std::endl;
                std::cerr << res.message.str() << std::endl;
                return Schema();
            }

            return schema;
        }

        int numSchemas()
        {
            return schemaRegistry.size();
        }

    private:
        struct SchemaMetadata
        {
            std::string schemaName;
            int *versionNumber;

            bool operator<(const SchemaMetadata &other) const
            {
                if (schemaName != other.schemaName)
                {
                    return schemaName < other.schemaName;
                }
                return *versionNumber < *other.versionNumber;
            }
        };

        std::map<SchemaMetadata, std::string> schemaRegistry;
    };
} // namespace daqser::impl

#endif // __REGISTRY_H__