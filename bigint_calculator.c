#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "bigint.h"
#include <assert.h>
#include <stdbool.h>


/*
    bigint_a >= bigint_b ?
*/
bool is_gte(bigint_t bigint_a, bigint_t bigint_b)
{
    if (bigint_a.num_digits > bigint_b.num_digits)
        return true;
    if (bigint_a.num_digits < bigint_b.num_digits)
        return false;

    int j = bigint_a.num_digits - 1;
    while (j >= 0 && bigint_a.number[j] == bigint_b.number[j])
        j--;

    return (j == -1) || (bigint_a.number[j] > bigint_b.number[j]);
}

char *bigsum(char *a, char *b)
{
    bigint_t bigint_a = from_string(a);
    if (bigint_a.number == NULL)
        return NULL;
    bigint_t bigint_b = from_string(b);
    if (bigint_b.number == NULL)
        return NULL;

    if (pad_operands(&bigint_a, &bigint_b) == EXIT_FAILURE)
        return NULL;

    assert(bigint_a.num_digits == bigint_b.num_digits);
    size_t result_size = bigint_a.num_digits + 1; //extra digit for the final carry
    uint64_t result[result_size];

    sum(bigint_a.num_digits, bigint_a.number, bigint_b.number, result);
    return remove_least_significant_zeros(to_string((bigint_t){result, result_size}));
}

/*
    a - b
*/
char *bigsubtract(char *a, char *b)
{
    bigint_t bigint_a = from_string(a);
    if (bigint_a.number == NULL)
        return NULL;
    bigint_t bigint_b = from_string(b);
    if (bigint_b.number == NULL)
        return NULL;

    bigint_t greatest_operand, least_operand;
    char sign;

    if (is_gte(bigint_a, bigint_b))
    {
        greatest_operand = bigint_a;
        least_operand = bigint_b;
        sign = '+';
    }
    else
    {
        greatest_operand = bigint_b;
        least_operand = bigint_a;
        sign = '-';
    }

    if (pad_operands(&greatest_operand, &least_operand) == EXIT_FAILURE)
        return NULL;

    assert(greatest_operand.num_digits == least_operand.num_digits);
    size_t result_size = greatest_operand.num_digits;
    uint64_t result[result_size];

    subtract(greatest_operand.num_digits, greatest_operand.number, least_operand.number, result);
    char *result_str = to_string((bigint_t){result, result_size});
    char *prettified_result = remove_least_significant_zeros(result_str);

    if (sign == '+')
        return prettified_result;

    char *signed_result = (char *)malloc((strlen(prettified_result) + 2) * sizeof(char));
    signed_result[0] = '-';
    signed_result[1] = '\0';
    strcat(signed_result, prettified_result);
    free(result_str);
    return signed_result;
}
