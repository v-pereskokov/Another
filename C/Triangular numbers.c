#include <stdio.h>
#include <math.h>
#include <ctype.h>

#define LONG_MAX 9223372036854775807L
typedef __int64_t int64;

int triangular_number(const int64 target)
{
    int sqrt_value = (int)sqrt(2 * target);
    if (sqrt_value + pow(sqrt_value, 2) == 2 * target)
        return sqrt_value;
    return 0;
}

int main()
{
    int64 target;
    scanf("%lld", &target);
    if (target >= 1 && target <= LONG_MAX && !isalpha(target)) {
        printf("%d", triangular_number(target));
    }
    else
        printf("0");
    printf("\n");
    return 0;
}
