#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "link_emulator/lib.h"

#define HOST "127.0.0.1"
#define PORT 10001


int main(int argc,char** argv){
 
  init(HOST,PORT);

  int current_size;

  for( int i = 1; i < argc; i++ ){
    int descriptor;
    int size;
    int data;
    msg r;
    msg t;
      memset(r.payload,0,MAX_LEN);
      memset(t.payload,0,MAX_LEN);
      if( recv_message(&r) < 0){
        perror("Unable to receive file_name");
        return -1;
      }
        printf("[%s] Got msg with payload:,sending ACK %s\n", argv[0], r.payload);
        strcat(r.payload,"-receiver");
        descriptor = open(r.payload, O_WRONLY | O_CREAT | O_TRUNC, 0644);

        if( descriptor < 0 ){
          printf("Nu se poate creea fisier");
          return -1;
        }
        
        sprintf(t.payload,"ACK(%s)",r.payload);
        t.len = strlen(t.payload)+ 1;
        send_message(&t);
        printf("[%s]ACK sent\n",argv[0]);
      
    if (recv_message(&r) < 0) {
        perror("Receive message");
        return -1;
      }

    printf("[%s] Got msg with payload: <%s>, sending ACK...\n",argv[0], r.payload);
     size = atoi(r.payload);
    memset(t.payload,0,MAX_LEN);
    sprintf(t.payload,"ACK%s",r.payload);
    t.len = strlen(t.payload) + 1;
    send_message(&t);
    printf("[%s] ACK sent\n",argv[0]);

    while( size ){
      if( recv_message(&r) < 0 ){
         perror("Receive message");
          return -1;
      }
       printf("[recv] Got msg with payload: <%s>, sending ACK...\n", r.payload);
       current_size = write(descriptor,r.payload,r.len);
       send_message(&r);
       size -= r.len;
       memset(r.payload,0,MAX_LEN);

    }

    close(descriptor);
  }


  return 0;
}
