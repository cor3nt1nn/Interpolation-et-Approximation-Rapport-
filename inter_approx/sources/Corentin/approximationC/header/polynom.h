typedef struct _polynom {
    int degree;
    double* coefficients;
} _polynom;

_polynom createPolynom(int degree) {
    _polynom poly;
    poly.degree = degree;
    poly.coefficients = malloc((degree+1) * sizeof(double));
    for (int i = 0; i < poly.degree+1; i++) {
        poly.coefficients[i] = 0;
    }
    return poly;
}

void freePolynom(_polynom poly) {
    free(poly.coefficients);
    poly.coefficients = NULL;
}
