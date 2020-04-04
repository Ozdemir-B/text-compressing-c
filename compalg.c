#include<stdio.h>
#include<stdlib.h>
#include "compalg.h"
#include<string.h>

#define T_SIZE 10

typedef struct{
  int o;//offset:number of positions we need to move to move back inorder to
        //       find the start of the matching string
  int l;//lenght: lenght of the match
  char c;//character: character that comes after the maching string we encoded
}triple;


const char * read_from_txt(char * location)
{
  FILE *fpr;
  fpr=fopen(location,"r");
  char * rd_line = (char*)malloc(100*sizeof(char));
  char * rd_all =(char*) malloc(2000*sizeof(char));
  int x=0,h=0;
   
  while(fgets(rd_line,30,fpr)!=NULL){ 
    //puts(rd_line);//this loop reads the text line by line and combines every line sequentialy
    rd_all=strcat(rd_all, rd_line);  
    }
  //printf("%s",rd_all);
  return rd_all;
}

void write_to_txt(char * text, char * location)
{
  FILE * fpw=fopen(location,"w");
  fputs(text,fpw);
}

const char* yaz(char *a)
{

    char * b = (char*) malloc(30*sizeof(char));
    //printf("\n%d\n",sizeof(b));
    int x;
    for(x=0;x<5;x++){
      b[x]=a[x];
    }
    //printf("%s",b);
    return b;
}


struct triple * lz77_encode(char *text,int sbSize, int labSize)
{
  //note: offset can be max sbSize and lenght can be max labSize

  int sum=0,f=0,x;

  //finding the lenght of the text string...
  while(text[f]!=NULL){sum=sum+1;f++;} //defines the lenght of array(text file) as sum
  printf("%d is the size of the text array\n",sum);

  triple * encoded; //defining a pointer of triple(exclusive struct data type of mine)
  encoded = (triple*) calloc(sum,sizeof(triple))  ; //defining the array of triples
  
  //defining the sliding window// //i was using char * . and there is no reason anyone use it anywhere. 
  //it is useless
  
  char searchBuffer[sbSize]; char LAB[labSize]; 
  int lenText=(int) strlen(text);
  char * subSB; char * subLAB; char sub1[labSize]; char sub2[labSize]; char cr[lenText];
  //dr=(char *)malloc(sizeof(char)*200);
  //sub1=(char*)malloc(sizeof(char)*labSize);
  //subLAB=(char*)malloc(sizeof(char)*labSize);
  //searchBuffer = (char *)malloc(sizeof(char)*sbSize);
  //LAB = (char*)malloc(sizeof(char)*labSize);
  int slidingWindowSize = sbSize + labSize;
  //sliding window  ===  [search buffer][look ahaed buffer]  <--text direction--
  //sliding window is combination of search buffer and LAB.



