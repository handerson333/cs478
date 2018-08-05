#include "./HORS.h"
#include <sys/time.h>
int main() {
  int l = 128;
  int t = 1024;
  int k = 32;
  int b = 8;
  int m = 30;
  int t_array[t];
  int subset[k];
  struct timeval t1, t2, t3, t4;
  double elapsedTime;
  srand(time(NULL));

  gettimeofday(&t3, NULL);

  init_t_array(t_array, t);
  int choose = t_choose_k(t,k);


  gettimeofday(&t1, NULL);
  S(m, k, t, subset);
  gettimeofday(&t2, NULL); 
  elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
  elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
  elapsedTime = elapsedTime/1000;
  printf("TIME ELAPSED SECRET: %f\n", elapsedTime);

  gettimeofday(&t1, NULL);
  key_gen(t, k, l);
  gettimeofday(&t2, NULL); 
  elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
  elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
  elapsedTime = elapsedTime/1000;
  printf("TIME ELAPSED KEYGEN: %f\n", elapsedTime);
  
  
  sign("hfeiowaieyabu", t, k);
  if(verify("hfeiowaburiaoieyabu", t, k) == 1){
    printf("Accepted\n");
  } else{
    printf("Rejected\n");
  }


  gettimeofday(&t1, NULL);
  sign("fneuiabrhbauosefhau", t, k);
  if(verify("fneuiabrhbauosefhau", t, k) == 1){
    printf("Accepted\n");
  } else {
    printf("Rejected\n");
  }
  gettimeofday(&t2, NULL); 
  elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
  elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
  elapsedTime = elapsedTime/1000;
  printf("TIME ELAPSED SIGN: %f\n", elapsedTime);
  
  sign("fneuiabrhbauosefhau", t, k);
  if(verify("hello", t, k) == 1){
    printf("Accepted\n");
  } else {
    printf("Rejected\n");
  }
  gettimeofday(&t4, NULL);  
  elapsedTime = (t4.tv_sec - t3.tv_sec) * 1000.0;
  elapsedTime += (t4.tv_usec - t3.tv_usec) / 1000.0;
  elapsedTime = elapsedTime/1000;
  printf("TIME ELAPSED HORS: %f\n", elapsedTime);
  
  return 0;
}
