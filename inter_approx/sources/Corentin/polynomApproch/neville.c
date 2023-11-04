#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "header/polynom.h"
#include "header/matrix.h"

#define MAX(i, j) (((i) > (j)) ? (i) : (j))

_polynom computePolynomials(float** data, int k, int i, int nbPoints, FILE* fd){
    if (k==0){
        _polynom polynom=createPolynom(0);
        polynom.coefficients[0]=data[1][i];
        return polynom;
    }
    else{
        _polynom polynom=createPolynom(k);
        _polynom polynomTemp=createPolynom(k);
        
        _polynom poly1=createPolynom(1);
        poly1.coefficients[1]=1;
        poly1.coefficients[0]=-data[0][i+k];

        _polynom poly2=createPolynom(1);
        poly2.coefficients[1]=-1;
        poly2.coefficients[0]=data[0][i];

        _polynom polyMult1=computePolynomials(data, k-1, i, nbPoints, fd);
        _polynom polyMult2=computePolynomials(data, k-1, i+1, nbPoints, fd);
        float denom=data[0][i]-data[0][i+k];
        multPolynom(poly1, polyMult1, polynomTemp);
        multPolynom(poly2, polyMult2, polynom);
        addPolynom(polynomTemp, polynom, polynom);
        divisePolynom(polynom, denom, polynom);

        freePolynom(poly1);
        freePolynom(poly2);
        freePolynom(polynomTemp);
        freePolynom(polyMult1);
        freePolynom(polyMult2);
        return polynom;
    }
}

float interpolaPoint(float** data, int k, int i, float abscisse){
    if (k==0){ return data[1][i];}
    else{ return ((abscisse-data[0][i+k])*interpolaPoint(data, k-1, i, abscisse)+(data[0][i]-abscisse)*interpolaPoint(data, k-1, i+1, abscisse))/(data[0][i]-data[0][i+k]);}
}

void writeDataIntoFile(float** data, _polynom polynom, int n, int nbPoints, int marge, FILE* fichier){
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
        fprintf(fichier, "%f ", interpolaPoint(data, n-1, 0, xmin+pas*k));
    }
}

void printPolynomial(_polynom polynom) {
    if (polynom.degree < 0) {
        printf("0");
        return;
    }

    for (int i = polynom.degree; i >= 0; i--) {
        float coefficient = polynom.coefficients[i];
        if (coefficient != 0.00) {
            if (i < polynom.degree) {
                if (coefficient > 0.0) {
                    printf(" + ");
                } else {
                    printf(" - ");
                }
            }

            if (i == 0) {
                printf("%.6f", fabs(coefficient));
            } else {
                printf("%.6fx^%d", fabs(coefficient), i);
            }
        }
    }

    printf("\n");
}


int main(int argc, char const *argv[])
{
    clock_t start, end;
    double cpu_time_used;
    FILE* fd=fopen(argv[1], "w");
    
    //Nombre de points
    int n;
    scanf("%d", &n);

    //Stockage des points
    float** data = createMatrix(2, n);
    completeMatrix(data, 2, n);
    puts("\nData Matrix");
    printMatrix(data, 2, n);
        
    start = clock();
    _polynom polynom=computePolynomials(data, n-1, 0, n, fd);
    end = clock();
    puts("\nPolynom");
    printPolynomial(polynom);
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("\nTemps d'exécution : %f secondes\n", cpu_time_used);
    writeDataIntoFile(data, polynom, n, 50, 1, fd);
    
    freeMatrix(data, 2);
    freePolynom(polynom);
    fclose(fd);  
    return 0;
}
