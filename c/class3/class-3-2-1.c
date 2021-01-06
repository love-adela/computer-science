#include <stdio.h>

int main(void) {
  /* 자료형 크기 알아보기 */
  int x;
  printf("변수 x의 크기       : %d\n", sizeof(x));   // 4
  printf("값 10의 크기        : %d\n", sizeof(10));  // 4
  printf("자료형 int의 크기   : %d\n", sizeof(int)); // 4

  double d;
  printf("변수 d의 크기       : %d\n", sizeof(d));   // 8
  printf("값 3.14의 크기        : %d\n", sizeof(3.14));  // 8
  printf("자료형 double의 크기   : %d\n", sizeof(double)); // 8

  char ch;
  printf("변수 ch의 크기       : %d\n", sizeof(ch));   // 1
  printf("값 'A'의 크기        : %d\n", sizeof('A'));  // 4 
  printf("자료형 double의 크기   : %d\n", sizeof(char)); // 1 

  printf("자료형 short의 크기: %d\n", sizeof(short));
  printf("자료형 int의 크기: %d\n", sizeof(int));
  printf("자료형 long의 크기: %d\n", sizeof(long));

  printf("자료형 float의 크기: %d\n", sizeof(float));
  printf("자료형 double의 크기: %d\n", sizeof(double));

  printf("자료형 char의 크기: %d\n", sizeof(char));
  
  return 0;
}
