#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//
#include "inter.h"
void coeff(_polynom *P, double *DD, int *X, int n) {
  P->coef[0] = DD[n - 1];
  for (int i = n - 2; i >= 0; i--) {
    for (int j = n - i - 1; j > 0; j--) {
      P->coef[j] = P->coef[j - 1] - X[i] * P->coef[j];
    }
    P->coef[0] = DD[i] - X[i] * P->coef[0];
  }
}
void dd(int *X, double *Y, double *M, int n) {
  for (int i = 0; i < n; i++)
    M[i] = Y[i];
  for (int i = 0; i < n - 1; i++) {
    for (int j = n - 1; j > i; j--) {
      M[j] = (double)(M[j] - M[j - 1]) / (X[j] - X[j - i - 1]);
    }
  }
}
double interpolate(double *DD, int *X, int n, double x) {
  double eval = 0;
  for (int i = n; i >= 0; i--) {
    eval = eval * (x - X[i]) + DD[i];
  }
  return eval;
}
/*
 * revoir le calcul des coefficients du polynome, différence divisée ok
 */
int main(int argc, char *argv[]) {
  (void)argc;
  int n;
  int *X;
  double *Y, *M;
  clock_t start, end;
  double cpu_time_used;
  ;
  FILE *f = fopen(argv[1], "r");
  FILE *f2 = fopen(argv[2], "w");
  fscanf(f, "%d", &n);
  X = malloc(n * sizeof *X);
  Y = malloc(n * sizeof *Y);
  getInfos(f, X, Y, n);
  _polynom *P = initPolynom(n - 1);
  M = malloc(n * sizeof *M);
  double *E = calloc(atoi(argv[3]), sizeof *E);
  double *XN = calloc(atoi(argv[3]), sizeof *XN);
  start = clock();
  dd(X, Y, M, n);
  coeff(P, M, X, n);
  for (int i = 0; i < P->deg + 1; i++)
    fprintf(stderr, "%e x**%d ", P->coef[i], i);
  int j = 0;
  int xMin = minList(X, n);
  int xMax = maxList(X, n);
  for (double x = xMin; x <= xMax; x += (xMax - xMin) / (atof(argv[3]))) {
    XN[j] = x;
    E[j] = interpolate(M, X, n, x);
    ++j;
  }
  serialize(f, f2, E, XN, M, n, atoi(argv[3]));
  end = clock();
  cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
  fprintf(stderr, "\n runtime: %f seconds\n", cpu_time_used);

  free(P->coef);
  free(P);
  free(X);
  free(Y);
  free(XN);
  free(E);
  fclose(f);
  fclose(f2);
  return 0;
}
