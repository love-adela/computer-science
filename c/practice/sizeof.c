#include <stdio.h>

int main() {
  union ex{
    char c;
    int n;
  }e;
  printf("%lu", sizeof(e));
  return 0;
}
