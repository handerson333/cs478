#ifndef __LIB_DETERMINANT_
#define __LIB_DETERMINANT_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#define SIZE 4
//int SIZE = 4;




void find_cofactor(double matrix[SIZE][SIZE], double submatrix[SIZE][SIZE], int subrow, int subcol, int subsize){
    int i = 0;
    int j = 0;
 

    for (int row = 0; row < subsize; row++){
        for (int col = 0; col < subsize; col++){

            if (row != subrow && col != subcol){
                submatrix[i][j++] = matrix[row][col];

                if (j == subsize - 1){
                    j = 0;
                    i++;
                }
            }
        }
    }
}
 

double get_determinant(double matrix[SIZE][SIZE], int subsize){
    double total = 0; 
 

    if (subsize == 1)
        return matrix[0][0];
 
    double submatrix[SIZE][SIZE]; 
 
    int cofactor = 1; 
 

    for (int i = 0; i < subsize; i++){

        find_cofactor(matrix, submatrix, 0, i, subsize);
        total += cofactor * matrix[0][i] * get_determinant(submatrix, subsize - 1);
 

        cofactor *= -1;
    }
 
    return total;
}
 


void print_table(double matrix[SIZE][SIZE]){
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++)
            printf("%.1f\t", matrix[i][j]);
        printf("\n");
    }
}


#endif