  //START OF THE ENCODING PROCESS//
  int z,a,b,c,d;c=0;
  for(z=0;z<sum+1;z++){
     d=0;
    /*encoded atamasının yapılması için z yerine c kullanıcam. 
      çünkü zyi encode işlemi sırasında artırabilirim*/

    //filling the search and look ahead buffers with the data sequentialy//
    for(a=0;a<labSize;a++){
      LAB[a]=text[a+z];
    }
    printf("\n||||%s\n",LAB);
    for(b=0; b<z && b<sbSize ;b++){

      if(z>sbSize) searchBuffer[b]=text[b+(z-sbSize)];
      else searchBuffer[b]=text[b];
      
    }
    //printf("\n%s<--",searchBuffer); printf("%s\n",LAB);
    
    //ENCODING PART//
    int offset, lenght,o=0,u;int lenText=(int)strlen(text);

    //case 1:
    if(z==0) { encoded[c].o=0; encoded[c].l=0; encoded[c].c=LAB[0]; } //(first element)
    
    //case 2:
    if(z>0) //(not first element)
    {
      //int labLen=(int)strlen(LAB); int sbLen=(int)strlen(searchBuffer);
      
      //printf("\n->%s--%s--%d\n",searchBuffer,LAB,z);

      //case 2.1 :
      if( strchr(searchBuffer,LAB[d]) == NULL) //MATCH == FALSE  (if LAB[0] is not in SB)
      {
        //printf("yok-%d\n",c);

        encoded[c].o=0; encoded[c].l=0; encoded[c].c=LAB[d];
        
        
      }
      
      //case 2.2 :
      else // MATCH == TRUE (if LAB[0] in SB) (to search if elements comes after LAB[0] also in SB) //match durumu
      {
        //printf("var-%d\n",c); 
        
        //*********fill the temp*********************************
        while( strchr(searchBuffer,LAB[d]) != NULL )
        {
          if(LAB[d]=='\0') break;
          sub1[d]=LAB[d];
          // - > LAB daki ardarda gelen, SB içinde bulunan elemanları bir dizi içine al.
          d++;
          
        }
        //*******************************************************
        
        
        

        //case 2.2.1 :
        if(d==1) //tek elemanlı match
        {
          //cr=strstr(text,LAB);
          offset=0;
          char *dr=strchr(text,LAB[0]);
          int v = strlen(dr);
          offset=lenText-v;
          //printf(">>>%s-%s\n",text,LAB);
          //printf("\n%ld\n",strlen(LAB));
          

          //offset=100;
          encoded[c].o=offset; 
          if(LAB[d]=='\0'){ encoded[c].l=d-1;encoded[c].c=LAB[d-1];} // son eleman olması durumunu değerlendiriyor.
          else{ encoded[c].c=LAB[d];encoded[c].l=d; }
          

          //encode[c] ataması yapılması yap //tek match için
        }
        

        //case 2.2.2 ://çok elemanlı match
        if(d>1) 
        {
          //kodumun sorunlu..................--düzeldi...........................
          while(d>1)//çok elemanlı match için
          {
            //bir diziyi tamamen boşaltmak için tüm elemanlarını sırayla null olarak götermeliyim.
            //yani bir char pointer dizisinin ilk elemanını null yapmam yetmiyor.
            //saçmalık
            int r;for(r=0;r<10;r++){sub2[r]='\0';} // -> sub2 yi boşaltıyorum.

            strncpy(sub2,sub1,d);
            //printf("{{{%s-%d}}}",sub2,d);
            if(strstr(searchBuffer,sub2)!=NULL){ break;}
            else 
            {
              d=d-1; //sub1 arrayının boyutunu sondan 1 küçültmeliyim. 
              //bunun yerine boyutunu sub1 e göre ayarlayacağım sub2 dizisi oluşturdum.
            }
            }
            //////...............................................................................

          // -> encode[c] ataması yapılır.
        
          offset=0;
          char * temp;
          strncpy(temp,LAB,labSize); //to pick the firs 10 elements of an array with 10 elements. bullshit
          char * sr=strstr(text,temp);
          int v=0;
          v = (int)strlen(sr);
          //int v=0; while(sr[v]){v++;}
          //int v = (int) strlen(sr);
          
          //printf("->%s-%s\n",text,LAB);
          
          
          offset=lenText-v;

          
          encoded[c].o=offset; //encoded[c].l=d;
          if(LAB[d]=='\0'){ encoded[c].l=d-1;encoded[c].c=LAB[d-1];} // son eleman olması durumunu değerlendiriyor.
          else{ encoded[c].c=LAB[d];encoded[c].l=d; }
          
          
        }
        int r;
        for(r=0;r<10;r++){sub1[r]='\0';}
      
        z=z+d;
        lenght=d;
      }

    }
    
    
    c++;
  }
  

  return encoded;   // returns triple pointer (triple array)
}


const char * lz77_decode(struct triple * t)
{
  return 0;
}

const char * deflate(char *a)
{
  return 0;
}
