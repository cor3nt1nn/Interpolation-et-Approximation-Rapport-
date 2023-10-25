#ifndef SOURCE_H_
#define SOURCE_H_
/*
 * PRINT MATRIX WITH RIGHT FORMAT
 */
void printMatrix(float **matrix, int m, int p) {
  printf("PRINTING MATRIX FROM: %p LOCATION :\n", matrix);
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < p; j++) {
      (j <= p - 2) ? printf("%f ", matrix[i][j]) : printf("%f", matrix[i][j]);
    }
    puts("");
  }
}
/*
 * PRINT VECTOR WITH GOOD FORMAT:
 */
void printVect(float *V, int m) {
  printf("PRINTING VECTOR FROM: %p LOCATION :\n", V);
  for (int i = 0; i < m; i++) {
    (i <= m - 2) ? printf("%f ", V[i]) : printf("%f\n", V[i]);
  }
}
void copy(float *V, float *T, int n) {
  for (int i = 0; i < n; i++) {
    V[i] = T[i];
  }
}
/*
 * CALCULATE THE NORM OF A VECTOR
 */
double norm(float *b, int n) {
  double sum = 0;
  for (int i = 0; i < n; i++) {
    sum += b[i] * b[i];
  }
  sum = sqrt((double)sum);
  return sum;
}
/*
 * ALLOCATE MEMORY FOR VECTORS
 */
float *buildVect(int n) {
  float *V = calloc(n, sizeof *V);
  return V;
}
/*
 * ALLOCATE MEMORY FOR MATRIX
 */
float **allocate(int m, int n) {
  float **T = malloc(m * sizeof *T);
  for (int i = 0; i < m; i++) {
    T[i] = malloc(n * sizeof *T[i]);
    if (T[i] == NULL) {
      for (int j = 0; j < i; j++) {
        free(T[i]);
      }
      free(T);
      puts("ALLOCATION ERROR");
      exit(-1);
    }
  }
  return T;
}
/*
 * FILL MATRIX BY USER INPUTin
 */
void fillM(int m, int p, float **T) {
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < p; j++) {
      T[i][j] = 0;
      printf("Enter coefficient for %p[%d][%d]", T, i, j);
      scanf("%f", &T[i][j]);
    }
  }
}
/*
 * FREE MATRIX
 */
void freeAll(float **T, int m) {
  for (int i = 0; i < m; i++) {
    free(T[i]);
  }
  free(T);
}
/*
 * CREATE A VECTOR THAT IS THE RESULT OF V1-V2
 */
float *subVect(float *V1, float *V2, int m) {
  float *V3 = buildVect(m);
  for (int i = 0; i < m; i++) {
    V3[i] = V1[i] - V2[i];
  }
  return V3;
}
/*
 * ABSOLUTE VALUE FOR FLOAT
 */
float Fabs(float a) { return (a > 0) ? a : -a; }

/*
 * CALULATE A PART OF THE FORMULA THAT GIVES x_i^(k)
 * CREATED FOR LISIBILITY
 */
float jacobiSum(float **A, float *V, int m, int i) {
  float s = 0;
  for (int j = 0; j < m; j++) {
    if (j != i)
      s += A[i][j] * V[j];
  }
  return s;
}
/*
 * CALCULATION FOR ERROR BETWEEN TWO ITERATIONS
 * IT FOLLOWS THE FORMULA GIVEN IN THE SHEET
 */
float epsi(float *V, float *S, int n) {
  float max = Fabs(V[0] - S[0]);
  for (int i = 1; i < n; i++) {
    if (Fabs(S[i] - V[i]) > max)
      max = Fabs(S[i] - V[i]);
  }
  return max;
}
/*
 * IMPLEMENTATION OF '.' OPERATOR FOR MATRIX
 */
float **multiplication(float **M1, float **M2, int m, int q) {
  float **R = allocate(m, q);
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < q; j++) {
      for (int k = 0; k < q; k++) {
        R[i][j] += M1[i][k] * M2[k][j];
      }
    }
  }
  return R;
}
/*
 * IMPLEMENTATION OF '.' OPERATOR FOR MATRIX AND VECTORS
 */
float *multiplicationMV(float **M1, float *M2, int m) {
  float *R = buildVect(m);
  for (int i = 0; i < m; i++) {
    for (int k = 0; k < m; k++) {
      R[k] += M1[k][i] * M2[k];
    }
  }
  return R;
}
/*
 * INITIATE A VECTOR OF N ELEMENTS TO 1
 */
void fillOne(float *V, int m) {
  for (int i = 0; i < m; i++)
    V[i] = 1;
}
/*
 * DETERMINE IF JACOBI LEADS TO RESULTS BY CALCULATED IF A MATRIX A IS STRICTLY
 * DOMINANT DIAGONAL MATRIX
 */
int conv(float **A, int m) {
  float sl = 0;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < m; j++) {
      if (i != j)
        sl += fabs(A[i][j]);
    }
    if (A[i][i] - sl <= 0)
      return 0;
  }
  return 1;
}

/*
 * BUILD AUGMENTED MATRIX
 */
float **AugmentedMatrix(float **M1, float **M2, int m, int n) {
  float **A = allocate(m, m + 1);
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n + 1; j++) {
      (j != n) ? (A[i][j] = M1[i][j]) : (A[i][j] = M2[i][0]);
    }
  }
  return A;
}

#endif // SOURCE_H_
