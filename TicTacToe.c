#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void printBoard(int board[9]);
void playerturn(int *turnpotr, int *board,int *movestotal);
void gamestate(int *board,int lastmove,int *movestotal);

int main (){
     int i=0;
    int board[9] = {0};

   
    int turnval = 1;
    int *turnpotr = &turnval;
     
    printBoard(board);

    for(i=0;i<9;i++){
        playerturn(turnpotr,&board[0],&i);
        
        if(i==8){
            printf("game is a draw");
        }
    }

    return 0;
}

void playerturn(int *turnpotr, int *board, int *movestotal){
    int index=-1;
    int temp=-1;
    

    while(index > 8 || index < 0){
    printf("Enter index of your move  ");
    scanf("%d",&temp);
    if(board[temp-1]==0){
        index=temp-1;
    }
   }
     
    board[index]=*turnpotr;

    if(*turnpotr == 1){
        *turnpotr=2;
    } else {
        *turnpotr=1;
    }
    printBoard(board);
    gamestate(board,index,movestotal);

}


void gamestate(int *board,int lastmove, int *movestotal){

     

    switch ((lastmove)%3)
    {
    case 0: if((board[0]==board[3] && board[0]==board[6]) || (board[lastmove]==board[lastmove+1] && board[lastmove]==board[lastmove+2]))
     { if(board[0]!=0) {*movestotal = 9; printf("Player %d wins",board[0]); return;}} break;

    case 1: if((board[1]==board[4] && board[1]==board[7]) || (board[lastmove]==board[lastmove-1] && board[lastmove]==board[lastmove+1]))
     { if(board[1]!=0) {*movestotal = 9; printf("Player %d wins",board[1]); return;}} break;

    case 2: if((board[2]==board[5] && board[2]==board[8]) || (board[lastmove]==board[lastmove-1] && board[lastmove]==board[lastmove-2]))
     { if(board[3]!=0) {*movestotal = 9; printf("Player %d wins",board[2]); return;}} break;
      
    default:
        break;
    }
    
    if((board[0]==board[4] && board[0]==board[8]) || (board[2]==board[4] && board[2]==board[6])){
    if(board[4]!=0){
    printf("Player %d wins",board[4]);
    *movestotal = 9;
    return;
    }
    }

}



void printBoard(int board[9]){

    char line[50] = "";
    
     int i = 1;

       for(i=1; i<=9 ;i++){
            switch (board[i-1])
            {
            case 1: 
             strcat(line,"X");
                break;
            case 2: 
             strcat(line,"O");
             break;

            default:

                strcat(line," ");
                break;
            }
           
           strcat(line,"|");
        
         if(i%3==0){strcat(line, "\n");}
       }
       printf("%s",line);

} 

