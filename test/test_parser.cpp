#define NATIVE
#include <unity.h>
#include <string>
#include <sstream>
#include <iostream>

#include "testing_suite.hpp"
#include "tokenizer.hpp"
#include "parser.hpp"

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

void TestingSuite::runParserTests()
{
    RUN_TEST(test_simple_sequence_validation);
    RUN_TEST(test_full_sequence_validation);
}