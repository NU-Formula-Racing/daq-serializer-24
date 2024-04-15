#define NATIVE
#include <unity.h>
#include <string>
#include <sstream>
#include <iostream>

#include "daqser.hpp"
#include "testing_suite.hpp"

void test_basic_use(void)
{
    daqser::initialize();
    daqser::setSchema("test-api-basic", 1, 0, 1);
    daqser::printSchema();

    std::vector<std::uint8_t> schemaSer = daqser::serializeSchema();
    for (std::uint8_t byte : schemaSer)
    {
        std::cout << (char)byte;
    }
    std::cout << std::endl;


    // now try to deserialize the schema
    std::string schemaName = "test-api-basic";
    int version[] = {1, 0, 1};

    daqser::setSchemaFromSerializedMeta(schemaSer);
    Schema schema = daqser::getSchema();
    TEST_ASSERT_EQUAL_STRING(schemaName.c_str(), schema.schemaName.c_str());
    TEST_ASSERT_EQUAL_INT(version[0], schema.versionNumber[0]);
    TEST_ASSERT_EQUAL_INT(version[1], schema.versionNumber[1]);
    TEST_ASSERT_EQUAL_INT(version[2], schema.versionNumber[2]);
    TEST_ASSERT_TRUE_MESSAGE(schema.frameTemplate != nullptr, "Frame template is null");

    daqser::printSchema();

}

/// @brief I would imagine that the logger project would use these aspects of the API
void test_logger_sim(void)
{

}

/// @brief I would imagine that the wireless project would use these aspects of the API
void test_wireless_sim(void)
{

}


void TestingSuite::runApiTests()
{
    RUN_TEST(test_basic_use);
    RUN_TEST(test_logger_sim);
    RUN_TEST(test_wireless_sim);
}