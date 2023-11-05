#ifndef INTER_H_
#define INTER_H_
typedef struct _polynom {
  int deg;
  double *coef;
} _polynom;
_polynom *initPolynom(int n) {
  _polynom *_P = malloc(sizeof *_P);
  _P->deg = n;
  _P->coef = calloc(n, sizeof *_P->coef);
  return _P;
}
void serialize(FILE *f1, FILE *f2, double *E, double *XN, double *DD, int n,
               int eval) {
  fseek(f1, 0, SEEK_SET);
  char *s = malloc(
      20 * sizeof *s); // assuming that e notation not bigger than 20 char
  float c;
  int j = 0;
  fscanf(f1, "%e", &c); // dropping the n parameter
  while (fscanf(f1, "%e ", &c) != EOF) {
    if (j == n)
      putc('\n', f2);
    fprintf(f2, "%e ", c);
    j++;
  }
  putc('\n', f2);
  // put polynom coefficients
  for (int i = 0; i < eval + 1; i++) {
    int a = sprintf(s, "%e ", E[i]);
    s = realloc(s, a);
    fwrite(s, sizeof *s, a, f2);
  }
  putc('\n', f2);
  // put polynom coefficients
  for (int i = 0; i < eval + 1; i++) {
    int a = sprintf(s, "%e ", XN[i]);
    s = realloc(s, a);
    fwrite(s, sizeof *s, a, f2);
  }
  putc('\n', f2);
  for (int i = 0; i < n; i++) {
    int a = sprintf(s, "%e ", DD[i]);
    s = realloc(s, a);
    fwrite(s, sizeof *s, a, f2);
  }

  free(s);
}

int max(int a, int b) { return (a > b) ? a : b; }
int min(int a, int b) { return (a < b) ? a : b; }
float *evaluate(_polynom *P, float *T, int n) {
  float *I = calloc(n, sizeof *I);
  for (int i = 0; i < P->deg + 1; i++) {
    I[i] = P->coef[i] * pow(T[i], P->deg + 1 - i);
  }
  return I;
}
int minList(int *L, int n) {
  int min = L[0];
  for (int i = 0; i < n; i++)
    if (L[i] < min)
      min = L[i];
  return min;
}
int maxList(int *L, int n) {
  int max = L[0];
  for (int i = 0; i < n; i++)
    if (L[i] > max)
      max = L[i];
  return max;
}
_polynom *mult(_polynom *P, _polynom *Q) {
  _polynom *K = initPolynom(P->deg + Q->deg);
  int N = min(P->deg, Q->deg);
  int M = max(P->deg, Q->deg);
  _polynom *Max = (min(P->deg, Q->deg) == P->deg) ? Q : P;
  _polynom *Min = (min(P->deg, Q->deg) == P->deg) ? P : Q;
  for (int i = N; i >= 0; i--) {
    for (int j = M; j >= 0; j--) {
      K->coef[i + j] += Min->coef[i] * Max->coef[j];
    }
  }
  return K;
}
_polynom *add(_polynom *P, _polynom *P1) {
  int N = min(P->deg, P1->deg);
  int M = max(P->deg, P1->deg);
  _polynom *MP = (M == P1->deg) ? P1 : P;
  _polynom *A = initPolynom(M);
  for (int i = 0; i < N; i++) {
    A->coef[i] = P->coef[i] + P1->coef[i];
  }
  for (int i = N; i < M; i++) {
    A[i] = MP[i];
  }
  return A;
}

void getInfos(FILE *f, int *X, double *Y, int n) {
  for (int i = 0; i < n; i++)
    fscanf(f, "%d", &X[i]);
  for (int i = 0; i < n; i++)
    fscanf(f, "%lf", &Y[i]);
}
void printInfos(int *X, float *Y, int n) {
  for (int i = 0; i < n + 1; i++)
    printf("X_%d = %d\n Y_%i = %f\n", i, X[i], i, Y[i]);
}

#endif // INTER_H_
