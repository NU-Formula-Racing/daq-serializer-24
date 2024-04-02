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

void TestingSuite::runParserTests()
{
    RUN_TEST(test_simple_sequence_validation);
    RUN_TEST(test_full_sequence_validation);
    RUN_TEST(test_simple);
}