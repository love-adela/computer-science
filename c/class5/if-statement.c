#include <stdio.h>

int main(void) {
  // if - else문 
  int num;

  printf("정수 입력: ");
  scanf("%d", &num);
  if (num > 0) {
    printf("%d는 양수입니다.\n", num);
  } else {
    printf("%d는 음수입니다.\n", num);
  }
  return 0;
}
