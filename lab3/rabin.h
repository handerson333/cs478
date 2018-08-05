#ifndef __LIB_RABIN_
#define __LIB_RABIN_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

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
void get_subset_F(double F[N][N], double F_subset[M][N]);
int check_for_duplicates(int temp[4], int x);
void recover(double A[N][M], double F[N][N], double A_subset_inverse[M][M], double A_subset[M][M], double F_subset[M][N],double result[M][N]);


void disperse(double F[L], double A[N][M], double mat[M][N], double Mult[N][N]){
  init_F(F);
  init_mat(mat, F);
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
    while(1){
      x = get_random_number();
      if(check_for_duplicates(temp, x) == 1){
        break;
      }
    }
    temp[i] = x;
  }
  for(int i=0; i<M; i++){
    for(int j=0; j<M; j++){
      A_subset[i][j] = A[i][j];
    }
  }
}

void get_subset_F(double F[N][N], double F_subset[M][N]){
  int temp[4];
  int x;
  for(int i=0; i<4; i++){
    while(1){
      x = get_random_number();
      if(check_for_duplicates(temp, x) == 1){
        break;
      }
    }
    temp[i] = x;
  }
  for(int i=0; i<M; i++){
    for(int j=0; j<N; j++){
      F_subset[i][j] = F[i][j];
    }
  }
}

void recover(double A[N][M], double F[N][N], double A_subset_inverse[M][M], double A_subset[M][M], double F_subset[M][N],double result[M][N]){
  get_subset_A(A, A_subset);
  get_subset_F(F, F_subset);
  //calculate inverse of A subset
  inverseFunc(A_subset, A_subset_inverse);
  // multiply_matrices(A_subset_inverse, F_subset, result[M][N]);
  matrixMult(A_subset_inverse, F_subset,recover);
  //result contains M
}

void print_Mult(double Mult[N][N]){
  for(int i=0; i<N; i++){
    for(int j=0; j<N; j++){
      printf("%.01f  ", Mult[i][j]);
    }
    printf("\n");
  }
}

void multiply_matrices(double A[N][M], double mat[M][N], double Mult[N][N]){
  for(int i=0; i<N; i++){
    for(int j=0; j<N; j++){
      Mult[i][j] = 0;
      for(int k=0; k<M; k++){
        for(int l=0; l<M; l++){
          Mult[i][j] = A[i][k]*mat[l][j]+Mult[i][j];
        }
      }
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

void print_A(double A[N][M]){
  for(int i=0; i<N; i++){
    for(int j=0; j<M; j++){
      printf("%.01f  ", A[i][j]);
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
    printf("%.01f ", F[i]);
  }
  printf("\n");
}

void print_mat(double mat[M][L/M]){
  for(int i=0; i<M; i++){
    for(int j=0; j<L/M; j++){
      printf("%.01f  ", mat[i][j]);
    }
    printf("\n");
  }
}
#endif