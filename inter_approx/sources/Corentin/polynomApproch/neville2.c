#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

        double denom=data[0][i]-data[0][i+k];
        if(k!=1){
            fprintf(fd, "%s", "((");
            printPolynomialIntoFile(poly1.coefficients, 1, fd);
            fprintf(fd, "%s", ")*(");}
        multPolynom(poly1, computePolynomials(data, k-1, i, nbPoints, fd), polynomTemp);
        if(k!=1){
            fprintf(fd, "%s", ")+(");
            printPolynomialIntoFile(poly2.coefficients, 1, fd);
            fprintf(fd, "%s", ")*(");}
        multPolynom(poly2, computePolynomials(data, k-1, i+1, nbPoints, fd), polynom);
        if(k!=1){
            fprintf(fd, "))/%lf", denom);
        }
        addPolynom(polynomTemp, polynom);
        divisePolynom(polynom, denom, polynom);               
        freePolynom(poly1);
        freePolynom(poly2);
        freePolynom(polynomTemp);
        if(k==1){
            printPolynomialIntoFile(polynom.coefficients, k, fd);
        }
        return polynom;
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
    //_polynom* coeff=createPolynomArray(n);
    
    start = clock();
    printPolynom(computePolynomials(data, n-1, 0, n, fd));
    end = clock();
    // puts("\nPolynomial ");
    // printPolynomIntoFile(coeff[0], fd);
    //printPolynomial(coeff[0].coefficients, n-1);

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("\nTemps d'exécution : %f secondes\n", cpu_time_used);

    freeMatrix(data, 2);
    //freePolynomArray(coeff, n);
    fclose(fd);  
    return 0;
}
