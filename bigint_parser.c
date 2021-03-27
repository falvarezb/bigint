#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "bigint.h"
#include <assert.h>
#include <stdbool.h>

/*
    Copy the digits of 'big_digit' into the block of memory 'result' starting at 'offset'
    Copy is done backwards (right to left) so that leftmost digits are the most significant ones
    If number of digits is less than BASE_POWER, the result is padded with 0s to the left

    Given 123, and buffer "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"
                                     
                           ⟍|⟋ 
    #1: "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"
    #2: "xxxxxxxxxxxxxxxxxxx3xxxxxxxxxxxxxxxx"
    #3: "xxxxxxxxxxxxxxxxxx23xxxxxxxxxxxxxxxx"
    #4: "xxxxxxxxxxxxxxxxx123xxxxxxxxxxxxxxxx"
    #4: "xxxxxxxxxxxxxxxx0123xxxxxxxxxxxxxxxx"
    .........
    #BASE_EXP: "x000000000000000123xxxxxxxxxxxxxxxx"
*/
void build_bigint_str(char *result, int offset, uint64_t big_digit)
{
    for (int i = BASE_EXP - 1; i >= 0; i--)
    {
        int idx = offset + i;
        result[idx] = '0' + (big_digit % 10);
        big_digit /= 10;
    }
}

/*


    Build a string by copying the content of each big digit into the block of memory 'str'
    As bigint stores the data in little-endian, the copy is made backwards

    bigint[0] is the least significat digit
    bigint[i] i=0...n-2 have exactly BASE_EXP decimal digits
    bigint[n-1] has up to BASE_EXP decimal digits

    Given [123456789012345678,456],

    #1: "000000000000000456xxxxxxxxxxxxxxxxxx"
    #2: "000000000000000456123456789012345678"
*/
char *to_string(bigint_t bigint)
{
    char *str = (char *)malloc((bigint.num_digits * BASE_EXP + 1) * sizeof(char));
    if (str != NULL)
    {
        for (int j = 0; j < bigint.num_digits; j++)
        {
            uint64_t big_digit = bigint.number[bigint.num_digits - 1 - j];
            build_bigint_str(str, BASE_EXP * j, big_digit);
        }
        str[bigint.num_digits * BASE_EXP] = '\0';
    }
    return str;
}

/*
    Convert the chars in the region [offset, offset + n_digits) into an integer
*/
uint64_t build_bigint(char *str, int offset, int n_digits)
{
    uint64_t big_digit = 0;
    char c[2] = {'0', '\0'};
    int decimal_digit;

    for (int i = offset; i < (offset + n_digits); i++)
    {
        c[0] = str[i];
        decimal_digit = atoi(c);
        big_digit = big_digit * 10 + decimal_digit;
    }
    return big_digit;
}

/*
    bigint[0] is the least significat digit
    bigint[i] i=0...n-2 have exactly BASE_EXP decimal digits
    bigint[n-1] has up to BASE_EXP decimal digits

    The chars of 'str' are processed in blocks of BASE_EXP units, each block
    is converted into an integer stored in an element of an array

    "456123456789012345678" --> [123456789012345678,456]
*/
bigint_t from_string(char *str)
{
    int num_big_digits = strlen(str) / BASE_EXP;
    if (strlen(str) % BASE_EXP)
    { //digits of bigint[n-1]
        num_big_digits++;
    }

    uint64_t *bigint = (uint64_t *)malloc(num_big_digits * sizeof(uint64_t));
    if (bigint != NULL)
    {
        int big_digit_counter = num_big_digits - 1;

        //bigint[n-1]
        int num_msb_decimal_digits;
        if ((num_msb_decimal_digits = strlen(str) % BASE_EXP))
        {
            bigint[big_digit_counter--] = build_bigint(str, 0, num_msb_decimal_digits);
        }

        //bigint[0]...bigint[n-2]
        int str_idx = num_msb_decimal_digits;

        while (big_digit_counter >= 0)
        {
            bigint[big_digit_counter--] = build_bigint(str, str_idx, BASE_EXP);
            str_idx += BASE_EXP;
        }
    }

    bigint_t result = {bigint, num_big_digits};
    return result;
}

/*
    Adds as many zeroes as needed to the right to make size of bigint equal to num_digits 
*/
uint64_t *pad_bigint(int original_num_digits, int new_num_digits, uint64_t *bigint)
{
    assert(original_num_digits < new_num_digits);
    uint64_t *new_bigint = (uint64_t *)realloc(bigint, new_num_digits * sizeof(uint64_t));
    if (new_bigint != NULL)
    {
        for (int i = original_num_digits; i < new_num_digits; i++)
        {
            new_bigint[i] = 0;
        }
    }
    return new_bigint;
}

/*
    Adds as many zeroes as needed to the right so that both operands have the same length
*/
int pad_operands(bigint_t *bigint_a, bigint_t *bigint_b)
{
    bigint_t *least_bigint, *greatest_bigint;

    if (bigint_a->num_digits == bigint_b->num_digits)
    {
        return EXIT_SUCCESS;
    }
    else if (bigint_a->num_digits < bigint_b->num_digits)
    {
        least_bigint = bigint_a;
        greatest_bigint = bigint_b;
    }
    else
    {
        least_bigint = bigint_b;
        greatest_bigint = bigint_a;
    }

    uint64_t *padded_bigint = pad_bigint(least_bigint->num_digits, greatest_bigint->num_digits, least_bigint->number);
    if (padded_bigint != NULL)
    {
        least_bigint->number = padded_bigint;
        least_bigint->num_digits = greatest_bigint->num_digits;
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

char *remove_least_significant_zeros(char *str)
{
    char c;
    while ((c = *str++) == '0')
        ;

    if (*(str - 1) == '\0') //result is 0
        return str - 2;

    return str - 1;
}
