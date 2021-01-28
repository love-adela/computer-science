#include <stdio.h>

int main(void) {
  int n;
  printf("1에서 4 사이의 정수를 입력하세요\n");
  scanf("%d", &n);
  switch (n) {
    case 1:
      printf("melon\n");
      break;
    case 2:
      printf("apple\n");
      break;
    case 3:
      printf("grape\n");
      break;
    case 4:
      printf("watermelon\n");
      break;
    default: printf("1에서 4 사이의 정수만 입력하세요:");
  }
  return 0;
}
