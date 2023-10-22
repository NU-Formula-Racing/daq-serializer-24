#define NATIVE
#include <unity.h>
#include <string>
#include <sstream>
#include <iostream>

#include "tokenizer.hpp"
#include "parser.hpp"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_simple_sequence_validation(void)
{
    std::string filename = std::string("./test/static/test_valid_meta.drive");
    Tokenizer tokenizer(filename);
    Parser parser;
    std::vector<Token> tokens = tokenizer.tokenize();
    Parser::ParsingResult result = parser.isValidSequence(tokens);
    TEST_ASSERT_TRUE_MESSAGE(result.isValid, "Expected true for valid sequence");
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();
    RUN_TEST(test_simple_sequence_validation);
    UNITY_END();
    return 0;
}