#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "inverse.h"
#include "matrixMult.h"

#define M 4
#define N 8
#define L 32

void divide_string(double* s, int size);
void init_F(double F[L]);
void init_mat(double mat[M][L/M], double F[L]);
void print_mat(double mat[M][L/M]);
void init_A(double A[N][M]);
void print_A(double A[N][M]);
void get_subset_A(double A[N][M], double A_subset[M][M]);
void get_subset_F(double Mult[N][N], double F_subset[M][N]);
int check_for_duplicates(int temp[4], int x);
void recover(double A[N][M], double F[N][N], double A_subset_inverse[M][M], double A_subset[M][M], double F_subset[M][N], double result[M][N]);

int main() {
  srand(time(NULL));
  int F[L];
  double mat[M][L/M];   //this is a m x n matrix
  double A[N][M];
  double Mult[N][N];
  double result[M][N];
  double A_subset[M][M];
  double F_subset[M][N];
  double A_subset_inverse[M][M];

  disperse(F, A, mat, Mult); //will be only diperse call
  recover(A, Mult, A_subset_inverse, A_subset, F_subset, result);
}

void disperse(double F[L], double A[N][M], double mat[M][N], double Mult[N][N]){
  init_F(F);
  init_mat(mat, F);
  print_mat(mat);
  init_A(A);
  multiply_matrices(A, mat, Mult);
}

int get_random_number(){
  return rand() % 8;
}

int check_for_duplicates(int temp[4], int x){
  for(int i=0; i<4; i++){
    if(x == temp[i]){
      return 0;
    }
  }
  return 1;
}

void get_subset_A(double A[N][M], double A_subset[M][M]){
  int temp[M];
  int x;
  for(int i=0; i<M; i++){
    temp[i] = i;
  }
  for(int i=0; i<M; i++){
    for(int j=0; j<M; j++){
      A_subset[i][j] = A[temp[i]][j];
    }
  }
}

void get_subset_F(double Mult[N][N], double F_subset[M][N]){
  print_Mult(Mult);
  printf("F SUBSET:\n");
  int temp[4];
  int x;
  for(int i=0; i<4; i++){
    temp[i] = i;
  }
  for(int i=0; i<M; i++){
    for(int j=0; j<N; j++){
      F_subset[i][j] = Mult[temp[i]][j];
      printf("%.0f\t", F_subset[i][j]);
    }
    printf("\n");
  }
}

void recover(double A[N][M], double Mult[N][N], double A_subset_inverse[M][M], double A_subset[M][M], double F_subset[M][N],double result[M][N]){
  print_A(A);
  get_subset_A(A, A_subset);
  get_subset_F(Mult, F_subset);
  print_A_subset(A_subset);
  //calculate inverse of A subset
  // inverseFunc(A_subset, A_subset_inverse);
  invert(A_subset, A_subset_inverse);
  print_A_subset_inverse(A_subset_inverse);
  // multiply_matrices(A_subset_inverse, F_subset, result[M][N]);
  multiply_matrices2(A_subset_inverse, F_subset, result);
  //result contains M
  print_result(result);
}

void print_A_subset_inverse(double A_subset_inverse[M][M]){
  printf("PRINTING A SUBSET INVERSE\n");
  for(int i=0; i<M; i++){
    for(int j=0; j<M; j++){
      printf("%.10f\t", A_subset_inverse[i][j]);
    }
    printf("\n");
  }
}

void print_Mult(double Mult[N][N]){
  printf("PRINTING MULT\n");
  for(int i=0; i<N; i++){
    for(int j=0; j<N; j++){
      printf("%.0f\t", Mult[i][j]);
    }
    printf("\n");
  }
}

void multiply_matrices(double A[N][M], double mat[M][N], double Mult[N][N]){
  float sum = 0;
  for(int i=0; i<N; i++){
    for(int j=0; j<N; j++){
      Mult[i][j] = 0;
      for(int k=0; k<M; k++){
        sum = sum + A[i][k]*mat[k][j];
      }
      Mult[i][j] = sum;
      sum = 0;
    }
  }
}

void multiply_matrices2(double A_subset_inverse[M][M], double F_subset[M][N], double result[M][N]){
  float sum = 0;
  for(int i=0; i<M; i++){
    for(int j=0; j<N; j++){
      result[i][j] = 0;
      for(int k=0; k<M; k++){
        sum = sum + A_subset_inverse[i][k]*F_subset[k][j];
      }
      result[i][j] = sum;
      sum = 0;
    }
  }
}

void init_A(double A[N][M]){
  for(int i=0; i<N; i++){
    for(int j=0; j<M; j++){
      if(j==0){
        A[i][j] = 1;
      } else {
        A[i][j] = pow(i+1, j+1);
      }
    }
  }
}

void print_A_subset(double A_subset[M][M]){
  printf("Printing A subset\n");
  for(int i=0; i<M; i++){
    for(int j=0; j<M; j++){
      printf("%.0f\t", A_subset[i][j]);
    }
    printf("\n");
  }
}

void print_result(double result[M][N]){
  printf("Printing result\n");
  for(int i=0; i<M; i++){
    for(int j=0; j<N; j++){
      printf("%.0f\t", result[i][j]);
    }
    printf("\n");
  }
}

void print_A(double A[N][M]){
  for(int i=0; i<N; i++){
    for(int j=0; j<M; j++){
      printf("%.0f\t", A[i][j]);
    }
    printf("\n");
  }
}

void init_F(double F[L]){
  for(int i=0; i<L; i++){
    F[i] = i;
  }
}

void init_mat(double mat[M][L/M], double F[L]){
  for(int i=0; i<M; i++){
    for(int j=0; j<L/M; j++){
      mat[i][j] = F[i*N + j];
    }
  }
}

void print_F(double F[L]){
  for(int i=0; i<L; i++){
    printf("%.0f ", F[i]);
  }
  printf("\n");
}

void print_mat(double mat[M][L/M]){
  printf("Printing Mat\n");
  for(int i=0; i<M; i++){
    for(int j=0; j<L/M; j++){
      printf("%.0f  ", mat[i][j]);
    }
    printf("\n");
  }
}
