#define NATIVE
#include <unity.h>
#include <string>
#include <sstream>
#include <iostream>

#include "testing_suite.hpp"
#include "tokenizer.hpp"
#include "parser.hpp"

using namespace daq::impl;

void test_sequence(std::string filename)
{
    Tokenizer tokenizer(filename);
    Parser parser;
    std::vector<Token> tokens = tokenizer.tokenize();
    Parser::ParsingResult result = parser.isValidSequence(tokens);
    std::stringstream ss;
    ss << "TOKENS:\n " << Tokenizer::dumpTokens(tokens, " ") << std::endl;
    ss << result.message.str();
    TEST_ASSERT_TRUE_MESSAGE(result.isValid, ss.str().c_str());
}

void test_simple_sequence_validation(void)
{
    test_sequence("./test/static/test_valid_meta.drive");
}

void test_full_sequence_validation(void)
{
    test_sequence("./test/static/test_full.drive");
}

void test_simple(void)
{
    Tokenizer tokenizer("./test/static/test_valid_meta.drive");
    Parser parser;
    std::vector<Token> tokens = tokenizer.tokenize();
    Schema out;
    Parser::ParsingResult result = parser.buildSchema(tokens, out);

    TEST_ASSERT_TRUE_MESSAGE(result.isValid, result.message.str().c_str());
    TEST_ASSERT_EQUAL_STRING("valid-test-schema", out.schemaName.c_str());
    int version[3] = {1, 0, 1};
    for (int i = 0; i < 3; i++) {
        TEST_ASSERT_EQUAL(version[i], out.versionNumber[i]);
    }

    // now test the frame template
    // our frame should be of type TestType
    // with a single float field called "value"

    FrameTemplate frameTemplate = *out.frameTemplate;
    TEST_ASSERT_EQUAL(1, frameTemplate.getFieldNames().size());
    TEST_ASSERT_TRUE_MESSAGE(frameTemplate.isField("value"), "value not found in frame template");
    TEST_ASSERT_TRUE_MESSAGE(frameTemplate.getField("value").type == FieldType::FLOAT, "value is not of type FLOAT");
}

void test_nested(void)
{
    Tokenizer tokenizer("./test/static/test_full.drive");
    Parser parser;
    std::vector<Token> tokens = tokenizer.tokenize();
    Schema out;
    Parser::ParsingResult result = parser.buildSchema(tokens, out);

    TEST_ASSERT_TRUE_MESSAGE(result.isValid, result.message.str().c_str());
    TEST_ASSERT_EQUAL_STRING("full-test-schema", out.schemaName.c_str());
    int version[3] = {1, 0, 0};
    for (int i = 0; i < 3; i++) {
        TEST_ASSERT_EQUAL(version[i], out.versionNumber[i]);
    }

    // now test the frame template
    // our frame should be of type CarData
    // CarData has two fields:
    // 1. A DateTime field called "timestamp" -- another custom type
    // 2. A float called ambientTemp
    // DateTime has one field:
    // 1. A long called "timeSince1990"

    FrameTemplate frameTemplate = *out.frameTemplate;
    TEST_ASSERT_EQUAL(2, frameTemplate.getFieldNames().size());
    TEST_ASSERT_TRUE_MESSAGE(frameTemplate.isField("timestamp.timeSince1990"), "timestamp.timeSince1990 not found in frame template");
    TEST_ASSERT_TRUE_MESSAGE(frameTemplate.isField("ambientTemp"), "ambientTemp not found in frame template");

    // test the types of the fields
    TEST_ASSERT_TRUE_MESSAGE(frameTemplate.getField("timestamp.timeSince1990").type == FieldType::LONG, "timestamp.timeSince1990 is not of type LONG");
    TEST_ASSERT_TRUE_MESSAGE(frameTemplate.getField("ambientTemp").type == FieldType::FLOAT, "ambientTemp is not of type FLOAT");
}

