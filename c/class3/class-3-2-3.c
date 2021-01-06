#include <stdio.h>

int main(void) {
  float x = 1.23456e-38;
  float y = 1.23456e-38;
  double z = 1.23456e-46;

  printf("e\n", x); // e
  printf("e\n", y); // e
  printf("e\n", z); // e

  return 0;
}
