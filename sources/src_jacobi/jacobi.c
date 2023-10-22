#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//
#include "source.h"
//
//
/*
 * Jacobi function with minError and iterations number modifable
 */
int jacobi(float **A, float *vector, float *b, float *S, int n, float minErr,
           int bound) {
  float epsilon = epsi(S, vector, n);
  int k = 0;
  while (k < bound && epsilon >= minErr) {
    fprintf(stderr, "%0.6f ", epsilon);
    // printf("EPSILON : %f\n", epsilon);
    for (int i = 0; i < n; i++) {
      vector[i] = (1 / A[i][i]) * (b[i] - jacobiSum(A, vector, n, i));
    }
    epsilon = epsi(vector, S, n);
    k++;
  }
  return k;
}
int main(int argc, char *argv[]) {
  int m, p; // maxIter;
  // float minErr;
  (void)argc;
  puts("A matrix dimensions: ");
  scanf("%d%d", &m, &p);
  float *ones = buildVect(m);
  float *X = buildVect(m);
  fillOne(ones, m);
  float **A = allocate(m, p);
  fillM(m, p, A);
  float *b = multiplicationMV(A, ones, m);
  puts("inputs for max Error and max Iteration");
  // scanf("%f%d", &minErr, &maxIter);
  printf("\n ===== CONVERGENCE PREDICTION: %s =====\n",
         (conv(A, m) == 1) ? ("conv") : ("may not conv"));
  int count = jacobi(A, X, b, ones, m, atof(argv[1]), atoi(argv[2]));
  fprintf(stderr, "\n%d", count);
  printf("EPSILON CALCULATED %d:", count);
  freeAll(A, m);
  free(X);
  free(b);
  free(ones);
  return 0;
}
