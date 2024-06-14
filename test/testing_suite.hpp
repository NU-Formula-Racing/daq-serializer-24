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
        if (RUN_FRAME_TESTS)
        {
            std::cout << "*** RUNNING FRAME TESTS ***" << std::endl;
            runFrameTests();
            std::cout << "*** FINISHED RUNNING FRAME TESTS ***" << std::endl;
        }
        if (RUN_REGISTRY_TESTS)
        {
            std::cout << "*** RUNNING REGISTRY TESTS ***" << std::endl;
            runRegistryTests();
            std::cout << "*** FINISHED RUNNING REGISTRY TESTS ***" << std::endl;
        }
        if (RUN_API_TESTS)
        {
            std::cout << "*** RUNNING API TESTS ***" << std::endl;
            runApiTests();
            std::cout << "*** FINISHED RUNNING API TESTS ***" << std::endl;
        }
        std::cout << "*** FINISHED RUNNING TESTS ***" << std::endl;
        UNITY_END();
    }

private:
    const bool RUN_TOKENIZER_TESTS = false;
    const bool RUN_PARSER_TESTS = false;
    const bool RUN_DATATYPE_FACTORY_TESTS = true;
    const bool RUN_FRAME_TESTS = true;
    const bool RUN_REGISTRY_TESTS = false;
    const bool RUN_API_TESTS = false;
    void runTokenizerTests();
    void runParserTests();
    void runDataTypeFactoryTests();
    void runFrameTests();
    void runRegistryTests();
    void runApiTests();
};

#endif // __TESTING_SUITE_H__