#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void generateMatrixCoefficient5(int m, int p) {
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < p; j++) {
      if (i == j) {
        puts("1");
      } else if (i == 1 || j == 1) {
        printf("%lf\n", pow(2, 1 - j));
      } else
        puts("0");
    }
  }
}
int main(int argc, char *argv[]) {
  (void)argc;
  puts("3\n3");
  puts("3\n1");
  generateMatrixCoefficient5(atoi(argv[1]), atoi(argv[2]));
  puts("1\n1\n1");
  return 0;
}
