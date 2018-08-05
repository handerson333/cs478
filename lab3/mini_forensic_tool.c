#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <openssl/sha.h>
#include "huffman.h"
// #include "determinant.h"
// #include "vandermonde.h"
// #include "rabin.h"

char global_hash[SHA256_DIGEST_LENGTH*2] = {0};
char global_concat_hash[(SHA256_DIGEST_LENGTH*4)+1] = {'\0'};

void concat_hash(char* string1, char* string2);
void hash_string(char* s);
#define M 4
#define N 8
#define L 32
char** item;
char** item_prime;
char** V;
char** VP;
char* C;
char** S;
char** SP;
char* K;

int h[33] = {0};

char concat[139] = {'\0'};
char s[1024][SHA256_DIGEST_LENGTH*2+1] = {'\0'};
char v[1024][SHA256_DIGEST_LENGTH*2+1] = {'\0'};

char sign_s[1024][SHA256_DIGEST_LENGTH*2+1] = {'\0'};
char sign_v[1024][SHA256_DIGEST_LENGTH*2+1] = {'\0'};
char ver_v[1024][SHA256_DIGEST_LENGTH*2+1] = {'\0'};
typedef struct {
  char* z;
  int st;
} sk;

typedef struct {
  char R[SHA256_DIGEST_LENGTH*2+1];
  int d;
} pk;




void receiver(double A[N][M], int F[L], double A_subset[M][M], double F_subset[M][N], double A_subset_inverse[M][M]);

int main(){
    srand(time(NULL));
    int F[L];
    double mat[M][L/M];   //this is a m x n matrix
    double A[N][M];
    double Mult[N][N];
    double result[M][N];
    double A_subset[M][M];
    double F_subset[M][N];
    double A_subset_inverse[M][M];
    char* I[1024];
    fill_I(I);
    int l = 128;
    int m = 30;
    int t = 1024;
    int k = 32;

    char items[1024][100];
    for(int i=0; i<1024; i++){
      strcpy(items[i], "data to be compressed");
    }
	  char *data = "data to be compressed by our huffman algorithm";
    char buf[1024];
    char MP[1024][100];

    printf("SENDER START\n\n");


    // Huffman Compress message
    // M ← Compress(Mi)
    init(data);
    for(int i=0; i<1024; i++){
      compress(items[i], buf);
      strcpy(MP[i], buf);
    }

    printf("Compressed: %s\n", buf);
    strcpy(MP,buf);

    //Encrypt MP
    //HMAC C

    concat_hash(MP, I);


    // disperse(F, A, mat, Mult);
    printf("SENDER END\n\n");
    printf("RECEIVER START\n\n");



    // recover(A, F, A_subset_inverse, A_subset, F_subset);
    printf("Decompressed:\n");
    // decompress(buf, byte[1]);




    printf("RECEIVER END\n\n");
    return 0;
}



void fill_I(char I[1024]){
    // for (int i = 0; i < 10; i++){
    //     sprintf(I[i], "%d", i);
    // }
}



void concat_hash(char* string1, char* string2) {
    memset (&global_concat_hash[0], '\0', sizeof(global_concat_hash));
    strcpy(global_concat_hash, string1);
    strcat(global_concat_hash, string2);
    hash_string(global_concat_hash);
    //strcpy(string1, global_hash);
    //printf("parent node hash: %s\n global hash:");
}





void recursive_hash(int i, int j){
    if(S[i] == S[j]){
        return;
    }

}


void hash_string(char* s) {
    memset(&global_hash[0], '\0', sizeof(global_hash));
    unsigned char temp[SHA256_DIGEST_LENGTH] = {'\0'};
    SHA256((unsigned char*)s, strlen(s), temp);
    for(int i=0; i<SHA256_DIGEST_LENGTH; i++){
        sprintf((char*)&(global_hash[i*2]), "%02x", temp[i]);
    }

}
