#include "acutest.h"
#include "bigint.h"
#include <stddef.h>
#include <math.h>
#include <string.h>

void test_bigsum(){
    {
        char* a = "125858548944446868589689484398988889";
        char* b= "4404588898938984849498448948989";
        char* expected = "125862953533345807574538982847937878";
        char* result = bigsum(a, b);
        TEST_CHECK_(strcmp(result, expected) == 0, "bigsum(%s, %s)=%s but expected %s", a, b, result, expected);
    }

    {
        char* a = "-1";
        char* b= "12";
        char* expected = "13";
        char* result = bigsum(a, b);
        TEST_CHECK_(strcmp(result, expected) == 0, "bigsum(%s, %s)=%s but expected %s", a, b, result, expected);
    }

    {
        char* a = "0";
        char* b= "0";
        char* expected = "0";
        char* result = bigsum(a, b);
        TEST_CHECK_(strcmp(result, expected) == 0, "bigsum(%s, %s)=%s but expected %s", a, b, result, expected);
    }

    {
        char* a = "1";
        char* b= "1843947378473748483873478";
        char* expected = "1843947378473748483873479";
        char* result = bigsum(a, b);
        TEST_CHECK_(strcmp(result, expected) == 0, "bigsum(%s, %s)=%s but expected %s", a, b, result, expected);
    }

    {
        char* a = "1843947378473748483873478";
        char* b= "1";
        char* expected = "1843947378473748483873479";
        char* result = bigsum(a, b);
        TEST_CHECK_(strcmp(result, expected) == 0, "bigsum(%s, %s)=%s but expected %s", a, b, result, expected);
    }
}

void test_bigsubtract(){
    {
        char* a = "125858548944446868589689484398988889";
        char* b= "4404588898938984849498448948989";
        char* expected = "125854144355547929604839985950039900";
        char* result = bigsubtract(a, b);
        TEST_CHECK_(strcmp(result, expected) == 0, "bigsubtract(%s, %s)=%s but expected %s", a, b, result, expected);
    }

    {
        char* a = "1";
        char* b= "12";
        char* expected = "-11";
        char* result = bigsubtract(a, b);
        TEST_CHECK_(strcmp(result, expected) == 0, "bigsubtract(%s, %s)=%s but expected %s", a, b, result, expected);
    }

    {
        char* a = "12";
        char* b= "12";
        char* expected = "0";
        char* result = bigsubtract(a, b);
        TEST_CHECK_(strcmp(result, expected) == 0, "bigsubtract(%s, %s)=%s but expected %s", a, b, result, expected);
    }

     {
        char* a = "1";
        char* b= "1843947378473748483873478";
        char* expected = "-1843947378473748483873477";
        char* result = bigsubtract(a, b);
        TEST_CHECK_(strcmp(result, expected) == 0, "bigsum(%s, %s)=%s but expected %s", a, b, result, expected);
    }

    {
        char* a = "1843947378473748483873478";
        char* b= "1";
        char* expected = "1843947378473748483873477";
        char* result = bigsubtract(a, b);
        TEST_CHECK_(strcmp(result, expected) == 0, "bigsum(%s, %s)=%s but expected %s", a, b, result, expected);
    }
}

TEST_LIST = {
    {"test_bigsum", test_bigsum},
    {"test_bigsubtract", test_bigsubtract}
};
