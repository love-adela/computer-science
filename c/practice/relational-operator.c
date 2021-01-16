#include <stdio.h>

int main(void) {
  int x= 0;
  printf("%d\n", x++);
  if (++x < 5) {
    printf("%d", x);
  }
  return 0;
}
