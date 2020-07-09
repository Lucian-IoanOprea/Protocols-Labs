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
  msg r;
  frame myframe;
  memset(r.payload,0,MAX_LEN);
  int size;
  int ok = 0;
 
   memset(r.payload,0,MAX_LEN);

    if( recv_message(&r) < 0 ){
    perror("Cadrul nu a fost trimis\n");
    return -1;
  }
  //  memset(r.payload,0,MAX_LEN);
    memcpy(myframe.payload,r.payload,MAX_LEN);
    printf("%s",myframe.payload);
    for( int i = 0; i < strlen(myframe.payload); i++ )
      ok ^= myframe.payload[i];

     printf("[%s], %d\n",argv[0],ok);
    // printf("[%s], %d\n",argv[0],myframe.sum_control);
    if( ok != myframe.sum_control){
      printf("[%s] Eroare\n",argv[0]);
      printf(r.payload,"NACK");
    }
     else {
      printf("Daa");
      printf("[%s] Message is correct\n",argv[0]);
      sprintf(r.payload,"ACK");
    }
    send_message(&r);

  return 0;
}
