#include <unity.h>

#include "testing_suite.hpp"
#include "datatype_factory.hpp"
#include "frame.hpp"

DataType build_example_datatype()
{
    Field field1 = Field::emptyField("field1", FieldType::INT);
    Field field2 = Field::emptyField("field2", FieldType::FLOAT);
    Field field3 = Field::emptyField("field3", FieldType::BOOL);

    DataType innerType;
    innerType.addField(field1);
    innerType.addField(field2);
    innerType.addField(field3);

    Field field4 = Field::emptyField("field4", FieldType::STRING);
    Field field5 = Field::emptyField("field5", FieldType::VERSION);

    DataType outerType;
    outerType.addField(field4);
    outerType.addField(field5);
    outerType.addCustomField("innerField", innerType);

    return outerType;
}

void test_frame_template_constructor()
{
    FrameTemplate frameTemplate = FrameTemplate(build_example_datatype());
    TEST_ASSERT_EQUAL(5, frameTemplate.getFieldNames().size());
    TEST_ASSERT_TRUE_MESSAGE(frameTemplate.isField("field4"), "field4 not found in frame template");
    TEST_ASSERT_TRUE_MESSAGE(frameTemplate.isField("field5"), "field5 not found in frame template");
    TEST_ASSERT_TRUE_MESSAGE(frameTemplate.isField("innerField.field1"), "innerField.field1 not found in frame template");
    TEST_ASSERT_TRUE_MESSAGE(frameTemplate.isField("innerField.field2"), "innerField.field2 not found in frame template");
    TEST_ASSERT_TRUE_MESSAGE(frameTemplate.isField("innerField.field3"), "innerField.field3 not found in frame template");

}

void test_frame_template_set()
{
    FrameTemplate frameTemplate = FrameTemplate(build_example_datatype());
    frameTemplate.set("field4", "test");
    frameTemplate.set("innerField.field1", 1);
    frameTemplate.set("innerField.field2", 2.0f);
    frameTemplate.set("innerField.field3", true);

    TEST_ASSERT_EQUAL_STRING("test", frameTemplate.get<std::string>("field4").c_str());
    TEST_ASSERT_EQUAL(1, frameTemplate.get<int>("innerField.field1"));
    TEST_ASSERT_EQUAL(2.0f, frameTemplate.get<float>("innerField.field2"));
    TEST_ASSERT_EQUAL(true, frameTemplate.get<bool>("innerField.field3"));
}

void test_frameteplate_buildFrame()
{

}

void TestingSuite::runFrameTests()
{
    RUN_TEST(test_frame_template_constructor);
    RUN_TEST(test_frame_template_set);
    RUN_TEST(test_frameteplate_buildFrame);
}