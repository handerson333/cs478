#include <stdio.h>
#ifndef __LIB_MERK_
#define __LIB_MERK_

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <openssl/sha.h>

//#define LEAVES 1025
#define COUNT 10
#define PARENT ((int)floor(((i-1)/2)))
#define MOST_LEFT_LEAF ((int)(num_nodes-1)/2)




typedef struct node
{
    char hash[(SHA_DIGEST_LENGTH*2)+1]; //8 bytes
    char data[(SHA_DIGEST_LENGTH*2)+1];; // 8 bytes
    struct node* left; //8 bytes
    struct node* right; //8 bytes
}node;


int get_log(int y);
char concat_hash[(SHA_DIGEST_LENGTH*4)+1] = {'\0'};
char global_hash[(SHA_DIGEST_LENGTH*2)+1] = {'\0'};
node* newNode();

int isEmpty(node *root);
void push(node** root, char* input);

void print2DUtil(node *root, int space);
void print2D(node *root);
char* get_root_hash(node *root);
void hash_tree(node* parent_node);
// void hash_string_merkle(char* s);
char* hash_siblings( char left[41], char right[41] );
int everything(int leaf, char** data);
char** get_path(char data[][41], char* leaf_hash);
int verify_nodes(char data[][41]);
int do_all_no_print(char data[][41], int leaf);
char* form(char data[][41]);








int verify_nodes(char data[][41]){

    int leaves = (sizeof(data)/sizeof(*data[0]));
    int num_nodes = (leaves*2)-1;

    //for each given node, check if same as tree leaf
    for (int i = 0; i < leaves; i++){
        //printf("verifying node: %s\n", data[i]);
        //printf("I: %d\n", i);
        //printf("MOST LEFT _LEAF + I: %d\n", MOST_LEFT_LEAF + i);
        if (do_all_no_print(data, MOST_LEFT_LEAF + i) != 1){
            return 0;
        }
    }
    return 1;
}

int do_all_no_print(char data[][41], int node_num){
    /*create root*/

    int leaves = (sizeof(data)/sizeof(*data[0]));

    int num_nodes = (leaves*2)-1;
    int num_levels = (int)log2(leaves);
    int num_levels_1 = (num_levels+1);


    node* root[num_nodes];

    for ( int i=0; i< num_nodes; i++){
        root[i] = newNode();
    }


    for( int i = 0; i <(MOST_LEFT_LEAF); i++ ){
        root[i]->left = root[(i+i+1)];
        root[i]->right = root[(i+i+2)];
    }
    //printf("data at 0 = %s\n", data[0]);
    int j = 0;
    for( int i = (MOST_LEFT_LEAF); i < num_nodes; i++ ){

        strcpy(root[i]->data, data[j]);
        //printf("root[i]-> data: %s\n data: %s\n", root[i]->data, data[j]);
        j++;
    }

    for( int i = (MOST_LEFT_LEAF); i < num_nodes; i++ ){
        //printf("i leaf hash: %d\n", i);
        hash_leaf(root[i]);
    }

    for (int i = (MOST_LEFT_LEAF-1); i >= 0; i--){
        //printf("i tree hash: %d\n", i);
        hash_tree(root[i]);
    }




    // char auth[num_levels_1][41];
    // memset(auth,'\0', sizeof(auth) );


    // // leaf is current leaf number to verify fits into tree
    // // counter is counter for temporary auth array
    // // auth[] stores each consecutive has to see if it all hashes up to root hash

    // int counter = 0;
    // int i = leaf;
    // strcpy(auth[counter], root[leaf]->hash);

    // printf("AUTH[COUNTER] @ I: %d and COUNTER: %d\t%s\n",i,counter, auth[counter]);
    // counter++;

    // while(i != 0){
    //     if(root[PARENT]->left->hash == root[i]->hash){
    //         strcpy(auth[counter], root[PARENT]->right->hash);
    //         printf("sibling data: %s\nAUTH[COUNTER] @ I: %d and COUNTER: %d\n%s\n\n",root[PARENT]->left->data,i,counter, auth[counter]);
    //         counter++;
    //     }
    //     else if(root[PARENT]->right->hash == root[i]->hash){
    //         strcpy(auth[counter], root[PARENT]->left->hash);
    //         printf("sibling data: %s\nAUTH[COUNTER] @ I: %d and COUNTER: %d\n%s\n\n",root[PARENT]->left->data,i,counter, auth[counter]);
    //         counter++;
    //     }

    //     i = PARENT;
    //     printf("i after: %d\n", i);
    // }

    // i = 0;

    // memset(&concat_hash[0], '\0', sizeof(concat_hash));
    // strcpy(concat_hash, auth[i] );
    // // Verify (requires to get the authentication hashes first in order to fill auth)
    // while( i < num_levels){
    //     hash_siblings(auth, i);
    //     i++;
    // }

    // if (strcmp(concat_hash, get_root_hash(root[0])) == 0){
    //     printf("yes\n\n");
    //     return 1;
    // }
    // else{
    //     printf("no\n\n");
    //     return 0;
    // }

    //printf("root hash is: %s\n\n", root[0]->hash);

    memset(&concat_hash[0], '\0', sizeof(concat_hash));
    int i = node_num; // leaf number
    while(1){
        if(i%2 == 1 ){ //me left
            //printf("I am left sibling\n");
            strcpy(concat_hash, hash_siblings(root[i]->hash, root[i+1]->hash));//hash me || sib
        }
        if(i%2 == 0){ // sib left
            //printf("I am right sibling\n");
            strcpy(concat_hash, hash_siblings(root[i-1]->hash, root[i]->hash));//hash sib || me
        }
        //printf("concat hash is: %s\n",concat_hash);
        if( PARENT != 0){ // parent is not root
            i = PARENT;
        }else{
            if(strcmp(get_root_hash(root[0]), concat_hash) == 0){ //if root is same as leaves that make it up
                //printf("yes\n\n");
                return 1;

            }else{
                //printf("no\n\n");
                return 0;

            }
        }

    }






}






