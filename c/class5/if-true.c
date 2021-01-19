#include <stdio.h>
int main(void) {
  int x, y;

  printf("첫번째 수: ");
  scanf("%d", &x);
  printf("두번째 수: ");
  scanf("%d", &y);

  printf("큰수: %d\n", (x>y) ? x : y);
  printf("작은수: %d\n", (x<y) ? x : y);

  if (x>y){
    printf("큰 수:%d\n 작은수:%d\n", x, y);
  } if (x==y) {
    printf("%d와 %d\n는 같습니다.", x, y);
  } else {
    printf("큰 수:%d\n작은수:%d\n", y, x);
  }

  // True
  // if (1) {
  //  printf("Hi");
  // }
  // False
  // if (0) {
  //   printf("No");
  // }
  return 0;
}

