#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"


float* copyPolynom(float* pol1, int size){
    float* pol2=malloc(size*sizeof(float));
    for (int i=0; i<size; i++){
        pol2[i]=pol1[i];
    }
    return pol2;
}

float* multPolynom(float* pol1, float* pol2, int degMax, int size){
    float temp=0;
    for (int k=size-(degMax+1); k<size; k++){
        pol2[k-1]=pol1[0]*pol2[k]+(temp*pol1[1]);
        temp=pol2[k];
    }
    pol2[size-1]=pol1[1]*pol2[size-1];
    return pol2;
}

float* addPolynom(float* pol1, float* pol2, int size){
    for (int k=0; k<size; k++){
        pol2[k]=pol2[k]+pol1[k];
    }
    return pol2;
}

float* divisePolynom(float* pol1, float denom, int size){
    for (int k=0; k<size; k++){
        pol1[k]=pol1[k]/denom;
    }
    return pol1;
}

void polynomK(float** data, float** coeffMatrix, int k, int size){
    for (int k=0; k<size; k++){
        if (k==0){
            for (int i=0; i<size; i++){
                coeffMatrix[i][size-1]=data[1][i];
            }
        }
        else{
            for (int i=0; i<size-k; i++){
                float polynom[2]={1,-data[0][i+k]};
                float polynom2[2]={-1, data[0][i]};
                float* polynomK=malloc(size*sizeof(float));
                float* polynomK1=copyPolynom(coeffMatrix[i], size);
                float* polynomK2=copyPolynom(coeffMatrix[i+1], size);
                coeffMatrix[i]=divisePolynom(addPolynom(multPolynom(polynom, polynomK1, k, size), multPolynom(polynom2, polynomK2, k, size), size), data[0][i]-data[0][i+k], size);
            }
        }
    }
}

int main(int argc, char const *argv[])
{   
    //Nombre de points
    int n;
    scanf("%d", &n);

    //Stockage des points
    puts("\nMatrix Data");
    float** points=createMatrix(2,n);
    completeMatrix(points, 2, n );
    printMatrix(points, 2, n);
    
    //Matrice des coefficients
    puts("\nMatrix Coefficients");
    float** coeffMatrix=createMatrix(n,n);
    printMatrix(coeffMatrix, n, n);

    polynomK(points, coeffMatrix, 0, n);
    puts("\nMatrix Coefficients");
    printMatrix(coeffMatrix, n, n);
    return 0;
}