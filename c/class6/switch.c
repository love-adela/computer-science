#include <stdio.h>

int main(void) {
  int n;
  scanf("%d", &n);
  switch (n) {
    case 1:
      printf("1번 \n");
      break;
    case 2:
      printf("2번 \n");
      break;
    case 3:
      printf("3번 \n");
      break;
    default: printf("1에서 3 사이의 정수를 입력하세요:");
  }
  return 0;
}
