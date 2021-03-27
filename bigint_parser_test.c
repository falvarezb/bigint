#include "acutest.h"
#include "bigint.h"
#include <stddef.h>
#include <math.h>
#include <string.h>

void test_from_to_string() 
{
    {
        char* str = "000000000000000123";
        uint64_t expected[] = {123};
        bigint_t result = from_string(str);
        char* result2 = to_string(result);
        TEST_CHECK_(result.number[0] == expected[0], "from_string(%s)[0]=%llu but expected %llu", str, result.number[0], expected[0]);
        TEST_CHECK_(strcmp(result2, str) == 0, "result %s but expected %s", result2, str);    
    }

    {
        char* str = "000000000000000012345678901234567899";
        uint64_t expected[] = {345678901234567899, 12};
        bigint_t result = from_string(str);
        char* result2 = to_string(result);
        TEST_CHECK_(result.number[0] == expected[0], "from_string(%s)[0]=%llu but expected %llu", str, result.number[0], expected[0]);
        TEST_CHECK_(result.number[1] == expected[1], "from_string(%s)[1]=%llu but expected %llu", str, result.number[1], expected[1]);  
        TEST_CHECK_(strcmp(result2, str) == 0, "result %s but expected %s", result2, str);    
    }

    {
        char* str = "123456789012345678";
        uint64_t expected[] = {123456789012345678};
        bigint_t result = from_string(str);
        char* result2 = to_string(result);
        TEST_CHECK_(result.number[0] == expected[0], "from_string(%s)[0]=%llu but expected %llu", str, result.number[0], expected[0]);         
        TEST_CHECK_(strcmp(result2, str) == 0, "result %s but expected %s", result2, str);    
    }
}

void test_to_from_string() 
{
    {
        char* expected = "000000000000000123";
        uint64_t number[] = {123};
        bigint_t bigint = {number, 1};
        char* result = to_string(bigint);
        bigint_t result2 = from_string(result);
        
        TEST_CHECK_(strcmp(result, expected) == 0, "to_string()=%s but expected %s", result, expected);
        TEST_CHECK_(result2.number[0] == bigint.number[0], "result %llu but expected %llu", result2.number[0], bigint.number[0]);    
    }

    {
        char* expected = "000000000000000012345678901234567899";
        uint64_t number[] = {345678901234567899, 12};
        bigint_t bigint = {number, 2};
        char* result = to_string(bigint);
        bigint_t result2 = from_string(result);
        
        TEST_CHECK_(strcmp(result, expected) == 0, "to_string()=%s but expected %s", result, expected);
        TEST_CHECK_(result2.number[0] == bigint.number[0], "result %llu but expected %llu", result2.number[0], bigint.number[0]);   
        TEST_CHECK_(result2.number[1] == bigint.number[1], "result %llu but expected %llu", result2.number[1], bigint.number[1]);  
    }

    {
        char* expected = "123456789012345678";
        uint64_t number[] = {123456789012345678};
        bigint_t bigint  = {number, 1};
        char* result = to_string(bigint);
        bigint_t result2 = from_string(result);
        
        TEST_CHECK_(strcmp(result, expected) == 0, "to_string()=%s but expected %s", result, expected);
        TEST_CHECK_(result2.number[0] == bigint.number[0], "result %llu but expected %llu", result2.number[0], bigint.number[0]);
    }
}


TEST_LIST = {
    {"test_from_to_string", test_from_to_string},
    {"test_to_from_string", test_to_from_string}
};
