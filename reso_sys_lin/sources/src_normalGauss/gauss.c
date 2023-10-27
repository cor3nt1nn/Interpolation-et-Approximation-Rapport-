#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/*
CREATE A 2D FLOAT MATRIX
*/

float** createMatrix(int row, int column){
	float **mat=NULL;
	mat=malloc(row* sizeof(int*));
	if(mat==NULL){return NULL;}
	for (int i=0; i<row; i++){
		mat[i]=malloc(column* sizeof(int));
		if(mat[i]==NULL){
			for(int j=0; j<i; j++){
				free(mat[j]);
				return NULL;
			}
		}
	}
	return mat;
}

/*
PRINT A 2D FLOAT MATRIX
*/

void printMatrix(float **mat, int row, int column){
	for (int i=0; i<row; i++){
    		for(int j=0; j<column; j++){
         		printf("%.3f   ", mat[i][j]);
    		}
    		printf("\n");
	}
}

/*
FREE A 2D FLOAT MATRIX
*/

void freeMatrix(float **mat, int row){
	for(int i=0; i<row;i++){
		free(mat[i]);
	}
	free(mat);
}

/*
COMPLETE A 2D FLOAT MATRIX FROM USER INPUT
*/

void completeMatrix(float **mat, int row, int column){
	puts("\n		FILL IN THE VALUE OF MATRIX A \n");
	for (int i=0; i<row; i++){
    		for(int j=0; j<column; j++){
    			printf("Value for a_%d,%d:   ", i+1, j+1);
         		scanf("%f", &mat[i][j]);
    		}
	}
}

/*
GENERATE A COLUMN VECTOR "B" FROM A 2D FLOAT MATRIX "A"
*/

void generateB(float **matA, float **matB, int row, int column){
	for(int i=0; i<row; i++){
		float sum=0;
		for(int j=0; j<column; j++){
			sum+=matA[i][j];
		}
		matB[i][0]=sum;
    	}
}

/*
PERFORM GAUSSIAN ELIMINATION ON A Ax=B MATRIX SYSTEM OF LINEAR EQUATIONS
*/

void gauss(float** matA, float** matb, int size){
	for(int k=0; k<size-1; k++){
		for(int i=k+1; i<size; i++){
			float alpha=matA[i][k]/matA[k][k];
			for(int j=k; j<size; j++){
				matA[i][j]=matA[i][j]-alpha*matA[k][j];
			}
			matb[i][0]=matb[i][0]-alpha*matb[k][0];
		}
	}
}

/*
SOLVE A MATRIX SYSTEM OF LINEAR EQUATIONS USING BACKWARD SUBSTITUTION
*/
void resolution(float** matA, float** matb, float** matx, int size){
	matx[size-1][0]=matb[size-1][0]/matA[size-1][size-1];
	for (int i=size-2; i>=0; i--){
		float sum=0;
		for(int j=i+1; j<size; j++){
			sum+=matA[i][j]*matx[j][0];
		}
		matx[i][0]=(1/matA[i][i])*(matb[i][0]-sum);
	}
}

int main(){
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
	puts("\n		A matrix ");
	printMatrix(Amatrix, rowA, columnA);
	
	//B Matrix
	float** Bmatrix=createMatrix(rowA, 1);
	generateB(Amatrix, Bmatrix, rowA, columnA);
	puts("\n		B matrix ");
	printMatrix(Bmatrix, rowA, 1);
	
	
	//Matrix Triangularization
	puts("		TRIANGULARIZATION ");
	gauss(Amatrix, Bmatrix, rowA);
	puts("\n		A Matrix ");
	printMatrix(Amatrix, rowA, columnA);
	puts("\n		B Matrix ");
	printMatrix(Bmatrix, rowA, 1);
	
	//Solve the system
	float** Xmatrix=createMatrix(rowA, 1);
	puts("		SOLVING ");
	resolution(Amatrix, Bmatrix, Xmatrix, rowA);
	puts("\n		SOLUTION VECTOR X ");
	printMatrix(Xmatrix, rowA, 1);
	
	//Free
	freeMatrix(Amatrix, rowA);
	freeMatrix(Bmatrix, rowA);
	freeMatrix(Xmatrix, rowA);

	end = clock();
    
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    
    printf("\nTemps d'execution : %f secondes\n", cpu_time_used);
	return 0;
}


