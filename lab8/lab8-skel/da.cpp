#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


using namespace std;

int main(){
   int arr[2]={0}; 
   arr[1] = 111111;
   fprintf(stdout,"%d",arr[1]);
   fflush(stdout);
  arr[3] = 10;  // Accessing out of bound 
   return 0; 


}
