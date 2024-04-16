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

    // now we will set some values
    daqser::set<long>("timestamp.timeSince1990", 1234567890);
    daqser::set("ambientTemp", 25.0f);

    // now serialize the frame
    std::vector<std::uint8_t> frameSer = daqser::serializeFrame();
    for (std::uint8_t byte : frameSer)
    {
        std::cout << (int)byte << " ";
    }

    // now lets change the values
    daqser::set<long>("timestamp.timeSince1990", 1234567891);
    daqser::set("ambientTemp", 26.0f);

    // now check that the values have changed
    TEST_ASSERT_EQUAL(1234567891, daqser::get<long>("timestamp.timeSince1990"));
    TEST_ASSERT_EQUAL(26.0f, daqser::get<float>("ambientTemp"));

    // now deserialize the frame
    daqser::deserializeFrame(frameSer);

    // now check that the values have changed back
    TEST_ASSERT_EQUAL(1234567890, daqser::get<long>("timestamp.timeSince1990"));
    TEST_ASSERT_EQUAL(25.0f, daqser::get<float>("ambientTemp"));

    // now ensure that the api does not allow setting of nonexistent fields
    // but also does not crash
    daqser::set("nonexistent", 1);
    TEST_ASSERT_EQUAL(0, daqser::get<int>("nonexistent"));
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