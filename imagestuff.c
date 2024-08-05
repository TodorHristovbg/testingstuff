#include<stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

unsigned long hash(const char *str);
int ASCIISUM(char string[]);

#define TableSize 4096





typedef struct block{
    
    int numb;
    char *value;
    struct block *next;
    
}block;

block *table[TableSize];
int code = 255;
int CheckOrAdd(block *input);
int addToTable(block *input);
bool check(char input[]);
void compress(char input[]);

int main(){

int i=0;



for (int i =0; i < 256; i++)
{
    block *a = (block *)malloc(sizeof(block));

    a->value = (char *)malloc(sizeof(char)); // Allocate memory for a char
    *(a->value) = (char)i; // Assign the character value
    a->next=NULL;
}

for (int i =256; i < TableSize; i++)
{
    table[i]=NULL;
}


char test[] = "A robot may not injure a human being or, through inaction, allow a human being to come to harm. A robot must obey the orders given to it by human beings, except where such orders would conflict with the First Law. A robot must protect its own existence.";
            // geekific-geekific
//ababbabaaaab
compress(test);


 
}



unsigned long hash(const char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }

    return hash;
}


bool check(char input[]){

      int index = 256+hash(input)%(TableSize-256);

    if(input[1]=='\0'){
      
  
      return true;
    }

     

    if(table[index]==NULL){ 

 
      
       return false;}
 
    if(strcmp(table[index]->value,input)==0){ 
 
      return true; } 
      block *temp;
      temp=table[index];
      while (temp->next!=NULL)
      {
        if(strcmp(table[index]->value,input)==0){ return true;}
        temp=temp->next;
      }
      
 

    }



int addToTable(block *input){

     int index = 256+hash(input->value)%(TableSize-256);
     


    code++;
    input->numb=code;


     input->next=table[index];
     table[index]=input;
     
   // printf("hashadd success - new code %d value: %s index: %d\n",table[index]->numb,table[index]->value,index);

    


     return code;

}



void compress(char input[]){

 char current[100];
 memset(current, '\0', sizeof(current));

 int currsize; //last index of current
 int i = 0;       //iterations
 int end;         //index of char AFTER found string

 block *tempblock = NULL;


   FILE *file;
   file = fopen("LZW.txt", "w");

 while (i<strlen(input))
 {  

    current[0]=input[i];
    current[1]='\0';
    end=i+1;
    currsize=0;


  if(input[end]=='\0'){
    
    printf("compress output %d    %c\n",current[0],current[0]);
    break;
  }

    while(input[end]!='\0' && check(current)!=false){

      currsize++;
      current[currsize]=input[end];
      current[currsize+1]='\0';
      end++;
     
     
      
    }
 
    if(input[end]=='\0' && check(current) && current[1]!='\0'){
      int index = 256+hash(current)%(TableSize-256);
      printf(" we are done %s   %d\n",table[index]->value,table[index]->numb);
       fprintf(file,"%d",table[index]->numb);
      break;
    }

    tempblock = (block *)malloc(sizeof(block));
    tempblock->value = (char *)malloc(strlen(current) + 1);

    strcpy(tempblock->value,current);
    addToTable(tempblock);

  
    current[currsize]='\0';

    if(current[1]=='\0'){
      printf("compress - %d     %c\n",current[0],current[0]);
       fprintf(file,"%d ",current[0]);
    } else {

   int index = 256+hash(current)%(TableSize-256);
      fprintf(file,"%d ",table[index]->numb);
      printf("compress output for struct : %d    %s    \n",table[index]->numb,table[index]->value);
    }




    i+=currsize;
     
    memset(current, '\0', sizeof(current));
}
}
