#include <stdio.h>
#include <stdlib.h>

void genM6Coeff(int m, int p) {
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < p; j++) {
      if (i == j) {
        puts("3");
      } else if (j == i + 1 && i < p - 1) {
        puts("-1");
      } else if (j == i - 1 && i > 0) {
        puts("-2");
      } else
        puts("0");
    }
  }
}

int main(int argc, char *argv[]) {
  (void)argc;
  puts("6\n6");
  genM6Coeff(atoi(argv[1]), atoi(argv[1]));
  return 0;
}
