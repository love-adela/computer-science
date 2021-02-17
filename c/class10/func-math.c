#include <stdio.h>
#include <math.h>

int main(void) {
    int a = 10;
    int b = 3;
    int c = 25;
    double result = pow(a, b); // 1000
    double sqrt_res = sqrt(c);

    printf("%d의 %d승 = %5.0f\n", a, b, result);
    printf("%d의 제곱근 = %5.0f\n", c, result);

    return 0;
}
