#define NATIVE
#include <unity.h>
#include <string>
#include <sstream>
#include <iostream>

#include "testing_suite.hpp"
#include "tokenizer.hpp"
#include "parser.hpp"

using namespace daqser::impl;

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
    TEST_ASSERT_EQUAL(6, frameTemplate.getFieldNames().size());
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

void test_multiple_double_layer_backward(void)
{
    // same as above test, but DateTime is declared after CarData
    Tokenizer tokenizer("./test/static/test_multiple_double_layer_backward.drive");
    Parser parser;
    std::vector<Token> tokens = tokenizer.tokenize();
    Schema out;
    Parser::ParsingResult result = parser.buildSchema(tokens, out);

    TEST_ASSERT_TRUE_MESSAGE(result.isValid, result.message.str().c_str());
    TEST_ASSERT_EQUAL_STRING("multiple-double-layer-backward", out.schemaName.c_str());
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
    TEST_ASSERT_EQUAL(6, frameTemplate.getFieldNames().size());
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

void test_ultimate(void)
{
    Tokenizer tokenizer("./test/static/test_ultimate.drive");
    Parser parser;
    std::vector<Token> tokens = tokenizer.tokenize();
    Schema out;
    Parser::ParsingResult result = parser.buildSchema(tokens, out);

    TEST_ASSERT_TRUE_MESSAGE(result.isValid, result.message.str().c_str());
    TEST_ASSERT_EQUAL_STRING("test-ultimate", out.schemaName.c_str());
    int version[3] = {1, 0, 0};
    for (int i = 0; i < 3; i++) {
        TEST_ASSERT_EQUAL(version[i], out.versionNumber[i]);
    }

    FrameTemplate frameTemplate = *out.frameTemplate;

    // Checking the header fields
    const char* headerFields[] = {
        "header.timestamp.year", "header.timestamp.month", "header.timestamp.day",
        "header.timestamp.hour", "header.timestamp.minute", "header.timestamp.second",
        "header.timeSinceLastSample"
    };
    FieldType headerFieldTypes[] = {
        FieldType::INT, FieldType::INT, FieldType::INT,
        FieldType::INT, FieldType::INT, FieldType::INT,
        FieldType::FLOAT
    };

    // Checking the BMSData fields
    const char* bmsDataFields[] = {
        "bmsData.timestamp.year", "bmsData.timestamp.month", "bmsData.timestamp.day",
        "bmsData.timestamp.hour", "bmsData.timestamp.minute", "bmsData.timestamp.second",
        "bmsData.voltage", "bmsData.current", "bmsData.temperature"
    };
    FieldType bmsDataFieldTypes[] = {
        FieldType::INT, FieldType::INT, FieldType::INT,
        FieldType::INT, FieldType::INT, FieldType::INT,
        FieldType::FLOAT, FieldType::FLOAT, FieldType::FLOAT
    };

    // Checking TireData fields for all tires
    const char* tireFields[] = {
        "lfTire.pressure", "lfTire.temperature", "lfTire.rpm",
        "rfTire.pressure", "rfTire.temperature", "rfTire.rpm",
        "lrTire.pressure", "lrTire.temperature", "lrTire.rpm",
        "rrTire.pressure", "rrTire.temperature", "rrTire.rpm",
    };
    FieldType tireFieldTypes[] = {
        FieldType::FLOAT, FieldType::FLOAT, FieldType::FLOAT,
        FieldType::FLOAT, FieldType::FLOAT, FieldType::FLOAT,
        FieldType::FLOAT, FieldType::FLOAT, FieldType::FLOAT,
        FieldType::FLOAT, FieldType::FLOAT, FieldType::FLOAT
    };

    // Checking ambient temperature
    const char* ambientTempField = "ambientTemp";
    FieldType ambientTempFieldType = FieldType::FLOAT;

    // Perform checks
    for (int i = 0; i < sizeof(headerFields)/sizeof(headerFields[0]); i++) {
        std::cout << "Checking " << headerFields[i] << std::endl;
        TEST_ASSERT_TRUE_MESSAGE(frameTemplate.isField(headerFields[i]), (std::string(headerFields[i]) + " not found in frame template").c_str());
        TEST_ASSERT_TRUE_MESSAGE(frameTemplate.getField(headerFields[i]).type == headerFieldTypes[i], (std::string(headerFields[i]) + " is not of correct type").c_str());
    }

    for (int i = 0; i < sizeof(bmsDataFields)/sizeof(bmsDataFields[0]); i++) {
        std::cout << "Checking " << bmsDataFields[i] << std::endl;
        TEST_ASSERT_TRUE_MESSAGE(frameTemplate.isField(bmsDataFields[i]), (std::string(bmsDataFields[i]) + " not found in frame template").c_str());
        TEST_ASSERT_TRUE_MESSAGE(frameTemplate.getField(bmsDataFields[i]).type == bmsDataFieldTypes[i], (std::string(bmsDataFields[i]) + " is not of correct type").c_str());
    }

    for (int i = 0; i < sizeof(tireFields)/sizeof(tireFields[0]); i++) {
        std::cout << "Checking " << tireFields[i] << std::endl;
        TEST_ASSERT_TRUE_MESSAGE(frameTemplate.isField(tireFields[i]), (std::string(tireFields[i]) + " not found in frame template").c_str());
        TEST_ASSERT_TRUE_MESSAGE(frameTemplate.getField(tireFields[i]).type == tireFieldTypes[i], (std::string(tireFields[i]) + " is not of correct type").c_str());
    }

    TEST_ASSERT_TRUE_MESSAGE(frameTemplate.isField(ambientTempField), std::string(ambientTempField + std::string(" not found in frame template")).c_str());
    TEST_ASSERT_TRUE_MESSAGE(frameTemplate.getField(ambientTempField).type == ambientTempFieldType, (std::string(ambientTempField) + " is not of correct type").c_str());
}

void test_cyclic_simple(void)
{
    // data type with cyclic dependency
    // parsing should fail
    Tokenizer tokenizer("./test/static/test_cyclic_simple.drive");
    Parser parser;
    std::vector<Token> tokens = tokenizer.tokenize();
    Schema out;
    Parser::ParsingResult result = parser.buildSchema(tokens, out);

    std::cout << result.message.str() << std::endl;
    TEST_ASSERT_FALSE_MESSAGE(result.isValid, result.message.str().c_str());
}

void test_cyclic_two_layer(void)
{
    // data type with cyclic dependency
    // parsing should fail
    Tokenizer tokenizer("./test/static/test_cyclic_two_layer.drive");
    Parser parser;
    std::vector<Token> tokens = tokenizer.tokenize();
    Schema out;
    Parser::ParsingResult result = parser.buildSchema(tokens, out);

    std::cout << result.message.str() << std::endl;
    TEST_ASSERT_FALSE_MESSAGE(result.isValid, result.message.str().c_str());
}

void test_cyclic_advanced(void)
{
    // data type with cyclic dependency
    // parsing should fail
    Tokenizer tokenizer("./test/static/test_cyclic_advanced.drive");
    Parser parser;
    std::vector<Token> tokens = tokenizer.tokenize();
    Schema out;
    Parser::ParsingResult result = parser.buildSchema(tokens, out);

    std::cout << result.message.str() << std::endl;
    TEST_ASSERT_FALSE_MESSAGE(result.isValid, result.message.str().c_str());
}

void test_only_parse_meta(void)
{
    // just parse the meta information from test_ulimate.drive
    Tokenizer tokenizer("./test/static/test_ultimate.drive");
    Parser parser;
    std::vector<Token> tokens = tokenizer.tokenize();
    Schema out;
    Parser::ParsingResult result = parser.buildSchema(tokens, out, true);

    TEST_ASSERT_TRUE_MESSAGE(result.isValid, result.message.str().c_str());
    TEST_ASSERT_EQUAL_STRING("test-ultimate", out.schemaName.c_str());
    int version[3] = {1, 0, 0};
    for (int i = 0; i < 3; i++) {
        TEST_ASSERT_EQUAL(version[i], out.versionNumber[i]);
    }

    FrameTemplate *frameTemplate = &(*out.frameTemplate);
    TEST_ASSERT_TRUE_MESSAGE(frameTemplate == nullptr, "Frame template should be null");

}


void TestingSuite::runParserTests()
{
    RUN_TEST(test_simple_sequence_validation);
    RUN_TEST(test_full_sequence_validation);
    RUN_TEST(test_simple);
    RUN_TEST(test_nested);
    RUN_TEST(test_multiple_single_layer);
    RUN_TEST(test_multiple_double_layer);
    RUN_TEST(test_multiple_double_layer_backward);
    RUN_TEST(test_ultimate);
    RUN_TEST(test_cyclic_simple);
    RUN_TEST(test_cyclic_two_layer);
    RUN_TEST(test_cyclic_advanced);
    RUN_TEST(test_only_parse_meta);
}