char* form(char data[][41]){
    int leaves = (sizeof(data)/sizeof(*data[0]));

    int num_nodes = (leaves*2)-1;
    int num_levels = (int)log2(leaves);
    int num_levels_1 = (num_levels+1);


    node* root[num_nodes];

    for ( int i=0; i< num_nodes; i++){
        root[i] = newNode();
    }


    for( int i = 0; i <(MOST_LEFT_LEAF); i++ ){
        root[i]->left = root[(i+i+1)];
        root[i]->right = root[(i+i+2)];
    }
    // printf("data at 0 = %s\n", data[0]);
    int j = 0;
    for( int i = (MOST_LEFT_LEAF); i < num_nodes; i++ ){

        strcpy(root[i]->data, data[j]);
        // printf("root[i]-> data: %s\n data: %s\n", root[i]->data, data[j]);
        j++;
    }

    for( int i = (MOST_LEFT_LEAF); i < num_nodes; i++ ){
        //printf("i leaf hash: %d\n", i);
        hash_leaf(root[i]);
    }

    for (int i = (MOST_LEFT_LEAF-1); i >= 0; i--){
        //printf("i tree hash: %d\n", i);
        hash_tree(root[i]);
    }


    printf("\nRoot hash: %s\n\n", get_root_hash(root[0]));
    return get_root_hash(root[0]);

}


char** get_path(char data[][41], char* leaf_hash){
    int leaves = 1024;

    int num_nodes = (leaves*2)-1;
    int num_levels = (int)log2(leaves);
    int num_levels_1 = (num_levels+1);


    node* root[num_nodes];

    for ( int i=0; i< num_nodes; i++){
        root[i] = newNode();
    }


    for( int i = 0; i <(MOST_LEFT_LEAF); i++ ){
        root[i]->left = root[(i+i+1)];
        root[i]->right = root[(i+i+2)];
    }
    // printf("data at 0 = %s\n", data[0]);
    int j = 0;
    for( int i = (MOST_LEFT_LEAF); i < num_nodes; i++ ){

        strcpy(root[i]->data, data[j]);
        // printf("root[i]-> data: %s\n data: %s\n", root[i]->data, data[j]);
        j++;
    }

    for( int i = (MOST_LEFT_LEAF); i < num_nodes; i++ ){
        //printf("i leaf hash: %d\n", i);
        hash_leaf(root[i]);
    }

    for (int i = (MOST_LEFT_LEAF-1); i >= 0; i--){
        //printf("i tree hash: %d\n", i);
        hash_tree(root[i]);
    }

        hash_string_merkle(leaf_hash);
        strcpy(leaf_hash, global_hash);

    int leaf = 12;
    for( int i = (MOST_LEFT_LEAF); i < num_nodes; i++ ){

        // printf("ROOT data: %s\n", root[i]->data);
        // printf("ROOT at %d: %s\n", i, root[i]->hash);
        // printf("\nleaf hash is %s\n\n", leaf_hash);
        if (strcmp(root[i], leaf_hash) == 0){
            // printf("\n\n\ntest\n\n\n");
            leaf = i;
        }
    }

    //print tree
    //print2D(root[0]);

    //get authentication hashes
    //printf("\nroot hash is %s\n\n", get_root_hash(root[0]));


    // char auth[num_levels_1][41];
    char** auth = malloc(sizeof(char*)*num_levels_1);
    for(int i=0; i<num_levels_1; i++){
      auth[i] = malloc(sizeof(char)*42);
    }
    // memset(auth,'\0', sizeof(auth) );
    int counter = 0;

    int i = leaf;
    //strcpy(auth[counter], root[leaf]->hash);
    counter++;
    printf("\nleaf is %s\n\nAuthentication hashes are:\n", root[leaf]);

    while(i != 0){
        if(root[PARENT]->left->hash == root[i]->hash){
            strcpy(auth[counter], root[PARENT]->right->hash);

            counter++;
        }
        else if(root[PARENT]->right->hash == root[i]->hash){
            strcpy(auth[counter], root[PARENT]->left->hash);

            counter++;
        }

        i = PARENT;
        //printf("i after: %d\n", i);
    }
    i = 0;




    // print authentication hashes
    for(int i = 0; i<num_levels_1; i++){
        printf("%s\n", auth[i]);
    }
    i = 0;

    return auth;

}








