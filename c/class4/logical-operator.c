#include <stdio.h>

int main(void) {
  int x,y;

  printf("정수를 한번씩 입력하고 enter 또는 spacebar를 친 후 한 번 더 입력하세요:");
  scanf("%d", &x);
  scanf("%d", &y);

  printf("x==y의 결과: %d\n", x == y);
  printf("x!=y의 결과: %d\n", x != y);
  printf("x>y의 결과: %d\n", x > y);  
  printf("x<y의 결과: %d\n", x < y);  
  printf("x>=y의 결과: %d\n", x >= y);
  printf("x<=y의 결과: %d\n", x <= y);
  printf("큰 수 = %d\n", (x > y) ? x : y);
  printf("작은 수 = %d\n", (x < y) ? x : y);

  return 0;
}
