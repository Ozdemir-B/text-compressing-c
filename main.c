#include<stdio.h>
#include<stdlib.h>
#include "compalg.h"
#include<string.h>

typedef struct{int o;int l; char c;} triple;

int main(){
  
    //char * rd_all =(char*) malloc(200*sizeof(char));
    char * rd_all; rd_all=read_from_txt("text.txt");
    
    
    triple * arr=(triple*)malloc(sizeof(triple)*200); //creating an array of triples(array of structs)

    arr = lz77_encode(rd_all,30,10);
    int i; 
    for(i=0;i<25;i++){
    printf("\n%d , %d , -%c- \n",arr[i].o,arr[i].l,arr[i].c);
    }
    //finding the lenght of the string
    int sum=0, f=0;
    while(rd_all[f]!=NULL){sum=sum+1;f++;}//sum is the lenght (with \n and spaces)

    //int z; for(z=0;z<sum;z++) printf("%d-%c\n",arr[z].o,arr[z].c);

    
   
    return 0;
}
