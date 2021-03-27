#include "bigint.h"
#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <cmocka.h>
#include <math.h>


int setup(void** state){
    return 0;
}

int tear_down(void** state){
    return 0;
}

void test_runner(uint64_t u[], uint64_t v[], uint64_t result[], uint64_t expected[], size_t num_operands_digits, size_t num_result_digits, uint64_t* (*func_to_test)(int, uint64_t*, uint64_t*, uint64_t*)){
    (*func_to_test)(num_operands_digits, u, v, result);
    for (size_t i = 0; i < num_result_digits; i++)
        assert_int_equal(result[i], expected[i]);
}

void sum_trivial_case(void** state) 
{
    uint64_t u[] = {1};
    uint64_t v[] = {2};
    size_t num_digits = fmax(sizeof(u)/sizeof(u[0]), sizeof(v)/sizeof(v[0]));
    uint64_t result[num_digits+1];
    uint64_t expected[] = {3, 0};
    test_runner(u, v, result, expected, num_digits, num_digits+1, sum);
}

void sum_overflow(void** state) {
    uint64_t u[] = {123456789012345678lu, 576839484849498888lu};
    uint64_t v[] = {987654321098765432lu, 974857487482847488lu};
    int num_digits = fmax(sizeof(u)/sizeof(u[0]), sizeof(v)/sizeof(v[0]));
    uint64_t result[num_digits+1];
    uint64_t expected[] = {111111110111111110, 551696972332346377, 1};
    test_runner(u, v, result, expected, num_digits, num_digits+1, sum);
}

void subtract_positive_result(void** state){
    uint64_t u[] = {3};
    uint64_t v[] = {1};
    size_t num_digits = fmax(sizeof(u)/sizeof(u[0]), sizeof(v)/sizeof(v[0]));
    uint64_t result[num_digits];
    uint64_t expected[] = {2};
    test_runner(u, v, result, expected, num_digits, num_digits, subtract);
}

void subtract_zero_result(void** state){
    uint64_t u[] = {3};
    uint64_t v[] = {3};
    size_t num_digits = fmax(sizeof(u)/sizeof(u[0]), sizeof(v)/sizeof(v[0]));
    uint64_t result[num_digits];
    uint64_t expected[] = {0};
    test_runner(u, v, result, expected, num_digits, num_digits, subtract);
}

void subtract_multiple_digits(void** state){
    uint64_t u[] = {123456789012345678lu, 576839484849498888lu};
    uint64_t v[] = {987654321098765432lu, 174857487482847488lu};
    size_t num_digits = fmax(sizeof(u)/sizeof(u[0]), sizeof(v)/sizeof(v[0]));
    uint64_t result[num_digits];
    uint64_t expected[] = {135802467913580246, 401981997366651399};
    test_runner(u, v, result, expected, num_digits, num_digits, subtract);
}

int main(int argc, char const *argv[])
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(sum_trivial_case),
        cmocka_unit_test(sum_overflow),
        cmocka_unit_test(subtract_positive_result),
        cmocka_unit_test(subtract_zero_result),
        cmocka_unit_test(subtract_multiple_digits)
    };
    return cmocka_run_group_tests(tests, setup, tear_down);
}
