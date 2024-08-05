#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define TableSize 40

typedef struct Client
{
    char username[100];
    long password;
    unsigned long balance;
    struct Client* next;
}Client;



unsigned long hash(const char *str);
void addClient(int *state);
void removenewline(char *string);
bool userExists(Client *a);
void createUsersFromFile();
void hashTableAdd(Client **table,Client *user);




Client *table[TableSize];

int main(){

int a=0;
for (int a =0; a < 100; a++)
{
    table[a]=NULL;
}


createUsersFromFile();


while(a>-1 && a<3){
switch (a){
case 0: 
printf("Enter 1 to login\nEnter 2 to register a new user\nEnter 3 to exit\n");
scanf("%d",&a);
break;
case 1:
addClient(&a);
    break;
case 2:
addClient(&a);
break;
case 3:
break;

default:

    a=5;
    break;
}
}
 return 0;
}

unsigned long hash(const char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }

    return hash;
}

void addClient(int *state){
      

    Client a;

    
    char passwordstr[100];
    
    char checker[121];
    bool usernamech = true;
    bool match = false;

    FILE *file;
    file = fopen("DataBase.txt", "a+");

    printf("Username: ");
    scanf("%s",&a.username);
    
    printf("\nPassword: ");
    scanf("%s",passwordstr);
    a.password=hash(passwordstr);

   
      

    if(*state==1){
        if(userExists(&a)){
            printf("Login sucessful\n\n");
            *state=4;
            return;
        } else {
           printf("Wrong username or password\n");
         }
         
        
         
    }
    if(*state==2){

        //printf("%d",userExists(&a));


        if(userExists(&a)){
            printf("This user already exists\n\n");
        } else {
            fprintf(file,"%s\n",a.username);
            fprintf(file,"%lu\n",a.password);
            printf("Register succesful");
            *state=4;
            return;
        }
    }
 
    
  


    fclose(file); 

    

}

void removenewline(char *string){

  int size = strlen(string);
  for(;size>0;size--){
  if(string[size]=='\n'){
    string[size]='\0';
  }
  }
}
bool userExists(Client *a){

    FILE *file;
    file = fopen("DataBase.txt", "r");

   
    int index = a->password % TableSize;

    Client *temp =table[index];
   // printf("%s\n",temp->username);
   // printf("%d\n",temp->password);

  
  
    while (temp!=NULL)
    {
       if(strcmp(temp->username,a->username)==0 && (temp->password==a->password)==1){
         
         printf("user found\n");
         return true;

       }
    
       temp=temp->next;

    }
   
   
    return false;

    
}

void hashTableAdd(Client **table, Client *user){


if(user==NULL){
    return;
}


int index = user->password % TableSize;

//if(table[index]!=NULL){printf("Current user here    %s        %d\n",table[index]->username,table[index]->password);}


user->next=table[index];
table[index]=user;

//printf("New user here        %s        %d      %d\n",table[index]->username,table[index]->password,index);



}



void createUsersFromFile(){

    FILE *file;
    file = fopen("DataBase.txt", "r");
    char temp[121];
    bool user=true;
    Client *a = NULL;
    printf("%p",a);

    while((fgets(temp,sizeof(temp),file))){
        removenewline(&temp[0]);
      
             
        if(user){
          
           a = (Client *)malloc(sizeof(Client));
             printf("%p\n\n",a);
            strcpy(a->username,temp);
            user=false;
             
      
           
        } else {
            a->password=atoi(temp);
            user=true;
           //  printf("Adding user:    %s        %d\n",a->username,a->password);
             
            hashTableAdd(&table[0],a);

         
        }
        
       
        
    }
}

