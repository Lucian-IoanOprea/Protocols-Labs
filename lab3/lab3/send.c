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
  msg t;
  frame myframe;

  memset(t.payload,0,MAX_LEN);

  int descriptor, size, data;
  descriptor = open(argv[1], O_RDONLY);

  if( descriptor < 0 ){
    perror("Fisierul nu se poate deschide");
    return -1;
  }
 
  memset(t.payload,0,MAX_LEN);
  lseek(descriptor,0,SEEK_SET);
  // while( data = read(descriptor,myframe.payload,1395) ){
    if( data < 0){
      perror("Am terminat de citit\n");
      return -1;
    }
    t.len = data;
    myframe.sum_control = 0;
    for( int i = 0; i < data; i++ ){
      myframe.sum_control ^= myframe.payload[i];
    }
  
    memcpy(t.payload,myframe.payload,MAX_LEN);
    send_message(&t);
   
    memset(t.payload,0,MAX_LEN);
    recv_message(&t);

    if( strcmp(t.payload,"ACK") == 0){
      printf("[%s] Cadrul a fost trimis corect\n",argv[0]);
    }
    else{
      printf("[%s] Cadrul nu a fost trimis corect\n",argv[0]);

    }
 // }


  return 0;
}
