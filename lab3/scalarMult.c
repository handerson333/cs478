#include<stdio.h>
#include"./scalarMult.h"

/*void scalarMult(int matrix[M][N], int value){
	for(int i=0; i<M; i++){
		for(int j=0; j<N; j++){
			matrix[i][j] = value * matrix[i][j];
		}
	}
}*/

int main(){
	int m, n;
	printf("input M: ");
	scanf("%d", &m);
	printf("\nInput N: ");
	scanf("%d", &n);
	setMatrixDimensions(m, n);
	int val;
	printf("\nInput Multiplication Value: ");
	scanf("%d", &val);
	int matrix[M][N];
	int numCounter = 0; // used just to get different numbers from 1 - M*N
	for(int i=0; i<M; i++){
		for(int j=0; j<N; j++){
			matrix[i][j] = numCounter;
			numCounter += 1;
		}
	}
	printf("original matrix: \n");
	for(int i=0; i<M; i++){
		for(int j=0; j<N; j++){
			 printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
	scalarMult(matrix, val);
	printf("Changed matrix by scalar mult by %d: \n", val);
	for(int i=0; i<M; i++){
		for(int j=0; j<N; j++){
			 printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
	return 0;
}
