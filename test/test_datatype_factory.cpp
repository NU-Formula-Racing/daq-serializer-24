#include <unity.h>

#include "testing_suite.hpp"
#include "datatype_factory.hpp"

void test_field_predefined_int(void)
{
    Field field = Field::predfinedField("test", 123);
    TEST_ASSERT_TRUE(field.value == 123);
    TEST_ASSERT_TRUE(field.value.isValid());
    TEST_ASSERT_EQUAL_INT(sizeof(int), field.size);
}

void test_field_predefined_float(void)
{
    Field field = Field::predfinedField("test", 123.456f);
    TEST_ASSERT_TRUE(field.value == 123.456f);
    TEST_ASSERT_TRUE(field.value.isValid());
    TEST_ASSERT_EQUAL_INT(sizeof(float), field.size);
}

void test_field_predefined_bool(void)
{
    Field field = Field::predfinedField("test", true);
    TEST_ASSERT_TRUE(field.value == true);
    TEST_ASSERT_TRUE(field.value.isValid());
    TEST_ASSERT_EQUAL_INT(sizeof(bool), field.size);
}

void test_field_predefined_string(void)
{
    const char* str = "hello world! i am evan";
    Field field = Field::predfinedField("test", str);
    TEST_ASSERT_TRUE(field.value == "hello world! i am evan");
    TEST_ASSERT_TRUE(field.value.isValid());
    TEST_ASSERT_EQUAL_INT(sizeof(char*), field.size);
}

void test_field_predefined_version(void)
{
    int version[3] = {1, 2, 3};
    Field field = Field::predfinedField("test", version);
    TEST_ASSERT_TRUE(field.value == version);
    TEST_ASSERT_TRUE(field.value.isValid());
    TEST_ASSERT_EQUAL_INT(sizeof(int[3]), field.size);
}

void test_field_not_predefined_int(void)
{
    Field field = Field::emptyField("test", FieldType::INT);
    TEST_ASSERT_TRUE(field.value == 0);
    TEST_ASSERT_FALSE(field.predefined);
    TEST_ASSERT_FALSE(field.value.isValid());
    TEST_ASSERT_TRUE(sizeof(int) == field.size);
}

void test_field_not_predefined_float(void)
{
    Field field = Field::emptyField("test", FieldType::FLOAT);
    TEST_ASSERT_TRUE(field.value == 0.0f);
    TEST_ASSERT_FALSE(field.predefined);
    TEST_ASSERT_FALSE(field.value.isValid());
    TEST_ASSERT_EQUAL_INT(sizeof(float), field.size);
}

void test_field_not_predefined_bool(void)
{
    Field field = Field::emptyField("test", FieldType::BOOL);
    TEST_ASSERT_TRUE(field.value == false);
    TEST_ASSERT_FALSE(field.predefined);
    TEST_ASSERT_FALSE(field.value.isValid());
    TEST_ASSERT_EQUAL_INT(sizeof(bool), field.size);
}

void test_field_not_predefined_string(void)
{
    Field field = Field::emptyField("test", FieldType::STRING);
    // TODO: make this assertion pass
    // TEST_ASSERT_TRUE(field.value == "");
    TEST_ASSERT_FALSE(field.predefined);
    TEST_ASSERT_FALSE(field.value.isValid());
    TEST_ASSERT_EQUAL_INT(sizeof(char*), field.size);
}

void test_flat_data_type(void)
{
    Field floatField = Field::emptyField("float", FieldType::FLOAT);
    Field intField = Field::emptyField("int", FieldType::INT);
    std::size_t size = floatField.size + intField.size;
    DataType testType;

    testType.addField(floatField);
    testType.addField(intField);

    TEST_ASSERT_TRUE(testType.size == size);

    // test flattening
    std::map<std::string, DataMember> flatMembers = testType.flatten();
    TEST_ASSERT_TRUE(flatMembers.size() == 2);
    DataMember floatMember = flatMembers["float"];
    DataMember intMember = flatMembers["int"];

    // test that we get no errors converting the datamember to a field
    Field floatFieldFromMember = floatMember.getField();
    Field intFieldFromMember = intMember.getField();

    // now test that the fields are the is_same
    TEST_ASSERT_TRUE(floatFieldFromMember == floatField);
    TEST_ASSERT_TRUE(intFieldFromMember == intField);
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