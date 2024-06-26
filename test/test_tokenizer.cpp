#define NATIVE
#include <unity.h>
#include <string>
#include <sstream>
#include <iostream>

#include "tokenizer.hpp"
#include "testing_suite.hpp"

using namespace daqser::impl;

void test_integer_literal(void)
{
    Tokenizer tokenizer;
    TokenType type;
    bool result = tokenizer.isLiteral("123", type);
    TEST_ASSERT_TRUE_MESSAGE(result, "Expected true for integer literal");
    TEST_ASSERT_EQUAL_INT(TOKEN_INT_LITERAL, type);
}

void test_float_literal(void)
{
    Tokenizer tokenizer;
    TokenType type;
    bool result = tokenizer.isLiteral("123.456", type);
    TEST_ASSERT_TRUE_MESSAGE(result, "Expected true for float literal");
    TEST_ASSERT_EQUAL_INT(TOKEN_FLOAT_LITERAL, type);
}

void test_string_literal(void)
{
    Tokenizer tokenizer;
    TokenType type;
    bool result = tokenizer.isLiteral("\"hello world\"", type);
    TEST_ASSERT_TRUE_MESSAGE(result, "Expected true for string literal");
    TEST_ASSERT_EQUAL_INT(TOKEN_STRING_LITERAL, type);
}

void test_boolean_literals(void)
{
    Tokenizer tokenizer;
    TokenType type;

    // Testing without quotes
    bool result = tokenizer.isLiteral("true", type);
    TEST_ASSERT_TRUE_MESSAGE(result, "Expected true for true boolean literal");
    TEST_ASSERT_EQUAL_INT(TOKEN_BOOL_LITERAL, type);

    result = tokenizer.isLiteral("false", type);
    TEST_ASSERT_TRUE_MESSAGE(result, "Expected true for false boolean literal");
    TEST_ASSERT_EQUAL_INT(TOKEN_BOOL_LITERAL, type);
    
    // Testing with quotes
    result = tokenizer.isLiteral("\"true\"", type);
    TEST_ASSERT_TRUE_MESSAGE(result, "Expected true for '\"true\"' string literal representing boolean");
    TEST_ASSERT_EQUAL_INT(TOKEN_STRING_LITERAL, type); // This should probably be STRING_LITERAL, not BOOL_LITERAL

    result = tokenizer.isLiteral("\"false\"", type);
    TEST_ASSERT_TRUE_MESSAGE(result, "Expected true for '\"false\"' string literal representing boolean");
    TEST_ASSERT_EQUAL_INT(TOKEN_STRING_LITERAL, type); // This should probably be STRING_LITERAL, not BOOL_LITERAL
}

void test_version_literals(void) {
    Tokenizer tokenizer;
    TokenType type;

    // Testing valid version literals
    bool result = tokenizer.isLiteral("1.2.3", type);
    TEST_ASSERT_TRUE_MESSAGE(result, "Expected true for valid version literal '1.2.3'");
    TEST_ASSERT_EQUAL_INT(TOKEN_VERSION_LITERAL, type);

    result = tokenizer.isLiteral("0.0.0", type);
    TEST_ASSERT_TRUE_MESSAGE(result, "Expected true for valid version literal '0.0.0'");
    TEST_ASSERT_EQUAL_INT(TOKEN_VERSION_LITERAL, type);

    // Testing invalid version literals
    result = tokenizer.isLiteral("1.2", type); // Missing patch version
    // TEST_ASSERT_FALSE_MESSAGE(result, "Expected false for invalid version literal '1.2'");
    TEST_ASSERT_NOT_EQUAL_INT(TOKEN_VERSION_LITERAL, type);

    result = tokenizer.isLiteral("a.b.c", type); // Non-numeric characters
    TEST_ASSERT_FALSE_MESSAGE(result, "Expected false for invalid version literal 'a.b.c'");

    result = tokenizer.isLiteral("1.2.3.4", type); // Extra numeric character
    TEST_ASSERT_FALSE_MESSAGE(result, "Expected false for invalid version literal '1.2.3.4'");
}


void test_isSymbol_valid(void)
{
    Tokenizer tokenizer;
    TokenType type;
    bool result = tokenizer.isSymbol("{", type);
    TEST_ASSERT_TRUE_MESSAGE(result, "Expected true for valid symbol '{'");
    TEST_ASSERT_EQUAL_INT(TOKEN_L_BRACE, type);

    result = tokenizer.isSymbol("}", type);
    TEST_ASSERT_TRUE_MESSAGE(result, "Expected true for valid symbol '}'");
    TEST_ASSERT_EQUAL_INT(TOKEN_R_BRACE, type);

    // Test for other symbols...
}

void test_isSymbol_invalid(void)
{
    Tokenizer tokenizer;
    TokenType type;
    bool result = tokenizer.isSymbol("a", type);
    TEST_ASSERT_FALSE_MESSAGE(result, "Expected false for invalid symbol 'a'");

    result = tokenizer.isSymbol("1", type);
    TEST_ASSERT_FALSE_MESSAGE(result, "Expected false for invalid symbol '1'");
}

