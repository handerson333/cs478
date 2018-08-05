#include "./HORS.h"
#include "./merkle_hash.h"
#include <sys/time.h>
typedef struct {
  char* z;
  int st;
} sk;

typedef struct {
  char R[SHA_DIGEST_LENGTH*2+1];
  int d;
} pk;

char* itob(int i);
void pq_key_gen(int l, int k, int t, sk *secret, pk *public);
void pq_sign (int k, int t, char* m, sk secret, int d);
void pq_ver(int k, int t, char* m, pk public, int st);
int h[33] = {0};

char concat[139] = {'\0'};
char s[1024][SHA_DIGEST_LENGTH*2+1] = {'\0'};
char v[1024][SHA_DIGEST_LENGTH*2+1] = {'\0'};

char sign_s[1024][SHA_DIGEST_LENGTH*2+1] = {'\0'};
char sign_v[1024][SHA_DIGEST_LENGTH*2+1] = {'\0'};
char ver_v[1024][SHA_DIGEST_LENGTH*2+1] = {'\0'};

int main() {
  int t = 1024;
  int k = 32;
  int l = 128;
  struct timeval t1, t2, t3, t4;
  double elapsedTime;
  sk secret;
  pk public;
  gettimeofday(&t3, NULL);
  gettimeofday(&t1, NULL);
  pq_key_gen(l, k, t, &secret, &public);
  gettimeofday(&t2, NULL);
  elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
  elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
  elapsedTime = elapsedTime/1000;
  printf("TIME ELAPSED KEYGEN: %f\n", elapsedTime);
  gettimeofday(&t1, NULL);
  pq_sign(k, t, "hello", secret, public.d);
  gettimeofday(&t2, NULL);  
  elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
  elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
  elapsedTime = elapsedTime/1000;
  printf("TIME ELAPSED SIGN: %f\n", elapsedTime);
  gettimeofday(&t1, NULL);
  pq_ver(k, t, "hello", public, secret.st);
  gettimeofday(&t2, NULL);
  elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
  elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
  elapsedTime = elapsedTime/1000;
  printf("TIME ELAPSED VERIFY: %f\n", elapsedTime);
  gettimeofday(&t4, NULL);
  elapsedTime = (t4.tv_sec - t3.tv_sec) * 1000.0;
  elapsedTime += (t4.tv_usec - t3.tv_usec) / 1000.0;
  elapsedTime = elapsedTime/1000;
  printf("TIME ELAPSED PQSIG: %f\n", elapsedTime);
  return 0;
}

void pq_key_gen(int l, int k, int t, sk *secret, pk *public) {
  public->d = 1;
  secret->st = 1;
  secret->z = random_string(128);
  for(int i=0; i<public->d*t; i++){
    memset(concat, '\0', sizeof(concat));
    strcpy(concat, secret->z);
    strcat(concat, itob(i));
    hash_string(concat);
    strcpy(s[i], hash);
    hash_string(s[i]);
    strcpy(v[i], hash);
  }
  strcpy(public->R, form(v));
}

void pq_sign (int k, int t, char* m, sk secret, int d) {
  char* binary;
  int size = log2(t);
  if(secret.st > d){
    exit(0);
  } else {
    hash_string(m);
    binary = string_to_binary(hash);
    divide_string(binary, size);
    for(int i=0; i<k; i++){
      h[i] = btoi(split[i]);
    }
    for(int j=0; j<k; j++){
      int temp = (secret.st-1)+h[j];
      memset(concat, '\0', sizeof(concat));
      strcpy(concat, secret.z);
      strcat(concat, itob(temp));
      hash_string(concat);
      strcpy(sign_s[temp], hash);
      hash_string(sign_s[temp]);
      strcpy(sign_v[temp], hash);
      //get_path(v, sign_v[temp]);// get path for leaf
      // assign things to signature
      secret.st++;
    }
  }
  secret.st = 1;
}

void pq_ver(int k, int t, char* m, pk public, int st) {
  char* binary;
  int size = log2(t);
  if(st > public.d){
    exit(0);
  } else {
    hash_string(m);
    binary = string_to_binary(hash);
    divide_string(binary, size);
    for(int i=0; i<k; i++){
      h[i] = btoi(split[i]);
    }
    for(int j=0; j<k; j++){
      int temp = (st-1)+h[j];
      hash_string(sign_s[temp]);
      strcpy(ver_v[temp], hash);
      verify_nodes(ver_v);//call verify
      int b = 1; 
      if(b == 0){
        printf("Failed\n");
        exit(1);
      }
    }
  }
  printf("Success\n");
}

char* itob(int i) {
   static char bits[10] = {'0'};
   for(int i=0; i<10; i++){
     bits[i] = '0';
   }
   int bits_index = 9;
   while ( i > 0 ) {
      bits[bits_index--] = (i & 1) + '0';
      i = ( i >> 1);
   }
   return bits;
}
