#define NATIVE
#include <unity.h>
#include <string>
#include <sstream>
#include <iostream>

#include "daqser.hpp"
#include "testing_suite.hpp"

void test_basic_use(void)
{
    daqser::initialize();
    daqser::setSchema("test-api-basic", 1, 0, 1);
    daqser::printSchema();
}

/// @brief I would imagine that the logger project would use these aspects of the API
void test_logger_sim(void)
{

}

/// @brief I would imagine that the wireless project would use these aspects of the API
void test_wireless_sim(void)
{

}


void TestingSuite::runApiTests()
{
    RUN_TEST(test_basic_use);
    RUN_TEST(test_logger_sim);
    RUN_TEST(test_wireless_sim);
}