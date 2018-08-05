#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <openssl/sha.h>
//#include <string>
#define PORT 8080
#define K 8



long BUFFER_SIZE = 4096;
int sock = 0, valread;
char* pre_image[SHA_DIGEST_LENGTH*2] = {0};
char* result[SHA_DIGEST_LENGTH*3] = {0};
char hash[SHA_DIGEST_LENGTH*2] = {0};
char hash2[SHA_DIGEST_LENGTH*2] = {0};
char* removed;
struct sockaddr_in address,serv_addr;


void start_networking();
char* receive_message();
void send_message(char* message);
char* itob(int i);
void hash_string(char*);

int main(int argc, char const *argv[])
{
    start_networking();
    char *message[BUFFER_SIZE];
    strcpy(message, "Hello from client\n");

    send_message(message);
    printf("Hello message sent\n");

    while(1){
      memset(&hash[0], '\0', sizeof(hash));
      memset(&hash2[0], '\0', sizeof(hash2));
      memset(&result[0], '\0', sizeof(result));
      strcpy(hash, receive_message());
      if(strcmp(hash, "1") == 0){
        break;
      }
      send_message("Got the hash value\n");
      strcpy(pre_image, receive_message());

      for(int i=0; i<(pow(2,K)); i++){
        memset(&result[0], '\0', sizeof(result));
        strncpy(result, pre_image, sizeof(pre_image));
        strcat(result, itob(i));
        hash_string(result);
        if(check_hashes() == 1){
          send_message(itob(i));
          receive_message();
          send_message("Thank you");
          break;
        } else if(i == (pow(2,K)-1)){
          printf("Can't solve the puzzle\n\n");
          send_message("can't solve");
          receive_message();
          send_message("Thank you");
        }
      }
    }

    return 0;
}

int check_hashes(){
  if(strcmp(hash, hash2) == 0){
    return 1;
  } else {
    return 0;
  }
}

void hash_string(char* s) {
  unsigned char temp[SHA_DIGEST_LENGTH] = {'\0'};
  SHA1((unsigned char*)s, strlen(s), temp);
  for(int i=0; i<SHA_DIGEST_LENGTH; i++){
    sprintf((char*)&(hash2[i*2]), "%02x", temp[i]);
  }
}

char* itob(int i) {
   static char bits[K] = {'0'};
   for(int i=0; i<K; i++){
     bits[i] = '0';
   }
   int bits_index = K-1;
   while ( i > 0 ) {
      bits[bits_index--] = (i & 1) + '0';
      i = ( i >> 1);
   }
   return bits;
}


/* To send a message:
 * just overwrite char* message (currently is of size 4096)
 * and use send_message(message)
 */
void send_message(char* message){
    send(sock, message , strlen(message) , 0 );
}
/* To receive a message:
 * just make whatever you want equal to receive_message()
 * or use printf("%s\n", receive_message());
 * to immediately print the received message to the console
 */
char* receive_message(){
    char* buffer = malloc(sizeof(char)*4096);
    memset(&buffer[0], '\0', sizeof(buffer));
    read( sock , buffer, BUFFER_SIZE);
    return buffer;
}

void start_networking(){
   if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }


}
