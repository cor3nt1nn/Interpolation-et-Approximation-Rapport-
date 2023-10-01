#include <stdio.h>
#include <stdlib.h>

void genM6Coeff(int m, int p) {
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < p; j++) {
      if (i == j) {
        puts("3");
      } else if (j == i + 1 && i < p) {
        puts("-1");
      } else if (j == i - 1 && i > 1) {
        puts("-2");
      } else
        puts("0");
    }
  }
}

int main() {
  puts("3\n3\n3\n1");
  genM6Coeff(3, 3);
  puts("1\n1\n1");
  return 0;
}
