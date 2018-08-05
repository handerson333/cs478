



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <openssl/sha.h>
#include "merkle_hash.h"

int main(){
    char auth[8][41];
    memset(auth,'\0', sizeof(auth) );

    strcpy(auth[0], "data 0");
    strcpy(auth[1], "data 1");
    strcpy(auth[2], "data 2");
    strcpy(auth[3], "data 3");
    strcpy(auth[4], "hashhashhashhashhashhashhashhashhashhash");
    strcpy(auth[5], "data 5");
    strcpy(auth[6], "data 6");
    strcpy(auth[7], "data 7");
    // printf("size of auth4 = %d\n", sizeof(auth[4]));
    // printf("contents of auth4 = %s\n", auth[4]);
    form(auth);
    get_path( auth, auth[4] );
    // verify_nodes(auth);
    if (verify_nodes(auth)){
        printf("\nALL SIBLINGS VERIFIED\n");
    }else{
        printf("\n SIBLINGS NOT CORRECT\n");
    }
    //everything(12 , auth);
}