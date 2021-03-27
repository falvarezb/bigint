#include "acutest.h"
#include "bigint.h"
#include <stddef.h>
#include <math.h>
#include <string.h>

void test_sum() 
{
    {
        uint64_t u[] = {1};
        uint64_t v[] = {2};
        int num_digits = fmax(sizeof(u)/sizeof(u[0]), sizeof(v)/sizeof(v[0]));
        uint64_t result[num_digits+1];
        sum(num_digits, u, v, result);
        uint64_t expected[] = {3};
        TEST_CHECK_(result[0] == expected[0], "sum()[0]=%llu but expected %llu", result[0], expected[0]);
    }

    {
        uint64_t u[] = {123456789012345678lu, 576839484849498888lu};
        uint64_t v[] = {987654321098765432lu, 974857487482847488lu};
        int num_digits = fmax(sizeof(u)/sizeof(u[0]), sizeof(v)/sizeof(v[0]));
        uint64_t result[num_digits+1];
        sum(num_digits, u, v, result);
        uint64_t expected[] = {111111110111111110, 551696972332346377, 1};
        TEST_CHECK_(result[0] == expected[0], "sum()[0]=%llu but expected %llu", result[0], expected[0]);
        TEST_CHECK_(result[1] == expected[1], "sum()[0]=%llu but expected %llu", result[1], expected[1]);
        TEST_CHECK_(result[2] == expected[2], "sum()[0]=%llu but expected %llu", result[2], expected[2]);
    }
}

void test_subtract() 
{
    {
        uint64_t u[] = {3};
        uint64_t v[] = {1};
        int num_digits = fmax(sizeof(u)/sizeof(u[0]), sizeof(v)/sizeof(v[0]));
        uint64_t result[num_digits];
        subtract(num_digits, u, v, result);
        uint64_t expected[] = {2};
        TEST_CHECK_(result[0] == expected[0], "subtract()[0]=%llu but expected %llu", result[0], expected[0]);
    }

    {
        uint64_t u[] = {3};
        uint64_t v[] = {3};
        int num_digits = fmax(sizeof(u)/sizeof(u[0]), sizeof(v)/sizeof(v[0]));
        uint64_t result[num_digits];
        subtract(num_digits, u, v, result);
        uint64_t expected[] = {0};
        TEST_CHECK_(result[0] == expected[0], "subtract()[0]=%llu but expected %llu", result[0], expected[0]);
    }

    {
        uint64_t u[] = {123456789012345678lu, 576839484849498888lu};
        uint64_t v[] = {987654321098765432lu, 174857487482847488lu};
        int num_digits = fmax(sizeof(u)/sizeof(u[0]), sizeof(v)/sizeof(v[0]));
        uint64_t result[num_digits];
        subtract(num_digits, u, v, result);
        uint64_t expected[] = {135802467913580246, 401981997366651399};
        TEST_CHECK_(result[0] == expected[0], "subtract()[0]=%llu but expected %llu", result[0], expected[0]);
        TEST_CHECK_(result[1] == expected[1], "subtract()[1]=%llu but expected %llu", result[1], expected[1]);
    }
}

TEST_LIST = {
    {"test_sum", test_sum},
    {"test_subtract", test_subtract}
};
