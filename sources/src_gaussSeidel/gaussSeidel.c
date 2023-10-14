#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "matrix.h"
#include <math.h>

int isDominantDiagonalMatrix(float** matrix, int row){
    for(int i=0; i<row ; i++){
        float sum=0;
        for (int j=0; j<row ; j++){
            if(j!=i){
                sum+=abs(matrix[i][j]);
            }
        }
        if (sum>=abs(matrix[i][i])){
            return 0;
        }
    }
    return 1; 
}

float majEpsilon(float** matXk, int row){
    float maxforEps=0;
    for(int i=0; i<row; i++){
        float soustr=fabs(1-matXk[i][0]);
        printf("%f\n", matXk[i][0]);
        if (soustr>maxforEps){
            maxforEps=soustr;
        }
    }
    return maxforEps;
}

float** gaussSeidel(float **matA, float **matB, int row, int column, int nbIterMax){
    float **matXk=createMatrix(row, 1);
    for(int rowX=0; rowX<row; rowX++){
			matXk[rowX][0]=0;
    }
    float **matXk1=createMatrix(row, 1);

    float epsilon=majEpsilon(matXk, row);;
    int iter=0;
    
    while ((epsilon>=pow(10,-6)) && (iter<nbIterMax)){
        for(int i=0; i<row ; i++){
            float sumF=0;
            float sumE=0;
            //Calcul de F
            for(int j=i+1; j<row ; j++){
                sumF+=matA[i][j]*matXk[j][0];
            }
            //Calcul de E
            for(int j=0; j<i ; j++){
                sumE+=matA[i][j]*matXk1[j][0];
            }
            matXk1[i][0]=(matB[i][0]-sumF-sumE)/matA[i][i];
        }
        //Maj matrice Xk
        matXk[0][0]=matXk1[0][0];
        matXk[1][0]=matXk1[1][0];
        matXk[2][0]=matXk1[2][0];

        //Maj Epsilon
        epsilon=majEpsilon(matXk, row);
        printf("A l'iteration %d, Epsilon: %f\n", iter, epsilon);
        iter+=1;
    }
    return matXk1;
}

int main(int argc, char const *argv[])
{
    (void) argc;
    (void) argv;
    clock_t start, end;
    double cpu_time_used;
    start = clock();

	//A Matrix
	int rowA;
	int columnA;
	printf("\nRow count of matrix A : ");
	scanf("%d", &rowA);
	printf("\nColumn count of matrix A : ");
	scanf("%d", &columnA);

	float** Amatrix=createMatrix(rowA, columnA);
	completeMatrix(Amatrix, rowA, columnA);
	puts("\n		A matrix \n");
	printMatrix(Amatrix, rowA, columnA);
	
	//B Matrix
	float** Bmatrix=createMatrix(rowA, 1);
	generateB(Amatrix, Bmatrix, rowA, columnA);
	puts("\n		B matrix \n");
	printMatrix(Bmatrix, rowA, 1);
	
	//Solve the system
	puts("\n		SOLVING \n");
    float** Xvector=createMatrix(rowA, 1);
    if(isDominantDiagonalMatrix(Amatrix, rowA)){
        puts("ATTENTION: La matrice A n'est pas une matrice à diagonale strictement dominante donc Gauss-Seidel converge !!!!");
    }
    Xvector=gaussSeidel(Amatrix, Bmatrix, rowA, columnA, 10000000);
	puts("\n		SOLUTION VECTOR X \n");
	printMatrix(Xvector, rowA, 1);
	
	//Free
	/*freeMatrix(Amatrix, rowA);
	freeMatrix(Bmatrix, rowA);
	freeMatrix(Xmatrix, rowA);*/

	end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("\nTemps d'exécution : %f secondes\n", cpu_time_used);
    return 0;
}
