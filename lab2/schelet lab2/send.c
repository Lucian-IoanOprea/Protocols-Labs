#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "link_emulator/lib.h"

#define HOST "127.0.0.1"
#define PORT 10000


int main(int argc,char** argv){
  init(HOST,PORT);
  msg t
;  int size;
  int descriptor;
  int data;
for( int i = 1; i < argc; i++ ){
  
  memset(t.payload,0,MAX_LEN);
  sprintf(t.payload,argv[i]);
  t.len = strlen(t.payload) + 1;
  send_message(&t);

  if( recv_message(&t) < 0 ){
    perror("Eroare la primire nume fisier");
    return -1;
  }
  else {
      printf("[%s] Got reply with payload: %s\n", argv[0] , t.payload);
  }

  descriptor = open(argv[i],O_RDONLY);
  size = lseek(descriptor,0,SEEK_END);
  sprintf(t.payload,"%d",size);
  t.len = strlen(t.payload) + 1;
  send_message(&t);

   if( recv_message(&t) < 0 ){
    perror("Eroare la primire dimensiune fisier");
    return -1;
  }
  else {
      printf("[%s] Got reply with payload: %s\n", argv[0] , t.payload);
  }

  lseek(descriptor,0,SEEK_SET);

  while( data = read(descriptor,t.payload,MAX_LEN - 1)){
    if( data < 0){
      perror("Unable to read from the input\n");
    }
    else{
      t.len = data;
      send_message(&t);
        if (recv_message(&t) < 0){
                perror("receive error");
       }
       else {
                printf("[%s] Got reply with payload: ACK(%s)\n", argv[0] , t.payload);
        }
        memset(t.payload,0,MAX_LEN);
      
    }
  }

}

  return 0;
}