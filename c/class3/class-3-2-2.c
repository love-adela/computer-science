#include <stdio.h>

int main(void) {
  /* char 정수형 실습 */
  char c1 ='A';
  char c2 = 65;

  printf("%d(%d)\n", c1, c1); // 65(65)
  printf("%c(%d)\n", c1, c1); // A(65)
  printf("%c(%d)\n", c2, c2); // A(65)

  printf("%3c-%3c-%3c\n", c1, c1+1, c1+2); //  A- B- C
  printf("%3d-%3d-%3d\n", c1, c1+1, c1+2); // 65-66-67
  return 0;
}