void test_multiple_single_layer(void)
{
    Tokenizer tokenizer("./test/static/test_multiple_single_layer.drive");
    Parser parser;
    std::vector<Token> tokens = tokenizer.tokenize();
    Schema out;
    Parser::ParsingResult result = parser.buildSchema(tokens, out);

    TEST_ASSERT_TRUE_MESSAGE(result.isValid, result.message.str().c_str());
    TEST_ASSERT_EQUAL_STRING("multiple-single-layer", out.schemaName.c_str());
    int version[3] = {1, 0, 0};
    for (int i = 0; i < 3; i++) {
        TEST_ASSERT_EQUAL(version[i], out.versionNumber[i]);
    }

    // now test the frame template
    // our frame should be of type CarData
    // CarData has three fields:
    // 1. A DateTime field called "timestamp" -- another custom type
    // 2. A float called ambientTemp
    // 3. A BMSData field called "bmsData" -- another custom type
    // DateTime has one field:
    // 1. A long called "timeSince1990"
    // BMSData has two fields:
    // 1. A float called "voltage"
    // 2. A float called "current"
    // 3. A float called "temperature"

    FrameTemplate frameTemplate = *out.frameTemplate;
    TEST_ASSERT_EQUAL(5, frameTemplate.getFieldNames().size());
    TEST_ASSERT_TRUE_MESSAGE(frameTemplate.isField("timestamp.timeSince1990"), "timestamp.timeSince1990 not found in frame template");
    TEST_ASSERT_TRUE_MESSAGE(frameTemplate.isField("ambientTemp"), "ambientTemp not found in frame template");
    TEST_ASSERT_TRUE_MESSAGE(frameTemplate.isField("bmsData.voltage"), "bmsData.voltage not found in frame template");
    TEST_ASSERT_TRUE_MESSAGE(frameTemplate.isField("bmsData.current"), "bmsData.current not found in frame template");
    TEST_ASSERT_TRUE_MESSAGE(frameTemplate.isField("bmsData.temperature"), "bmsData.temperature not found in frame template");

    // test the types of the fields
    TEST_ASSERT_TRUE_MESSAGE(frameTemplate.getField("timestamp.timeSince1990").type == FieldType::LONG, "timestamp.timeSince1990 is not of type LONG");
    TEST_ASSERT_TRUE_MESSAGE(frameTemplate.getField("ambientTemp").type == FieldType::FLOAT, "ambientTemp is not of type FLOAT");
    TEST_ASSERT_TRUE_MESSAGE(frameTemplate.getField("bmsData.voltage").type == FieldType::FLOAT, "bmsData.voltage is not of type FLOAT");
    TEST_ASSERT_TRUE_MESSAGE(frameTemplate.getField("bmsData.current").type == FieldType::FLOAT, "bmsData.current is not of type FLOAT");
    TEST_ASSERT_TRUE_MESSAGE(frameTemplate.getField("bmsData.temperature").type == FieldType::FLOAT, "bmsData.temperature is not of type FLOAT");

}

void test_multiple_double_layer(void)
{
    Tokenizer tokenizer("./test/static/test_multiple_double_layer.drive");
    Parser parser;
    std::vector<Token> tokens = tokenizer.tokenize();
    Schema out;
    Parser::ParsingResult result = parser.buildSchema(tokens, out);

    TEST_ASSERT_TRUE_MESSAGE(result.isValid, result.message.str().c_str());
    TEST_ASSERT_EQUAL_STRING("multiple-double-layer", out.schemaName.c_str());
    int version[3] = {1, 0, 0};
    for (int i = 0; i < 3; i++) {
        TEST_ASSERT_EQUAL(version[i], out.versionNumber[i]);
    }

    // now test the frame template
    // our frame should be of type CarData
    // CarData has three fields:
    // 1. A DateTime field called "timestamp" -- another custom type
    // 2. A float called ambientTemp
    // 3. A BMSData field called "bmsData" -- another custom type
    // DateTime has one field:
    // 1. A long called "timeSince1990"
    // BMSData has two fields:
    // 1. A float called "voltage"
    // 2. A float called "current"
    // 3. A float called "temperature"
    // 4. A datetime called "timestamp"

    FrameTemplate frameTemplate = *out.frameTemplate;
    TEST_ASSERT_EQUAL(5, frameTemplate.getFieldNames().size());
    TEST_ASSERT_TRUE_MESSAGE(frameTemplate.isField("timestamp.timeSince1990"), "timestamp.timeSince1990 not found in frame template");
    TEST_ASSERT_TRUE_MESSAGE(frameTemplate.isField("ambientTemp"), "ambientTemp not found in frame template");
    TEST_ASSERT_TRUE_MESSAGE(frameTemplate.isField("bmsData.voltage"), "bmsData.voltage not found in frame template");
    TEST_ASSERT_TRUE_MESSAGE(frameTemplate.isField("bmsData.current"), "bmsData.current not found in frame template");
    TEST_ASSERT_TRUE_MESSAGE(frameTemplate.isField("bmsData.temperature"), "bmsData.temperature not found in frame template");
    TEST_ASSERT_TRUE_MESSAGE(frameTemplate.isField("bmsData.timestamp.timeSince1990"), "bmsData.timestamp.timeSince1990 not found in frame template");

    // test the types of the fields
    TEST_ASSERT_TRUE_MESSAGE(frameTemplate.getField("timestamp.timeSince1990").type == FieldType::LONG, "timestamp.timeSince1990 is not of type LONG");
    TEST_ASSERT_TRUE_MESSAGE(frameTemplate.getField("ambientTemp").type == FieldType::FLOAT, "ambientTemp is not of type FLOAT");
    TEST_ASSERT_TRUE_MESSAGE(frameTemplate.getField("bmsData.voltage").type == FieldType::FLOAT, "bmsData.voltage is not of type FLOAT");
    TEST_ASSERT_TRUE_MESSAGE(frameTemplate.getField("bmsData.current").type == FieldType::FLOAT, "bmsData.current is not of type FLOAT");
    TEST_ASSERT_TRUE_MESSAGE(frameTemplate.getField("bmsData.temperature").type == FieldType::FLOAT, "bmsData.temperature is not of type FLOAT");
    TEST_ASSERT_TRUE_MESSAGE(frameTemplate.getField("bmsData.timestamp.timeSince1990").type == FieldType::LONG, "bmsData.timestamp.timeSince1990 is not of type LONG");
}

void TestingSuite::runParserTests()
{
    RUN_TEST(test_simple_sequence_validation);
    RUN_TEST(test_full_sequence_validation);
    RUN_TEST(test_simple);
    RUN_TEST(test_nested);
    RUN_TEST(test_multiple_single_layer);
}