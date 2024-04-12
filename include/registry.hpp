#ifndef __REGISTRY_H__
#define __REGISTRY_H__

#include <string>
#include <map>
#include <vector>

#include "parser.hpp"
#include "tokenizer.hpp"

namespace daq::impl
{
    class Registry
    {
    public:
        // These are configuration values that are set in the implementation file
        // See src/registry.cpp
        static std::string LATEST_SCHEMA_FILE;
        static std::vector<std::string> REGISTERED_SCHEMA_FILES;

        Registry();
        ~Registry();

        static void Initialize()
        {
            schemaRegistry.clear();

            // also add the latest schema file, just in case
            Registry::REGISTERED_SCHEMA_FILES.push_back(Registry::LATEST_SCHEMA_FILE);

            Parser parser;
            for (std::string schemaFile : Registry::REGISTERED_SCHEMA_FILES)
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

        Schema getSchema(std::string schemaName, int versionNumber)
        {
            SchemaMetadata metadata = {schemaName, &versionNumber};

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
            Tokenizer tokenizer(Registry::LATEST_SCHEMA_FILE);
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
                std::cerr << "Error parsing schema file: " << Registry::LATEST_SCHEMA_FILE << std::endl;
                std::cerr << res.message.str() << std::endl;
                return Schema();
            }

            return schema;
        }

    private:
        struct SchemaMetadata
        {
            std::string schemaName;
            int *versionNumber;
        };

        static std::map<SchemaMetadata, std::string> schemaRegistry;
    };
} // namespace daq::impl


#endif // __REGISTRY_H__