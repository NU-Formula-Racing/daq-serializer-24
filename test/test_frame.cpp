#include <unity.h>

#include "testing_suite.hpp"
#include "datatype_factory.hpp"
#include "frame.hpp"

using namespace daqser::impl;

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
    DataType type = build_example_datatype();
    FrameTemplate frameTemplate = FrameTemplate(type);
    frameTemplate.set("field4", "test");
    frameTemplate.set("innerField.field1", 1);
    frameTemplate.set("innerField.field2", 2.0f);
    frameTemplate.set("innerField.field3", true);

    TEST_ASSERT_EQUAL_STRING("test", frameTemplate.get<std::string>("field4").c_str());
    TEST_ASSERT_EQUAL(1, frameTemplate.get<int>("innerField.field1"));
    TEST_ASSERT_EQUAL(2.0f, frameTemplate.get<float>("innerField.field2"));
    TEST_ASSERT_EQUAL(true, frameTemplate.get<bool>("innerField.field3"));
}

void test_frameteplate_serialize_frame()
{
    DataType type = build_example_datatype();
    FrameTemplate frameTemplate = FrameTemplate(type);
    frameTemplate.set("field4", "test"); // 5 bytes
    frameTemplate.set("innerField.field1", 1); // 4 bytes
    frameTemplate.set("innerField.field2", 2.0f); // 4 bytes
    frameTemplate.set("innerField.field3", true); // 1 byte

    // now we build the frame
    std::vector<std::uint8_t> frame = frameTemplate.serializeFrame();

    // print out the binary
    for (std::uint8_t byte : frame)
    {
        std::cout << byte << " ";
    }

    std::cout << std::endl;

    // check that the frame is the correct size
    TEST_ASSERT_EQUAL(25, frame.size());

    // check that the values haven't changed
    TEST_ASSERT_EQUAL_STRING("test", frameTemplate.get<std::string>("field4").c_str());
    TEST_ASSERT_EQUAL(1, frameTemplate.get<int>("innerField.field1"));
    TEST_ASSERT_EQUAL(2.0f, frameTemplate.get<float>("innerField.field2"));
    TEST_ASSERT_EQUAL(true, frameTemplate.get<bool>("innerField.field3"));

    // now set the values to something else
    frameTemplate.set("field4", "test2");
    frameTemplate.set("innerField.field1", 2);
    frameTemplate.set("innerField.field2", 3.0f);
    frameTemplate.set("innerField.field3", false);

    // check that the values have changed
    TEST_ASSERT_EQUAL_STRING("test2", frameTemplate.get<std::string>("field4").c_str());
    TEST_ASSERT_EQUAL(2, frameTemplate.get<int>("innerField.field1"));
    TEST_ASSERT_EQUAL(3.0f, frameTemplate.get<float>("innerField.field2"));
    TEST_ASSERT_EQUAL(false, frameTemplate.get<bool>("innerField.field3"));

    // now deserialize the frame
    frameTemplate.deserializeFrame(frame);

    // check that the values are back to the original values
    TEST_ASSERT_EQUAL_STRING("test", frameTemplate.get<std::string>("field4").c_str());
    TEST_ASSERT_EQUAL(1, frameTemplate.get<int>("innerField.field1"));
    TEST_ASSERT_EQUAL(2.0f, frameTemplate.get<float>("innerField.field2"));
    TEST_ASSERT_EQUAL(true, frameTemplate.get<bool>("innerField.field3"));
}

void test_frame_serialize_to_json()
{
    DataType type = build_example_datatype();
    FrameTemplate frameTemplate = FrameTemplate(type);
    frameTemplate.set("field4", "test");
    frameTemplate.set("innerField.field1", 1);
    frameTemplate.set("innerField.field2", 2.0f);
    frameTemplate.set("innerField.field3", true);

    std::string json = frameTemplate.serializeFrameToJson();
    std::cout << json << std::endl;

}

void TestingSuite::runFrameTests()
{
    RUN_TEST(test_frame_template_constructor);
    RUN_TEST(test_frame_template_set);
    RUN_TEST(test_frameteplate_serialize_frame);
    RUN_TEST(test_frame_serialize_to_json);
}