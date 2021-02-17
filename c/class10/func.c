#include <stdio.h>

int main(void) {
    printLine('*');
    printf(" 프로그램의 결과를 보여주세요 \n");
    printf("%c", c);
    printLine('-');
    int a = 5, b = 3;
    printf("%15d + %5d = %d\n", a, b, a+b);
}
// 함수의 정의
void printLine(char c) {
    for (int i=0; i<40; i++)
        printf("%c", c);
    printf("\n");
}

