#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <openssl/sha.h>
#define LEAVES 8
#define COUNT 10
#define PARENT ((int)floor(((i-1)/2)))
#define MOST_LEFT_LEAF ((int)(num_nodes-1)/2)
#define LEAF 12
#define LEAF_TO_VERIFY 12


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
node* newNode(char* input);

int isEmpty(node *root);
void push(node** root, char* input);

void print2DUtil(node *root, int space);
void print2D(node *root);
char* get_root_hash(node *root);
void hash_tree(node* parent_node);
void hash_string(char* s);
void verify_hash( char (*auth)[41], int i);

int main(){
    /*create root*/
    int num_nodes = (LEAVES*2)-1;
    int num_levels = (int)log2(LEAVES);
    int num_levels_1 = (num_levels+1);


    printf("num_nodes: %d\n", num_nodes);


    node* root[num_nodes];

    for ( int i=0; i< num_nodes; i++){
        root[i] = newNode("data");
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



    for(int i =0; i<num_nodes; i++){

    }



    //print tree
    print2D(root[0]);

    //get authentication hashes
    //printf("\nroot hash is %s\n\n", get_root_hash(root[0]));


    char auth[num_levels_1][41];
    memset(auth,'\0', sizeof(auth) );
    int counter = 0;
    int i = LEAF;
    strcpy(auth[counter], root[LEAF]);
    counter++;
    printf("\nleaf is %s\n\nAuthentication hashes are:\n\n", root[LEAF]);

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


    printf("\nIs the leaf, %s, part of the tree?\t", root[LEAF_TO_VERIFY]);
    i = 0;

    memset(&concat_hash[0], '\0', sizeof(concat_hash)); 
    strcpy(concat_hash, auth[i] );
    // Verify (requires to get the authentication hashes first in order to fill auth)
    while( i < num_levels){        
        verify_hash(auth, i);
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


void verify_hash( char (*auth)[41], int i) {
    // printf("On i=%d\n",i);
    // printf("On auth[i+1] = %s\n",auth[i+1]);
    //printf("On concat = %s\n",concat_hash);
    strcat(concat_hash, auth[i+1]);
    hash_string(concat_hash);
    strcpy(concat_hash, global_hash);

}










//BELOW THIS WORKS
//puts hashed input string into global_hash
void hash_string(char* s) {
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
    hash_string(concat_hash);
    strcpy(parent_node->hash, global_hash);
    //printf("parent node hash: %s\n global hash:");
}

void hash_leaf(node* leaf) {
    hash_string(leaf->data);
    strcpy(leaf->hash, global_hash);
}




char* get_root_hash(node *root){
    return root->hash;
}



node* newNode(char* input)
{
    node* node =
              (struct node*) malloc(0xfffff);
    node->left = NULL;
    node->right = NULL;
    //strcpy(node->hash, input);
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
