typedef struct _polynom {
    int degree;
    float* coefficients;
} _polynom;

_polynom createPolynom(int degree) {
    _polynom poly;
    poly.degree = degree;
    poly.coefficients = malloc((degree+1) * sizeof(float));
    for (int i = 0; i < poly.degree+1; i++) {
        poly.coefficients[i] = 0;
    }
    return poly;
}

void printPolynom(_polynom poly) {
    puts("");
    for (int i = 0; i < poly.degree+1; i++) {
        printf("%lf ", poly.coefficients[i]);
    }
    puts("");
}

_polynom multPolynom(_polynom pol1, _polynom pol2, _polynom dest){
    float temp=0;
    for(int k=dest.degree; k>0; k--){
        dest.coefficients[k]=pol2.coefficients[k-1]*pol1.coefficients[1]+(temp*pol1.coefficients[0]);
        temp=pol2.coefficients[k-1];
    }
    dest.coefficients[0]=pol2.coefficients[0]*pol1.coefficients[0];
    return dest;
}

_polynom addPolynom(_polynom pol1, _polynom pol2, _polynom dest){
    for (int k=0; k<pol1.degree+1; k++){
        dest.coefficients[k]=pol2.coefficients[k]+pol1.coefficients[k];
    }
    return dest;
}

_polynom divisePolynom(_polynom pol1, float denom, _polynom dest){
    for (int k=0; k<pol1.degree+1; k++){
        dest.coefficients[k]=pol1.coefficients[k]/denom;
    }
    return dest;
}

void freePolynom(_polynom poly) {
    free(poly.coefficients);
    poly.coefficients = NULL;
}
