#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "header/matrix.h"
#include "header/polynom.h"

float* getMeans(float** data, int n) {
    float* result = malloc(4 * sizeof(float));
    float sumX = 0, sumY = 0, sumX2 = 0, sumXY = 0;

    for (int i = 0; i < n; i++) {
        float x = data[0][i];
        float y = data[1][i];

        sumX += x;
        sumY += y;
        sumX2 += x * x;
        sumXY += x * y;
    }

    result[0] = sumX / n;
    result[1] = sumY / n;
    result[2] = sumX2 / n;
    result[3] = sumXY / n;

    return result;
}

void printPolynomials(_polynom polynom, char type){
    if(type=='l'){
        printf("y=%fx+%f\n", polynom.coefficients[1], polynom.coefficients[0]);
    }
    if(type=='e'){
        printf("y=%fexp(%fx)\n", polynom.coefficients[0], polynom.coefficients[1]);
    }
    if(type=='p'){
        printf("y=%fx^%f\n", polynom.coefficients[0], polynom.coefficients[1]);
    }
}

_polynom computeLinearPolynom(float** data, int n) {
    _polynom polynom = createPolynom(1);
    float* meanValues = getMeans(data, n);
    polynom.coefficients[0] = ((meanValues[1] * meanValues[2]) - (meanValues[0] * meanValues[3])) /
                                  (meanValues[2] - (meanValues[0] * meanValues[0]));
    polynom.coefficients[1] = (meanValues[3] - (meanValues[0] * meanValues[1])) /
                                  (meanValues[2] - (meanValues[0] * meanValues[0]));
    
    free(meanValues);
    return polynom;
}

float evaluatePolynom(_polynom polynom, float abs, char type) {
    if(type=='l'){
        return polynom.coefficients[1] * abs + polynom.coefficients[0];
    }
    if(type=='e'){
        return polynom.coefficients[0] * expf(polynom.coefficients[1] * abs);
    }
    if(type=='p'){
        return polynom.coefficients[0]* pow(abs, polynom.coefficients[1]);
    }
}

void completeDataMatrix(float** data, float** matrix, int nbData, char type){
    for (int i = 0; i < nbData; i++) {
        if(type=='e'){
            matrix[0][i]=data[0][i];
            matrix[1][i]=logf(data[1][i]);
        }
        if(type=='p'){
            matrix[0][i] = log10f(data[0][i]);
            matrix[1][i] = log10f(data[1][i]);
        }
    }
}   

_polynom computeExponentialPolynom(float** data, int n) {
    //Creation d'une matrice pour les données nécessaires à l'ajustement exponentiel
    float** dataForExp = createMatrix(2, n);
    completeDataMatrix(data, dataForExp, n, 'e');
    //Creation du polynome ln(y)=Bx+A
    _polynom polynom = computeLinearPolynom(dataForExp, n);
    //Transformation en y=exp(A)exp(Bx)
    polynom.coefficients[0]=expf(polynom.coefficients[0]);
    polynom.coefficients[1]=polynom.coefficients[1];
    freeMatrix(dataForExp, 2);
    return polynom;
}

_polynom computePowerPolynom(float** data, int n) {
    //Creation d'une matrice pour les données nécessaires à l'ajustement puissance
    float** dataForPow = createMatrix(2, n);
    completeDataMatrix(data, dataForPow, n, 'p');
    //Creation du polynome log(y)=Blog(x)+A
    _polynom polynom = computeLinearPolynom(dataForPow, n);
    //Transformation en y=(10^A)x^B
    polynom.coefficients[0]=pow(10, polynom.coefficients[0]);
    polynom.coefficients[1]=polynom.coefficients[1];
    freeMatrix(dataForPow, 2);
    return polynom;
}

void writeDataIntoFile(float** data, _polynom polynom, char type, int n, int nbPoints, int marge, FILE* fichier){
    printMatrixIntoFile(data, 2, n, fichier);
    float xmin=data[0][0];
    float xmax=data[0][0];
    for (int j = 1; j < n; j++) {
    float value = data[0][j];
    if (value < xmin) {
        xmin = value;
    }
    if (value > xmax) {
        xmax = value;
    }
    }
    float pas = (xmax - xmin) / nbPoints;
    for (int k = -marge; k < nbPoints+marge+1; k++) {
        fprintf(fichier, "%f ", xmin+pas*k);
    }
    fprintf(fichier, "\n");
    for (int k = -marge; k < nbPoints+marge+1; k++) {
        fprintf(fichier, "%f ", evaluatePolynom(polynom, xmin+pas*k, type));
    }
}

int main(int argc, char const* argv[]) {
    //Ecriture des données
    FILE* fd = fopen(argv[1], "w+");

    //Nombre de points
    int n;
    char type;
    printf("Nombre de points: ");
    scanf("%d", &n);

    printf("\nType d'approximation: ");
    scanf(" %c", &type);

    // Stockage des points
    float** data = createMatrix(2, n);
    completeMatrix(data, 2, n);
    puts("\nData Matrix");
    printMatrix(data, 2, n);

    
    ///////////////////////         AJUSTEMENT LINEAIRE         //////////////////////////////
    if(type=='l'){
        _polynom linPolynom=computeLinearPolynom(data, n);
        printPolynomials(linPolynom, 'l');
        writeDataIntoFile(data, linPolynom, type, n, 50, 3, fd);
        freePolynom(linPolynom);
    }
    ///////////////////////         AJUSTEMENT EXPONENTIEL         ///////////////////////////
    if(type=='e'){
        _polynom expPolynom=computeExponentialPolynom(data, n);
        printPolynomials(expPolynom, 'e');
        writeDataIntoFile(data, expPolynom, type, n, 50, 3, fd);
        freePolynom(expPolynom);
    }
    ///////////////////////         AJUSTEMENT PUISSANCE         /////////////////////////////
    if(type=='p'){
        _polynom powPolynom=computePowerPolynom(data, n);
        printPolynomials(powPolynom, 'p');
        writeDataIntoFile(data, powPolynom, type, n, 50, 0, fd);
        freePolynom(powPolynom);
    }

    freeMatrix(data, 2);
    fclose(fd);
    return 0;
}

