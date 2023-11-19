#ifndef __TESTING_SUITE_H__
#define __TESTING_SUITE_H__

#include <unity.h>
#include <iostream>

class TestingSuite
{
public:
    TestingSuite() {}
    ~TestingSuite() {}

    void runTests()
    {
        UNITY_BEGIN();
        std::cout << "*** RUNNING TESTS ***" << std::endl;
        // run tests
        if (RUN_TOKENIZER_TESTS)
        {
            std::cout << "*** RUNNING TOKENIZER TESTS ***" << std::endl;
            runTokenizerTests();
        }
        if (RUN_DATATYPE_FACTORY_TESTS)
        {
            std::cout << "*** RUNNING DATATYPE FACTORY TESTS ***" << std::endl;
            runDataTypeFactoryTests();
        }
        if (RUN_PARSER_TESTS)
        {
            std::cout << "*** RUNNING PARSER TESTS ***" << std::endl;
            runParserTests();
        }
        std::cout << "*** FINISHED RUNNING TESTS ***" << std::endl;
        UNITY_END();
    }

private:
    const bool RUN_TOKENIZER_TESTS = false;
    const bool RUN_PARSER_TESTS = false;
    const bool RUN_DATATYPE_FACTORY_TESTS = true;
    void runTokenizerTests();
    void runParserTests();
    void runDataTypeFactoryTests();
};

#endif // __TESTING_SUITE_H__