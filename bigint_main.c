#include <stdio.h>
#include "bigint.h"


int main(int argc, char const *argv[]) {
    char *result = bigsubtract("1", "1843947378473748483873478");
    printf("result=%s\n", result);
    return 0;
}