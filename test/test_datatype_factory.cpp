#include <unity.h>

#include "testing_suite.hpp"
#include "datatype_factory.hpp"

void test_field_predefined_int(void)
{
    Field field("test", 123);
    TEST_ASSERT_EQUAL_INT(123, field.value);
    TEST_ASSERT_EQUAL_INT(sizeof(int), field.size);
}

void test_field_predefined_float(void)
{
    Field field("test", 123.456);
    TEST_ASSERT_EQUAL_FLOAT(123.456, field.value);
    TEST_ASSERT_EQUAL_INT(sizeof(float), field.size);
}

void test_field_predefined_bool(void)
{
    Field field("test", true);
    TEST_ASSERT_EQUAL_INT(true, field.value);
    TEST_ASSERT_EQUAL_INT(sizeof(bool), field.size);
}

void test_field_predefined_string(void)
{
    Field field("test", "hello world");
    TEST_ASSERT_EQUAL_STRING("hello world", field.value);
    TEST_ASSERT_EQUAL_INT(sizeof(std::string), field.size);
}

void test_field_predefined_version(void)
{
    int version[3] = {1, 2, 3};
    Field field("test", version);
    TEST_ASSERT_TRUE(version == field.value)
    TEST_ASSERT_EQUAL_INT(sizeof(int[3]), field.size);
}

void test_field_not_predefined_int(void)
{
    Field field("test", FieldType::INT);
    TEST_ASSERT_EQUAL_INT(0, field.value.intVal);
    TEST_ASSERT_FALSE(field.predefined);
    TEST_ASSERT_EQUAL_INT(sizeof(int), field.size);
}

void test_field_not_predefined_float(void)
{
    Field field("test", FieldType::FLOAT);
    TEST_ASSERT_EQUAL_FLOAT(0.0, field.value.floatValue);
    TEST_ASSERT_FALSE(field.predefined);
    TEST_ASSERT_EQUAL_INT(sizeof(float), field.size);
}

void test_field_not_predefined_bool(void)
{
    Field field("test", FieldType::BOOL);
    TEST_ASSERT_EQUAL_INT(false, field.value.boolValue);
    TEST_ASSERT_FALSE(field.predefined);
    TEST_ASSERT_EQUAL_INT(sizeof(bool), field.size);
}

void test_field_not_predefined_string(void)
{
    Field field("test", FieldType::STRING);
    TEST_ASSERT_EQUAL_STRING("", field.value.strVal.c_str());
    TEST_ASSERT_FALSE(field.predefined);
    TEST_ASSERT_EQUAL_INT(sizeof(std::string), field.size);
}

void test_field_not_predefined_version(void)
{
    Field field("test", FieldType::VERSION);
    TEST_ASSERT_EQUAL_INT(0, field.value.versionValue[0]);
    TEST_ASSERT_EQUAL_INT(0, field.value.versionValue[1]);
    TEST_ASSERT_EQUAL_INT(0, field.value.versionValue[2]);
    TEST_ASSERT_FALSE(field.predefined);
    TEST_ASSERT_EQUAL_INT(sizeof(int[3]), field.size);
}

void TestingSuite::runDataTypeFactoryTests()
{
    // field tests
    RUN_TEST(test_field_predefined_int);
    RUN_TEST(test_field_predefined_float);
    RUN_TEST(test_field_predefined_bool);
    RUN_TEST(test_field_predefined_string);
    RUN_TEST(test_field_predefined_version);
    RUN_TEST(test_field_not_predefined_int);
    RUN_TEST(test_field_not_predefined_float);
    RUN_TEST(test_field_not_predefined_bool);
    RUN_TEST(test_field_not_predefined_string);
    RUN_TEST(test_field_not_predefined_version);
}