int everything(int leaf, char** data){
    /*create root*/

    int leaves = (sizeof(data)/sizeof(*data[0]));
    printf("leaves = %d\n", leaves);

    int num_nodes = (leaves*2)-1;
    int num_levels = (int)log2(leaves);
    int num_levels_1 = (num_levels+1);


    //printf("num_nodes: %d\n", num_nodes);

    node* root[num_nodes];

    for ( int i=0; i< num_nodes; i++){
        root[i] = newNode();
    }

    for( int i = 0; i <(MOST_LEFT_LEAF); i++ ){
        root[i]->left = root[(i+i+1)];
        root[i]->right = root[(i+i+2)];
    }
    // for( int i = (MOST_LEFT_LEAF); i < num_nodes; i++ ){
    //     strcpy(root[i]->data, "leaf");
    // }
    for( int i = (MOST_LEFT_LEAF); i < num_nodes; i++ ){
        //printf("i leaf hash: %d\n", i);
        hash_leaf(root[i]);


    }
    for (int i = (MOST_LEFT_LEAF-1); i >= 0; i--){
        //printf("i tree hash: %d\n", i);
        hash_tree(root[i]);


    }

    //print tree
    print2D(root[0]);

    //get authentication hashes
    //printf("\nroot hash is %s\n\n", get_root_hash(root[0]));


    char auth[num_levels_1][41];
    memset(auth,'\0', sizeof(auth) );
    int counter = 0;
    int i = leaf;
    strcpy(auth[counter], root[leaf]->hash);
    counter++;
    printf("\nleaf is %s\n\nAuthentication hashes are:\n\n", root[leaf]);

    while(i != 0){
        if(root[PARENT]->left->hash == root[i]->hash){
            strcpy(auth[counter], root[PARENT]->right->hash);

            counter++;
        }
        else if(root[PARENT]->right->hash == root[i]->hash){
            strcpy(auth[counter], root[PARENT]->left->hash);

            counter++;
        }

        i = PARENT;
        //printf("i after: %d\n", i);
    }
    i = 0;




    // print authentication hashes
    for(int i = 0; i<num_levels_1; i++){
        printf("%s\n", auth[i]);
    }
    i = 0;


    //printf("\nIs the leaf, %s, part of the tree?\t", root[leaf]);
    i = 0;

    memset(&concat_hash[0], '\0', sizeof(concat_hash));
    strcpy(concat_hash, auth[i] );
    // Verify (requires to get the authentication hashes first in order to fill auth)
    while( i < num_levels){
        hash_siblings(auth, i);
        i++;
    }
    //printf("On concat = %s\n",concat_hash);
    if (strcmp(concat_hash, get_root_hash(root[0])) == 0){
        printf("yes\n\n");
    }
    else{
        printf("no\n\n");
    }



    //printf("\nnum_levels: %d\n\n", num_levels);


    return 0;
}
//END MAIN


char* hash_siblings( char left[41], char right[41] ) {
    char cat[81];
    memset(&cat[0], '\0', sizeof(cat));
    strcpy(cat, left);
    strcat(cat, right);
    hash_string_merkle(cat);
    return global_hash;
}










//BELOW THIS WORKS
//puts hashed input string into global_hash
void hash_string_merkle(char* s) {
    memset(&global_hash[0], '\0', sizeof(global_hash));
    unsigned char temp[SHA_DIGEST_LENGTH] = {'\0'};
    SHA1((unsigned char*)s, strlen(s), temp);
    for(int i=0; i<SHA_DIGEST_LENGTH; i++){
        sprintf((char*)&(global_hash[i*2]), "%02x", temp[i]);
    }
}


void hash_tree(node* parent_node) {
    memset (&concat_hash[0], '\0', sizeof(concat_hash));
    strcpy(concat_hash, parent_node->left->hash);
    strcat(concat_hash, parent_node->right->hash);
    hash_string_merkle(concat_hash);
    strcpy(parent_node->hash, global_hash);
    //printf("parent node hash: %s\n global hash:");
}

void hash_leaf(node* leaf) {
    // printf("size: %d\n content: %s\n", sizeof(leaf->data), leaf->data);
    hash_string_merkle(leaf->data);
    strcpy(leaf->hash, global_hash);
}




char* get_root_hash(node *root){
    return root->hash;
}



node* newNode()
{
    node* node =
              (struct node*) malloc(0xfffff);
    node->left = NULL;
    node->right = NULL;
    return node;
}


void print2DUtil(node *root, int space)
{
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += COUNT;

    // Process right child first
    print2DUtil(root->right, space);

    // Print current node after space
    // count
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("%s\n", root->hash);

    // Process left child
    print2DUtil(root->left, space);
}

// Wrapper over print2DUtil()
void print2D(node *root)
{
   // Pass initial space count as 0
   print2DUtil(root, 0);
}
#endif
