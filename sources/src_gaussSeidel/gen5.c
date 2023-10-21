#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void generateMatrixCoefficient5(int m, int p) {
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < p; j++) {
      if (i == j) {
        puts("1");
      } 
      else if (j==0){ 
        printf("%f\n", pow(2, 1 - (i+1)));
      }
      else if (i==0){
        printf("%f\n", pow(2, 1 - (j+1)));
      }
      else{
        puts("0");
      }
    }
    }
}
int main(int argc, char *argv[]) {
  (void)argc;
  puts("6\n6");
  generateMatrixCoefficient5(6,6);
  return 0;
}