void test_isKeyword_valid(void)
{
    Tokenizer tokenizer;
    TokenType type;
    bool result = tokenizer.isKeyword("meta", type);
    TEST_ASSERT_TRUE_MESSAGE(result, "Expected true for valid keyword 'meta'");
    TEST_ASSERT_EQUAL_INT(TOKEN_META, type);

    result = tokenizer.isKeyword("def", type);
    TEST_ASSERT_TRUE_MESSAGE(result, "Expected true for valid keyword 'def'");
    TEST_ASSERT_EQUAL_INT(TOKEN_DEF, type);

    // Test for other keywords...
}

void test_isKeyword_invalid(void)
{
    Tokenizer tokenizer;
    TokenType type;
    bool result = tokenizer.isKeyword("invalid_keyword", type);
    TEST_ASSERT_FALSE_MESSAGE(result, "Expected false for invalid keyword 'invalid_keyword'");

    result = tokenizer.isKeyword("123", type);
    TEST_ASSERT_FALSE_MESSAGE(result, "Expected false for invalid keyword '123'");

    // Test for other invalid keywords...
}

void test_valid_meta(void)
{
    std::string fileName = std::string("./test/static/test_valid_meta.drive");
    Tokenizer Tokenizer(fileName);
    TokenType expected[] = {
        TOKEN_META, TOKEN_L_BRACE, TOKEN_IDENTIFIER, TOKEN_COLON, TOKEN_STRING_LITERAL, TOKEN_SEMICOLON, TOKEN_IDENTIFIER, TOKEN_COLON, TOKEN_VERSION_LITERAL, TOKEN_SEMICOLON, TOKEN_R_BRACE,  // meta
        TOKEN_DEF, TOKEN_IDENTIFIER, TOKEN_L_BRACE, TOKEN_IDENTIFIER, TOKEN_IDENTIFIER, TOKEN_SEMICOLON, TOKEN_R_BRACE, // def TestType
        TOKEN_FRAME, TOKEN_L_PARENTHESES, TOKEN_IDENTIFIER, TOKEN_R_PARENTHESES, TOKEN_SEMICOLON,
        TOKEN_END_OF_FILE
    };

    std::vector<Token> tokens  = Tokenizer.tokenizeFile();
    for (int i = 0; i < tokens.size(); i++)
    {
        std::stringstream message;
        message << "Expected " << expected[i] << " but got " << tokens[i].type << " at token " << i;
        std::string messageStr = message.str();
        TEST_ASSERT_TRUE_MESSAGE(tokens[i].type == expected[i], messageStr.c_str());
    }
}

void test_full(void)
{
    std::string filename = std::string("./test/static/test_full.drive");
    Tokenizer Tokenizer(filename);
    TokenType expected[] = {
        TOKEN_META, TOKEN_L_BRACE, TOKEN_IDENTIFIER, TOKEN_COLON, TOKEN_STRING_LITERAL, TOKEN_SEMICOLON, TOKEN_IDENTIFIER, TOKEN_COLON, TOKEN_VERSION_LITERAL, TOKEN_SEMICOLON, TOKEN_R_BRACE, // meta
        TOKEN_DEF, TOKEN_IDENTIFIER, TOKEN_L_BRACE, TOKEN_IDENTIFIER, TOKEN_IDENTIFIER, TOKEN_SEMICOLON, TOKEN_R_BRACE, // def DateTime
        TOKEN_DEF, TOKEN_IDENTIFIER, TOKEN_L_BRACE, TOKEN_IDENTIFIER, TOKEN_IDENTIFIER, TOKEN_SEMICOLON, TOKEN_IDENTIFIER, TOKEN_IDENTIFIER, TOKEN_SEMICOLON, TOKEN_R_BRACE, // def CarData
        TOKEN_FRAME, TOKEN_L_PARENTHESES, TOKEN_IDENTIFIER, TOKEN_R_PARENTHESES, TOKEN_SEMICOLON, TOKEN_END_OF_FILE // frame (CarData)
    };

    std::vector<Token> tokens = Tokenizer.tokenizeFile();
    for (int i = 0; i < tokens.size(); i++)
    {
        std::stringstream message;
        TokenType expectedType = expected[i];
        std::string expected = Tokenizer::tokenTypeToString(expectedType);
        std::string actual = Tokenizer::tokenTypeToString(tokens[i].type);
        message << "Expected " << expected << " but got " << actual << " at token " << i;
        std::string messageStr = message.str();
        TEST_ASSERT_TRUE_MESSAGE(tokens[i].type == expectedType, messageStr.c_str());
    }
}

void TestingSuite::runTokenizerTests()
{
    RUN_TEST(test_integer_literal);
    RUN_TEST(test_float_literal);
    RUN_TEST(test_string_literal);
    RUN_TEST(test_boolean_literals);
    RUN_TEST(test_version_literals);
    RUN_TEST(test_isSymbol_valid);
    RUN_TEST(test_isSymbol_invalid);
    RUN_TEST(test_isKeyword_valid);
    RUN_TEST(test_isKeyword_invalid);
    RUN_TEST(test_valid_meta);
    RUN_TEST(test_full);
}
