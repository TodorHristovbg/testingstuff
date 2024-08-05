#include<stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define numbproperties 3

typedef struct person
{
  char name[100];
  int age;

}person;
void trimstring(char *str);
void setName(person *person,char *name);
void setAge(person *person,int age);



int main(){

    FILE *file;
   file = fopen("jtest.json", "r");
   char tempfromfile[100];
   char tempstring[100];
   char str[100];

   memset(tempfromfile,'\0',sizeof(tempfromfile));
   memset(str,'\0',sizeof(str));
   
   char *properties[numbproperties];
   properties[0]="name";
   properties[1]="age";
   properties[2]="NO MATCH";
   

  person *aperson=NULL;
   aperson=(person *)malloc(sizeof(person));

 
    while (fgets(tempfromfile,sizeof(tempfromfile),file))
    {  
      trimstring(tempfromfile);
      if(tempfromfile[0]!='{' && tempfromfile[0]!='}' && tempfromfile[0]!='\0'){
  
      sscanf(tempfromfile,"%[ \"a-z1-9]:%[ \"a-z1-9]",str,tempstring);
      trimstring(str); 
         trimstring(tempstring);
 //   printf("split str-%s    tempfromfile-%s\n",str,tempstring);
  
      }
    if(str[0]=='\0'){
        memset(str,'\0',sizeof(str));
        continue;
    }

    int i=0;
   

    for(;i<numbproperties-1;){
      if(strcmp(properties[i],str)==0){
        printf("match found at index %d\n",i);
         goto found;
      }
   i++;
    } 


    found:
    switch (i)
    {
    case 0: setName(aperson,tempstring);
   //    printf("person pointer %p\n",aperson);
      break;
    case 1: 
   
    setAge(aperson,atoi(tempstring));
 //   printf("person pointer %p\n",aperson);
    default:
      break;
    }

      memset(str,'\0',sizeof(str));
       memset(tempstring,'\0',sizeof(str));
      memset(tempfromfile,'\0',sizeof(tempfromfile));
    }
     printf("my name is %s and my age is %d\n",aperson->name,aperson->age);
    return 0;
}


void trimstring(char *string) {
    char *start = string;  

    // Skip over leading spaces
    while (*start==' ' || *start=='\t' || *start=='\n' || *start=='"') {
        start++;
    }
  
    if (start != string) {
        char *dst = string;
         while (*start != '\0') {
            *dst = *start; 
            dst++;         
            start++;       
        }
        *dst = '\0';
    }
     int length = strlen(string);
    if (length > 1) {
        string[length - 1] = '\0'; // Null-terminate one character earlier
    }
}


void setName(person *person,char *name){

//printf("setting name : %s\n",name);
strcpy(person->name,name);


}
void setAge(person *person,int age){

person->age=age;

}
