#include <unity.h>

#include "testing_suite.hpp"
#include "datatype_factory.hpp"

void test_field_predefined_int(void)
{
    Field field = Field::predfinedField("test", 123);
    TEST_ASSERT_TRUE(field.value == 123);
    TEST_ASSERT_EQUAL_INT(sizeof(int), field.size);
}

void test_field_predefined_float(void)
{
    Field field = Field::predfinedField("test", 123.456f);
    TEST_ASSERT_TRUE(field.value == 123.456f);
    TEST_ASSERT_EQUAL_INT(sizeof(float), field.size);
}

void test_field_predefined_bool(void)
{
    Field field = Field::predfinedField("test", true);
    TEST_ASSERT_TRUE(field.value == true);
    TEST_ASSERT_EQUAL_INT(sizeof(bool), field.size);
}

void test_field_predefined_string(void)
{
    const char* str = "hello";
    Field field = Field::predfinedField("test", str);
    TEST_ASSERT_TRUE(field.value == "hello");
    TEST_ASSERT_EQUAL_INT(sizeof(char*), field.size);
}

void test_field_predefined_version(void)
{
    int version[3] = {1, 2, 3};
    Field field = Field::predfinedField("test", version);
    TEST_ASSERT_TRUE(field.value == version);
    TEST_ASSERT_EQUAL_INT(sizeof(int[3]), field.size);
}

void test_field_not_predefined_int(void)
{
    Field field = Field::emptyField("test", FieldType::INT);
    TEST_ASSERT_TRUE(field.value == 0);
    TEST_ASSERT_FALSE(field.predefined);
    TEST_ASSERT_TRUE(sizeof(int) == field.size);
}

void test_field_not_predefined_float(void)
{
    Field field = Field::emptyField("test", FieldType::FLOAT);
    TEST_ASSERT_TRUE(field.value == 0.0f);
    TEST_ASSERT_FALSE(field.predefined);
    TEST_ASSERT_EQUAL_INT(sizeof(float), field.size);
}

void test_field_not_predefined_bool(void)
{
    Field field = Field::emptyField("test", FieldType::BOOL);
    TEST_ASSERT_TRUE(field.value == false);
    TEST_ASSERT_FALSE(field.predefined);
    TEST_ASSERT_EQUAL_INT(sizeof(bool), field.size);
}

void test_field_not_predefined_string(void)
{
    Field field = Field::emptyField("test", FieldType::STRING);
    TEST_ASSERT_TRUE(field.value == "");
    TEST_ASSERT_FALSE(field.predefined);
    TEST_ASSERT_EQUAL_INT(sizeof(std::string), field.size);
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
}