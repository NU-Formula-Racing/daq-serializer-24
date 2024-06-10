#include <unity.h>

#include "testing_suite.hpp"
#include "datatype_factory.hpp"

using namespace daqser::impl;

void test_value_int(void)
{
    Value value = 123;
    TEST_ASSERT_TRUE(value == 123);
    TEST_ASSERT_TRUE(value.get<int>() == 123);
    TEST_ASSERT_TRUE(value.isValid());
}

void test_value_float(void)
{
    Value value = 123.456f;
    TEST_ASSERT_TRUE(value == 123.456f);
    TEST_ASSERT_TRUE(value.get<float>() == 123.456f);
    TEST_ASSERT_TRUE(value.isValid());
}

void test_value_bool(void)
{
    Value value = true;
    TEST_ASSERT_TRUE(value == true);
    TEST_ASSERT_TRUE(value.get<bool>() == true);
    TEST_ASSERT_TRUE(value.isValid());
}

void test_value_string(void)
{
    Value value = "hello world! i am evan";
    TEST_ASSERT_TRUE(value == "hello world! i am evan");
    std::cout << "RAH" << std::endl;
    TEST_ASSERT_TRUE(value.get<std::string>() == "hello world! i am evan");
    TEST_ASSERT_TRUE(value.isValid());
}

void test_value_byte(void)
{
    Value value = (std::uint8_t)0x12;
    TEST_ASSERT_TRUE(value == (std::uint8_t)0x12);
    TEST_ASSERT_TRUE(value.get<std::uint8_t>() == (std::uint8_t)0x12);
    TEST_ASSERT_TRUE(value.isValid());
}

void test_value_version(void)
{
    int version[3] = {1, 2, 3};
    Value value = version;
    TEST_ASSERT_TRUE(value == version);
    int *versionPtr = value.get<int *>();
    TEST_ASSERT_TRUE(versionPtr[0] == 1);
    TEST_ASSERT_TRUE(versionPtr[1] == 2);
    TEST_ASSERT_TRUE(versionPtr[2] == 3);
    TEST_ASSERT_TRUE(value.isValid());
}

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
    const char *str = "hello world! i am evan";
    Field field = Field::predfinedField("test", str);
    TEST_ASSERT_TRUE(field.value == "hello world! i am evan");
    TEST_ASSERT_TRUE(field.value.isValid());
    TEST_ASSERT_EQUAL_INT(sizeof(char *), field.size);
}

void test_field_predefined_version(void)
{
    int version[3] = {1, 2, 3};
    Field field = Field::predfinedField("test", version);
    TEST_ASSERT_TRUE(field.value == version);
    TEST_ASSERT_TRUE(field.value.isValid());
    TEST_ASSERT_EQUAL_INT(sizeof(int[3]), field.size);
}

void test_field_predefined_byte(void)
{
    std::uint8_t byte = 0x12;
    Field field = Field::predfinedField("test", byte);
    TEST_ASSERT_TRUE(field.value == byte);
    TEST_ASSERT_TRUE(field.value.isValid());
    TEST_ASSERT_EQUAL_INT(sizeof(std::uint8_t), field.size);

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
    TEST_ASSERT_EQUAL_INT(sizeof(char *), field.size);
}

void test_field_not_predefined_byte(void)
{
    Field field = Field::emptyField("test", FieldType::BYTE);
    TEST_ASSERT_TRUE(field.value == 0);
    TEST_ASSERT_FALSE(field.predefined);
    TEST_ASSERT_FALSE(field.value.isValid());
    TEST_ASSERT_EQUAL_INT(sizeof(std::uint8_t), field.size);
}

void test_value_copy_constructor(void)
{
    Value value = 123;
    Value valueCopy = Value(value);
    TEST_ASSERT_TRUE_MESSAGE(valueCopy == 123, "Value copy obtained via copy constructor is not 123");

    // now try copying via pointer
    void *valuePtr = &value;
    Value value2 = *(Value *)valuePtr;
    TEST_ASSERT_TRUE_MESSAGE(value2 == 123, "Value copy obtained via pointer is not 123");
}

void test_field_copy_constructor(void)
{
    Field field = Field::predfinedField("test", 123);
    Field fieldCopy = Field(field);
    // std::cout << "field: " << field.toString() << std::endl;
    // std::cout << "fieldCopy: " << fieldCopy.toString() << std::endl;
    TEST_ASSERT_TRUE_MESSAGE(fieldCopy.name == "test", "Field copy name is not test");
    TEST_ASSERT_TRUE_MESSAGE(fieldCopy.type == FieldType::INT, "Field copy type is not INT");
    TEST_ASSERT_TRUE_MESSAGE(fieldCopy.predefined == true, "Field copy is not predefined");
    TEST_ASSERT_TRUE_MESSAGE(fieldCopy.value == field.value, "Field copy value does not equal field value");
    TEST_ASSERT_TRUE_MESSAGE(fieldCopy.value == 123, "Field copy value is not 123");
    TEST_ASSERT_TRUE_MESSAGE(fieldCopy.value.isValid(), "Field copy value is not valid");
    TEST_ASSERT_EQUAL_INT(sizeof(int), fieldCopy.size);
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
    TEST_ASSERT_TRUE_MESSAGE(flatMembers.size() == 2, "Flat members size is not 2");
    // test that we get no errors converting the datamember to a field
    try
    {
        DataMember floatMember = flatMembers["float"];
        DataMember intMember = flatMembers["int"];
        Field floatFieldFromMember = floatMember.getField();
        Field intFieldFromMember = intMember.getField();
        // now test that the fields are the is_same
        TEST_ASSERT_TRUE_MESSAGE(floatFieldFromMember == floatField, "Float fields are not the same");
        TEST_ASSERT_TRUE_MESSAGE(intFieldFromMember == intField, "Int fields are not the same");
    }
    catch (std::exception &e)
    {
        std::cout << "Encountered an error while running test_flat_data_type: " << e.what() << std::endl;
        TEST_FAIL_MESSAGE(e.what());
    }
}

