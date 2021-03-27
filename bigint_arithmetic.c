#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "bigint.h"
#include <assert.h>
#include <stdbool.h>

/*
    Basic operations to perform arbitrary-precision arithmetic 

    * base = 10^BASE_EXP
    * in this base, individual digits are values in the range [0, 10^BASE_EXP-1]
    * numbers are represented as arrays of digits using little-endian representation, 
      in other words, u[0] contains the least significant digit
    * the only limitation to the number of digits is the physical memory of the machine
*/


/*
    classical algorithm of the sum
    * w = u + v
    * w has one more digit than u and v to store the final carry (either 0 or 1)
*/
uint64_t *sum(int num_digits, uint64_t *u, uint64_t *v, uint64_t *w)
{
    int carry = 0;
    for (int i = 0; i < num_digits; i++)
    {
        w[i] = u[i] + v[i] + carry;
        carry = 0;
        if (w[i] >= BASE)
        { //overflow
            w[i] -= BASE;
            carry = 1;
        }
    }
    w[num_digits] = carry;
    return w;
}

/*
    classical algorithm of the subtraction)
    * w = u - v, where u >= v
*/
uint64_t *subtract(int num_digits, uint64_t *u, uint64_t *v, uint64_t *w)
{
    int borrow = 0;
    for (int i = 0; i < num_digits; i++)
    {
        uint64_t subtrahend = v[i] + borrow;
        borrow = 0;
        if (u[i] < subtrahend)
        { //overflow
            w[i] = u[i] + BASE - subtrahend;
            borrow = 1;
        }
        else
        {
            w[i] = u[i] - subtrahend;
        }
    }
    return w;
}
