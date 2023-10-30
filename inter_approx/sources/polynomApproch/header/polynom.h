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
    for (int i = 0; i < poly.degree+1; i++) {
        printf("%f ", poly.coefficients[i]);
    }
    puts("");
}

void printPolynomIntoFile(_polynom poly, FILE* fd) {
    for (int i = poly.degree; i >=0; i--) {
        printf("%f ", poly.coefficients[i]);
        fprintf(fd, "%f ", poly.coefficients[i]);
    }
    puts("");
    fprintf(fd, "\n");
}

void printPolynomial(float* coefficients, int degree) {
    puts("");
    int i;
    int firstTerm = 1;  // Pour gérer le premier terme
    for (i = degree; i >= 0; i--) {
        if (coefficients[i] != 0.0f) {
            // Gestion du signe
            if (coefficients[i] > 0.0f && !firstTerm) {
                printf(" + ");
            } else if (coefficients[i] < 0.0f && !firstTerm) {
                printf(" - ");
            }
            
            // Gestion du coefficient
            float coefficient = (coefficients[i] > 0.0f) ? coefficients[i] : -coefficients[i];
            if (coefficient != 1.0f || i == 0) {
                printf("%.6f", coefficient);
            }

            // Gestion de l'exposant
            if (i > 1) {
                printf("x^%d", i);
            } else if (i == 1) {
                printf("x");
            }

            firstTerm = 0;  // Le premier terme a été affiché
        }
    }

    if (firstTerm) {
        // Cas où le polynôme est nul
        printf("0");
    }

    printf("\n");
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

_polynom addPolynom(_polynom pol1, _polynom pol2_dest){
    for (int k=0; k<pol1.degree+1; k++){
        pol2_dest.coefficients[k]+=pol1.coefficients[k];
    }
    return pol2_dest;
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

_polynom* createPolynomArray(int nbPoints) {
    _polynom* polyArray = NULL;
    polyArray = malloc((nbPoints) * sizeof(_polynom));
    if (polyArray == NULL) {
        return NULL;
    }
    for (int i = 0; i < nbPoints; i++) {
        polyArray[i] = createPolynom(nbPoints-1-i);
        if (polyArray[i].coefficients == NULL) {
            for (int j = 0; j < i; j++) {
                freePolynom(polyArray[j]);
            }
            return NULL;
        }
    }
    return polyArray;
}

void printPolynomArray(_polynom* polyArray, int nbPoints) {
    for (int i = 0; i < nbPoints; i++) {
        printPolynom(polyArray[i]);
    }
}

void freePolynomArray(_polynom* polyArray, int nbPoints) {
    for (int i = 0; i < nbPoints; i++) {
        freePolynom(polyArray[i]);
    }
    free(polyArray);
}