void test_nested_data_type_flatten(void)
{
    // nested data type hierarchy
    // def innerType:
    //     float : float
    //     int : int
    //
    // def outerType:
    //     bool : bool
    //     inner : innerType
    //

    // Create the inner type
    DataType innerType;
    Field floatField = Field::emptyField("float", FieldType::FLOAT);
    Field intField = Field::emptyField("int", FieldType::INT);
    innerType.addField(floatField);
    innerType.addField(intField);

    // Create the outer type
    DataType outerType;
    Field boolField = Field::emptyField("bool", FieldType::BOOL);
    outerType.addField(boolField);
    outerType.addCustomField("inner", innerType);

    // validation
    // test that the size is correct
    std::size_t size = boolField.size + innerType.size;
    TEST_ASSERT_TRUE_MESSAGE(outerType.size == size, "Outer type size is not correct");
    // now try flattening
    std::map<std::string, DataMember> flatMembers = outerType.flatten();
    TEST_ASSERT_TRUE_MESSAGE(flatMembers.size() == 2, "Flat members size is not 2");
    try
    {
        // test that we get no errors converting the datamember to a field
        DataMember boolMember = flatMembers["bool"];
        DataMember innerMember = flatMembers["inner"];
        std::cout << "got members from flat" << std::endl;
        std::cout << boolMember.toString() << std::endl;
        std::cout << innerMember.toString() << std::endl;

        std::cout << "getting fields from members" << std::endl;
        Field boolFieldFromMember = boolMember.getField();
        std::cout << "getting inner type from member" << std::endl;
        DataType innerTypeFromMember = innerMember.getDataType();
        std::cout << "got fields from members" << std::endl;
        // now test that the fields are the is_same
        TEST_ASSERT_TRUE_MESSAGE(boolFieldFromMember == boolField, "Bool fields are not the same");
        TEST_ASSERT_TRUE_MESSAGE(innerTypeFromMember == innerType, "Inner types are not the same");
        // now test that the inner type is correct
        std::map<std::string, DataMember> innerFlatMembers = innerTypeFromMember.flatten();
        TEST_ASSERT_TRUE_MESSAGE(innerFlatMembers.size() == 2, "Inner flat members size is not 2");
        DataMember innerFloatMember = innerFlatMembers["float"];
        DataMember innerIntMember = innerFlatMembers["int"];
        Field innerFloatFieldFromMember = innerFloatMember.getField();
        Field innerIntFieldFromMember = innerIntMember.getField();
        TEST_ASSERT_TRUE_MESSAGE(innerFloatFieldFromMember == floatField, "Inner float fields are not the same");
        TEST_ASSERT_TRUE_MESSAGE(innerIntFieldFromMember == intField, "Inner int fields are not the same");
    }
    catch (std::exception &e)
    {
        std::cout << "Encountered an error while running test_nested_data_type and flatten(): " << std::endl;
        // print out stack trace
        std::cout << e.what() << std::endl;
        TEST_FAIL_MESSAGE(e.what());
    }

    // now test this using the flattenFull method
    try 
    {
        std::map<std::string, Field> flattened = outerType.flattenFull();
        TEST_ASSERT_TRUE_MESSAGE(flattened.size() == 3, "Flattened size is not 4");
        // test that we get no errors converting the datamember to a field
        Field boolFieldFromMember = flattened["bool"];
        Field innerFloatFieldFromMember = flattened["inner.float"];
        Field innerIntFieldFromMember = flattened["inner.int"];

        TEST_ASSERT_TRUE_MESSAGE(boolFieldFromMember == boolField, "Bool fields are not the same");
        TEST_ASSERT_TRUE_MESSAGE(innerFloatFieldFromMember == floatField, "Inner float fields are not the same");
        TEST_ASSERT_TRUE_MESSAGE(innerIntFieldFromMember == intField, "Inner int fields are not the same");
    }
    catch (std::exception &e)
    {
        std::cout << "Encountered an error while running test_nested_data_type and flattenFull(): " << std::endl;
        // print out stack trace
        std::cout << e.what() << std::endl;
        TEST_FAIL_MESSAGE(e.what());
    }
}

void TestingSuite::runDataTypeFactoryTests()
{
    // value tests
    RUN_TEST(test_value_int);
    RUN_TEST(test_value_float);
    RUN_TEST(test_value_bool);
    RUN_TEST(test_value_string);
    RUN_TEST(test_value_version);

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
    RUN_TEST(test_field_copy_constructor);
    RUN_TEST(test_value_copy_constructor);

    // new byte tests
    RUN_TEST(test_value_byte);
    RUN_TEST(test_field_predefined_byte);
    RUN_TEST(test_field_not_predefined_byte);

    // data type tests
    RUN_TEST(test_flat_data_type);
    RUN_TEST(test_nested_data_type_flatten);
}