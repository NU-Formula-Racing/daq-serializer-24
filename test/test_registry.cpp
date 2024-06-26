#define NATIVE
#include <unity.h>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>

#include "testing_suite.hpp"
#include "registry.hpp"

using namespace daqser::impl;

void test_registry_initialize()
{
    Registry registry;
    registry.initialize();
    TEST_ASSERT_EQUAL(6, registry.numSchemas());
}   

void test_registry_get_schema()
{
    Registry registry;
    registry.initialize();
    int version[] = { 1, 0, 1 };
    Schema schema = registry.getSchema("df", version);
    TEST_ASSERT_EQUAL_STRING("df", schema.schemaName.c_str());
    for (int i = 0; i < 3; i++)
    {
        TEST_ASSERT_EQUAL(version[i], schema.versionNumber[i]);
    }
    TEST_ASSERT_TRUE_MESSAGE(schema.frameTemplate != nullptr, "Frame template is null");
}

void test_registry_get_cur_schema()
{
    // # meta information about the serialization method
    // meta
    // {
    //     # required meta-information (denoted with the '.')
    //     .schema : "test-ultimate";
    //     .version : 1.0.0;
    // }

    Registry registry;
    registry.initialize();
    Schema schema = registry.curSchema();
    TEST_ASSERT_EQUAL_STRING("test-ultimate", schema.schemaName.c_str());
    int version[] = { 1, 0, 0 };
    for (int i = 0; i < 3; i++)
    {
        TEST_ASSERT_EQUAL(version[i], schema.versionNumber[i]);
    }
    TEST_ASSERT_TRUE_MESSAGE(schema.frameTemplate != nullptr, "Frame template is null");
}

void TestingSuite::runRegistryTests()
{
    RUN_TEST(test_registry_initialize);
    RUN_TEST(test_registry_get_schema);
    RUN_TEST(test_registry_get_cur_schema);
}