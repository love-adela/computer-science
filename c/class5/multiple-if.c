#include <stdio.h>
int main(void) {
  int x;
  printf("정수 입력: ");
  scanf("%d", &x);

  if (x>0) {
    printf("%d=> 양수\n", x);
  }
  return 0;
}
