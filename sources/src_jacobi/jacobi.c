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
  float *cp = malloc(n * sizeof *cp);
  while (k < bound && epsilon >= minErr) {
    fprintf(stderr, "%f ", epsilon);
    // printf("EPSILON : %f\n", epsilon);
    copy(cp, vector, n);
    for (int i = 0; i < n; i++) {
      vector[i] = (1 / A[i][i]) * (b[i] - jacobiSum(A, cp, n, i));
    }
    epsilon = epsi(vector, S, n);
    k++;
  }
  free(cp);
  return k;
}
int main(int argc, char *argv[]) {
  int m, p; // maxIter;
  // float minErr;
  (void)argc;
  puts("A matrix dimensions: ");
  scanf("%d%d", &m, &p);
  float *ones =
      buildVect(m); // build the vector of m dimensions that is composed of 1
  float *X = buildVect(m); // Build the X_0 vector, already init to 0 by the
                           // calloc is source file
  fillOne(ones, m);
  float **A = allocate(m, p);
  fillM(m, p, A);
  float *b =
      multiplicationMV(A, ones, m); // FIND B matrix by using the A matrix and
                                    // the matrix that is composed only of ones
  // puts("inputs for max Error and max Iteration");
  //  scanf("%f%d", &minErr, &maxIter);
  printf("\n ===== CONVERGENCE PREDICTION: %s =====\n",
         (conv(A, m) == 1)
             ? ("conv")
             : ("may not conv")); // for user comfort to have a prediction of
                                  // the result validity
  int count =
      jacobi(A, X, b, ones, m, atof(argv[1]),
             atoi(argv[2])); // call jaocobi and count the number of iterations
                             // done and used minErr and bound as program params
  fprintf(stderr, "\n%d\n", count); // in stderr to produce some graphs
  printVect(X, m);
  printf("EPSILON CALCULATED %d:", count);
  freeAll(A, m);
  free(X);
  free(b);
  free(ones);
  return 0;
}
