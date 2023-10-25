#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "matrix.h"
#include <math.h>

float majEpsilon(float** matXk, int row){
    float maxforEps=0;
    for(int i=0; i<row; i++){
        float soustr=fabs(1-matXk[i][0]);
        if (soustr>maxforEps){
            maxforEps=soustr;
        }
    }
    return maxforEps;
}

float** gaussSeidel(FILE* fd, float **matA, float **matB, float **matXk, int row, int column, int nbIterMax){
    float **matXk1=createMatrix(row, 1);

    float epsilon=majEpsilon(matXk, row);
    fprintf(fd, "%.6f ", epsilon);
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
        for(int k=0; k<row ; k++){
            matXk[k][0]=matXk1[k][0];
        }
        
        //Maj Epsilon
        epsilon=majEpsilon(matXk, row);
        fprintf(fd, "%.6f ", epsilon);
        iter+=1;
    }
    if(iter==nbIterMax-1){
        puts("Nombre d'itérations maximum atteint");
    }
    fprintf(fd, "\n");
    fprintf(fd, "%d\n", iter+1);
    freeMatrix(matXk1, row);
    return matXk;
}

int main(int argc, char const *argv[])
{
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    FILE* fd=fopen(argv[1], "w");
	//A Matrix
	int rowA;
	int columnA;
	printf("\nRow count of matrix A : ");
	scanf("%d", &rowA);
	printf("\nColumn count of matrix A : ");
	scanf("%d", &columnA);

	float** Amatrix=createMatrix(rowA, columnA);
	completeMatrix(Amatrix, rowA, columnA);
	puts("\n		A matrix");
	printMatrix(Amatrix, rowA, columnA);
	
	//B Matrix
	float** Bmatrix=createMatrix(rowA, 1);
	generateB(Amatrix, Bmatrix, rowA, columnA);
	puts("		B matrix");
	printMatrix(Bmatrix, rowA, 1);
	
	//Solve the system
	puts("		SOLVING");
    float** Xvector=createMatrix(rowA, 1);
    for(int rowX=0; rowX<rowA; rowX++){
			Xvector[rowX][0]=0;
    }
    Xvector=gaussSeidel(fd, Amatrix, Bmatrix, Xvector, rowA, columnA, 1000);
	puts("		SOLUTION VECTOR X ");
	printMatrix(Xvector, rowA, 1);
	
	//Free
	freeMatrix(Amatrix, rowA);
	freeMatrix(Bmatrix, rowA);
	freeMatrix(Xvector, rowA);
    fclose(fd);

	end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Temps d'execution : %f secondes\n", cpu_time_used);
    return 0;
}
