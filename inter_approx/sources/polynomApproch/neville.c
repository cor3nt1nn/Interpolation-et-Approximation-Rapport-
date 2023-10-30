#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "header/polynom.h"
#include "header/matrix.h"

#define MAX(i, j) (((i) > (j)) ? (i) : (j))

void computePolynomials(float** data, _polynom* coeffPolynomArray, int nbPoints){
    for (int k=0; k<nbPoints; k++){
        if (k==0){
            for (int i=0; i<nbPoints; i++){
                coeffPolynomArray[i].coefficients[0]=data[1][i];
            }
        }
        else{
            _polynom poly1=createPolynom(1);
            _polynom poly2=createPolynom(1);
            _polynom polynomTemp=createPolynom(k);
            
            poly1.coefficients[1]=1;
            poly2.coefficients[1]=-1;

            for (int i=0; i<nbPoints-k; i++){
                
                poly1.coefficients[0]=-data[0][i+k];
                poly2.coefficients[0]=data[0][i];

                multPolynom(poly1, coeffPolynomArray[i], polynomTemp);
                multPolynom(poly2, coeffPolynomArray[i+1], coeffPolynomArray[i]);
                addPolynom(polynomTemp, coeffPolynomArray[i]);
                divisePolynom(coeffPolynomArray[i], data[0][i]-data[0][i+k], coeffPolynomArray[i]);
                
            }
            freePolynom(poly1);
            freePolynom(poly2);
            freePolynom(polynomTemp);
        }
    }
}

int main(int argc, char const *argv[])
{

    FILE* fd=fopen("results/41.txt", "w");
    if (fd == NULL) {
    perror("Erreur lors de l'ouverture du fichier de sortie");
    return 1;
    }
    
    clock_t start, end;
    double cpu_time_used;
    //Nombre de points
    int n;
    scanf("%d", &n);
    fprintf(fd, "%d\n", n);

    //Stockage des points
    float** data=createMatrix(2, n);
    completeMatrix(data, 2,n);
    puts("\nData Matrix ");
    printMatrixIntoFile(data, 2,n, fd);
    
      
    //Matrice des coefficients
    _polynom* coeff=createPolynomArray(n);
    
    start = clock();
    computePolynomials(data, coeff, n);
    end = clock();

    puts("\nPolynomial ");
    printPolynomIntoFile(coeff[0], fd);
    printPolynomial(coeff[0].coefficients, n-1);

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("\nTemps d'exécution : %f secondes\n", cpu_time_used);

    freeMatrix(data, 2);
    freePolynomArray(coeff, n);
    fclose(fd);  
    return 0;
}
