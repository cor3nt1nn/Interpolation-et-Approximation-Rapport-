/*
CREATE A 2D FLOAT MATRIX
*/

float** createMatrix(int row, int column){
	float **mat=NULL;
	mat=malloc(row* sizeof(float**));
	if(mat==NULL){return NULL;}
	for (int i=0; i<row; i++){
		mat[i]=malloc(column* sizeof(float*));
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
