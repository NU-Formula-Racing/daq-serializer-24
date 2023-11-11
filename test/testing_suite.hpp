#ifndef __TESTING_SUITE_H__
#define __TESTING_SUITE_H__

#include <unity.h>

class TestingSuite
{
public:
    TestingSuite() {}
    ~TestingSuite() {}

    void runTests()
    {
        UNITY_BEGIN();
        runTokenizerTests();
        runParserTests();
        UNITY_END();
    }

private:
    void runTokenizerTests();
    void runParserTests();
};

#endif // __TESTING_SUITE_H__