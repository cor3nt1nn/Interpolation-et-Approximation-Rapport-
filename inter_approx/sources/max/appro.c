#include <stdio.h>
#include <stdlib.h>

void getInfos(FILE *f, int *X, float *Y, int n) {
  for (int i = 0; i < n; i++)
    fscanf(f, "%f", &X[i]);
  for (int i = 0; i < n; i++)
    fscanf(f, "%f", &Y[i]);
}
float Favg(float *Y, int n) {
  float s = 0;
  for (int i = 0; i < n; i++) {
    s += Y[i];
  }
  return s / n;
}
void multiply(float *M, float *X, float *Y, int n) {
  for (int i = 0; i < n; i++) {
    M[i] = X[i] * Y[i];
  }
}
void add(float *A, float *X, float *Y, int n) {
  for (int i = 0; i < n; i++)
    A[i] = X[i] + Y[i];
}
void square(float *S, float *X, int n) {
  for (int i = 0; i < n; i++)
    S[i] = X[i] * X[i];
}
float *linear_regression(float *X, float *Y, int n) {
  float *equa, *M, *A, *S;
  equa = calloc(2, sizeof *equa);
  M = calloc(n, sizeof *M);
  A = calloc(n, sizeof *A);
  S = calloc(n, sizeof *S);

  multiply(M, X, Y, n);
  add(A, X, Y, n);
  square(S, X, n);
  equa[1] = (Favg(M, n) - Favg(X, n) * Favg(Y, n)) /
            (Favg(S, n) - Favg(X, n) * Favg(X, n));
  equa[0] = (Favg(Y, n) * Favg(S, n) - Favg(X, n) * Favg(M, n)) /
            (Favg(S, n) - Favg(X, n) * Favg(X, n));
  return equa;
}

float *evaluate(float *X, float *Y, float (*expr)(float *, float *, int),
                int n) {
  float *R = calloc(n, sizeof *R);
  for (int i = 0; i < n; i++)
    R[i] = expr(X, Y, n);
  return R;
}

int main(int argc, char *argv[]) {
  (void)argc;
  FILE *f = fopen(argv[1], "r");
  int n;
  fscanf(f, "%d", &n);
  int *X = calloc(n, sizeof *X);
  float *Y = calloc(n, sizeof *Y);
  getInfos(f, X, Y, n);
  fclose(f);
  return 0;
}
