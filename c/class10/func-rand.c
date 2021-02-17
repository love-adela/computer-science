#include <stdio.h>
#include <stdlib.h>

int main(void) {
    for (int i=1; i<=5; i++)
        printf("%d회 난수 = %5d\n", i, (rand()%10+1));

    return 0;
}
