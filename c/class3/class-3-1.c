#include <stdio.h>
// #define EX_RATE 1120 // #define으로 상수 선언

int main(void) {
  // 변수 선언 연습
  int iData = 50;
  double dData = 7.7 ;
  char ch = 'A';
  const int EX_RATE = 1100;

  printf("iData = %8d \n", iData);
  printf("dData = %8.2f \n", dData);
  printf("ch    = %8c \n", ch);

  // 10진수, 8진수, 16진수 예제
  int x = 10; // 10진수

  printf("%d = %d(%d) \n", x, x, 10);
  printf("%d = %o(%d) \n", x, x, 8);
  printf("%d = %x(%d) \n", x, x, 16);

  // 상수가 필요할 때의 예제
  int dollar1 = 10;
  int dollar2 = 100;
  int dollar3 = 1000;

//  int won1 = 1120 * dollar1;
//  int won2 = 1120 * dollar2;
//  int won3 = 1120 * dollar3;

  int won1 = EX_RATE * dollar1;
  int won2 = EX_RATE * dollar2;
  int won3 = EX_RATE * dollar3;

  printf("%d원 = %d달러 \n", won1, dollar1);
  printf("%d원 = %d달러 \n", won2, dollar2);
  printf("%d원 = %d달러 \n", won3, dollar3);

  return 0;
}
