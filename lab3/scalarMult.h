#include<stdio.h>
int M, N;

void setMatrixDimensions(int m, int n){
	M = m;
	N =n;
}

void scalarMult(int matrix[M][N], int value){
	for(int i=0; i<M; i++){
		for(int j=0; j<N; j++){
			matrix[i][j] = value * matrix[i][j];
		}
	}
}
