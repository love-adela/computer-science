#include <stdio.h>

int main(void) {
  int a = 10, b = 10;
  int x, y;

  // 전위 연산 결과
  // x = ++a;
  // y = --b;
  // printf("a = %d, b = %d\n", a, b); // a=11,b=9
  // printf("x = %d, y = %d\n", x, y); // x=11,y=9

  // 후위 연산 결과 
  //   x = a++;
  //   y = b--;
  //   printf("a = %d, b = %d\n", a, b); // a=11, b=9
  //   printf("x = %d, y = %d\n", x, y); // x=10, y=10
  
  // 전위 연산자와 후위 연산자 합쳐 쓰기
  //   x = ++a;
  //   y = b++;
  //   printf("a=%d, b=%d\n", a,b); // a=11, b=11
  //   printf("x=%d, y=%d\n", x,y); // x=11, y=10

  x = 10, y = 10;
  printf("=============\n");
  printf("  x = %d\n", x);        // x = 10
  printf("++x = %d\n", ++x);      // ++x = 11
  printf("  x = %d\n", x);        // x = 11
  printf("=============\n");
  printf("=============\n");
  printf("  y = %d\n", y);        // y = 10
  printf("y++ = %d\n", y++);      // y++ = 10
  printf("  y = %d\n", y);        // y = 11
  printf("=============\n");

  return 0;
}

