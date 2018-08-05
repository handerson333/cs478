#include <stdio.h>

int M1, N1;
int M2, N2;

void setMatricesDimensions(int m1, int m2, int n1, int n2){
	M1 = m1;
	M2 = m2;
	N1 = n1;
	N2 = n2;
}

void matrixMult(int matrix1[M1][N1], int matrix2[M2][N2], int multiply[M1][N2]){
	int sum = 0;
	int c, d, k;
	for (c = 0; c < M1; c++) {
      		for (d = 0; d < N2; d++) {
        		for (k = 0; k < M2; k++) {
          			sum = sum + matrix1[c][k]*matrix2[k][d];
        		}
 
       		 multiply[c][d] = sum;
        	 sum = 0;
     		 }
    	}
}
