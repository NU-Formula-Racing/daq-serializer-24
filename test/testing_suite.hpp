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
            std::cout << "*** FINISHED RUNNING TOKENIZER TESTS ***" << std::endl;
        }
        if (RUN_DATATYPE_FACTORY_TESTS)
        {
            std::cout << "*** RUNNING DATATYPE FACTORY TESTS ***" << std::endl;
            runDataTypeFactoryTests();
            std::cout << "*** FINISHED RUNNING DATATYPE FACTORY TESTS ***" << std::endl;
        }
        if (RUN_PARSER_TESTS)
        {
            std::cout << "*** RUNNING PARSER TESTS ***" << std::endl;
            runParserTests();
            std::cout << "*** FINISHED RUNNING PARSER TESTS ***" << std::endl;
        }
        if (RU_FRAME_TESTS)
        {
            std::cout << "*** RUNNING FRAME TESTS ***" << std::endl;
            runFrameTests();
            std::cout << "*** FINISHED RUNNING FRAME TESTS ***" << std::endl;
        }
        std::cout << "*** FINISHED RUNNING TESTS ***" << std::endl;
        UNITY_END();
    }

private:
    const bool RUN_TOKENIZER_TESTS = true;
    const bool RUN_PARSER_TESTS = true;
    const bool RUN_DATATYPE_FACTORY_TESTS = true;
    const bool RU_FRAME_TESTS = true;
    void runTokenizerTests();
    void runParserTests();
    void runDataTypeFactoryTests();
    void runFrameTests();
};

#endif // __TESTING_SUITE_H__