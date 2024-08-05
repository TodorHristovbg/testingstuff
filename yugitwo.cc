#include <iostream>
#include <time.h>  

class Player;
class EquipSpell;
class Board;



class Card{

    std::string Name;
protected:
    Player *Owner;
    Board *ownboard;
public:

   

    Card(std::string name, Player* owner){
        setname(name);
       
    }
     Card(){
       setname("DEFAULT");

    }
    void empty(){
        setname("DEFAULT");
    }

    void setname(std::string name){
        Name=name;
       
    }  
    
    std::string getname(){
        return Name;
    }

    void setowner(Player* owner){
     Owner=owner;
    }
    Player* getowner(){
        return Owner;
    }

    virtual void Play(){
      
    }
    virtual void Display(){
        std::cout<<"Empty Card"<<std::endl;
    }

};

class Monster: public Card{

    int Attack;
    int Def;
    int Level;
    int attackposition=0;
    int attacks=0;
public:
    Monster(std::string name,int attack,int def, int level, Player* owner){
        
        setname(name);
        setattack(attack);
        setdef(def);
        setlevel(level);
        setowner(owner);
    }
    Monster(){
        setname("DEFAULT");
        setattack(0);
        setdef(0);
        setlevel(0);
    }

    void empty(){
        setname("DEFAULT");
        setattack(0);
        setdef(0);
        setlevel(0);
    }

    void Display(){
    //    std::cout<<"THIS IS CALLED"<<std::endl;
        std::string position;
        if(attackposition==2){ position= " in attack";}
        else if(attackposition==1){ position=" in defense";}
        else {
            position="";
        }
        


        std::cout<<getname()<<": Atk - "<<getattack()<<" Def - "<<getdef()<<" Level: "<<getlevel()<<position<<std::endl;
    }

    void addnumberofattacks(int i){
        attacks+=i;
    }
    void resetattacks(){
        attacks=0;
    }
    int getnumberofattacks(){
        return attacks;
    }

    void setattack(int attack){
        Attack=attack;
    }
    int getattack(){
        return Attack;
    }
    void changeattack(int change){
        Attack+=change;
    }

    void setdef(int def){
        Def=def;
    }
    int getdef(){
        return Def;
    }

    void setlevel(int level){
        Level=level;
    }
    int getlevel(){
        return Level;
    }  
    
    void setpositiontoattack(){
        attackposition=2;
    }
    void setpositiontodef(){
        attackposition=1;
    }
    void copyposition(int position){
        attackposition=position;
    }
    int getposition(){
        return attackposition;
    }


    void copyMonster(Monster* temp){
        setname(temp->getname());
        setattack(temp->getattack());
        setdef(temp->getdef());
        setlevel(temp->getlevel());
        setowner(temp->getowner());
        copyposition(temp->getposition());
    }

    ~Monster(){

     //   free(Attack);
    }


};

class Spell: public Card{

    int Change;
   
    
    
public:

    Spell(std::string Name){
            setname(Name);
            
    }

    Spell(){
        setname("DEFAULT");
    }


    virtual void copyspell(Spell* target){
        setname(target->getname());
        setowner(target->getowner());
    
    }

    void Display(){
        std::cout<<getname();
      
        
        std::cout<<std::endl;
    }
    
    virtual void effect(){
        std::cout<<"Standard effect called"<<std::endl;
    }

    virtual ~Spell(){
     //   std::cout<<"DEFAULT DESTRUCTOR CALLED"<<std::endl;
    }
    };

class EquipSpell : public Spell{

int Change;
Monster* Target;
bool Effectsenemy;  //0 - effects ally, 1 - effects enemy

public:

    EquipSpell(std::string Name,int change, bool enemy){
        setname(Name);
        setchange(change);
        settarget(enemy);
    }

    EquipSpell(){
        setname("DEFAULT");
    }
    void setboard(Board* own){
        ownboard=own;
    }
    void setchange(int change){
        Change=change;
    }
    int getchange(){
        return Change;
    }

    void settarget(bool enemy){
        Effectsenemy=enemy;
    }

    bool gettarget(){
        return Effectsenemy;
    }


    void effect(Monster* target){
        Target=target;
        target->changeattack(Change);

    }

    void Display(){
        std::cout<<getname()<<" - adds "<<getchange()<<std::endl;
    }

    ~EquipSpell(){
        std::cout<<"SELF DESTRUCT WOWWA"<<std::endl;
       Target->changeattack(-Change);
    }


};




class Board{

public:


Monster* monsterzone[6];
Spell* spellzone[6];

Board(){
    for(int i = 0;i<6;i++){
        monsterzone[i]= new Monster();
        spellzone[i]=new Spell();
    }
}

void destroymonster(int index){
    std::cout<<monsterzone[index]->getname()<<"Has been destroyed"<<std::endl;
    delete monsterzone[index];
    monsterzone[index]=new Monster();
    //

    //afasfsa
}

void destroybackrow(int index){

    if(dynamic_cast<EquipSpell*>(spellzone[index])!=nullptr){
        std::cout<<"WOWZA AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"<<std::endl;
    }

    delete spellzone[index];
    spellzone[index]=new Spell();
}


bool hasmonsterat(int index){
    if(monsterzone[index]->getname()=="DEFAULT"){
        return false;
    }
    return true;
}

Monster* getmonsterat(int index){
    if(hasmonsterat(index)){
        return monsterzone[index];
    }
    return nullptr;
}

bool hasbackrow(int index){
    if(spellzone[index]->getname()=="DEFAULT"){
        return false;
    }
    return true;

}

Spell* getspellat(int index){
    if(hasbackrow(index)){
        return spellzone[index];
    }
}



void triggerspell(int index){

    if(dynamic_cast<EquipSpell*>(spellzone[index])!=nullptr){
        int index;
        std::cout<<"Enter index of monster to be equipped"<<std::endl;
        std::cin>>index;
        while (!hasmonsterat(index))
        {
             std::cout<<"Please enter a valid index of monster to be equipped"<<std::endl;
             std::cin>>index;
        }
        
        dynamic_cast<EquipSpell*>(spellzone[index])->effect(getmonsterat(index));

    }


}














};


class Player{

    std::string Name;
    int lifepoints=0;
    Card *hand[6];
    Board* ownboard;
    Board* enemyboard;
    int normalsummon=0;

public:
  Player(std::string name){

        setname(name);
        addlifepoints(8000);
        for(int i=0;i<6;i++){
            hand[i]=new Card();

        }

    }

    void addnormalsummon(int i){
        normalsummon+=i;
    }
    void subtractnormalsummon(int i){
        normalsummon-=i;
    }
    int getnormalsummon(){
        return normalsummon;
    }
    void setname(std::string name){
        Name=name;
        
    }  
    
    std::string getname(){
        return Name;
    }
    void addlifepoints(int change){
        lifepoints+=change;
    }
    void removelifepoints(int change){
        lifepoints-=change;
    }
    int getlifepoints(){
        return lifepoints;
    }
    void setownboard(Board* own){
        ownboard=own;
    }
    void setenemyboard(Board* enemy){
        enemyboard=enemy;
    }

    bool ishandfull(){
        if(hand[5]->getname()=="DEFAULT"){
            return false;
        }
        return true;
    }
    bool ishandempty(){
        if(hand[0]->getname()=="DEFAULT"){
            return true;
        }
        return false;
    }
    bool ismonsterzoneempty(){
        int i=0;
        while(i<6){
            if(hasmonsterat(i)){
                return false;
            }
            i++;
        }
        return true;
    }

     void Draw(Card *card){
        int i=0;


        while (i<6)
        {   
            if(hand[i]->getname()=="DEFAULT"){

          

                hand[i]=card;
        
                  std::cout<<Name<<" has drawn ";
                  hand[i]->Display();
            
                return;
            }
            i++;
        }
        std::cout<<Name<<" has a full hand and cant draw."<<std::endl;
    
    }

    bool monsterzonefull(){
       
        int i=0;
        while (i<6)
        {
            if(!hasmonsterat(i)){
              
                return false;
            }
            i++;
        }
        std::cout<<"Monster zone is full??"<<std::endl;
        return true;
    }

    bool spellzonefull(){
         int i=0;
        while (i<6)
        {
            if(!hasbackrowat(i)){
                return false;
            }
            i++;
        }
        return true;
    }

    bool legalmove(int indexinhand){

      if(indexinhand<0 || indexinhand>5 || hand[indexinhand]->getname()=="DEFAULT")
        {
            std::cout<<"This is an illegal move"<<std::endl;
            return false;
        }
        

        if(dynamic_cast<Monster*>(hand[indexinhand])!= nullptr){
            if(getnormalsummon()<1){
                std::cout<<"You do not have any normal summons left"<<std::endl;
                return false;
            }
         
            if(monsterzonefull()){
                std::cout<<"Your monsterzone is full so you cant summon more monsters"<<std::endl;
                return false;
            }
        }


        if(dynamic_cast<Spell*>(hand[indexinhand])!= nullptr){
            if(spellzonefull()){
                std::cout<<"Your backrow is full and you cant play more spells/traps"<<std::endl;
            }
        }


    return true;

    }
    void Play(int indexinhand){



       if(dynamic_cast<Monster*>(hand[indexinhand])!= nullptr){ 
        playMonster(indexinhand); 
        }
       
       if(dynamic_cast<EquipSpell*>(hand[indexinhand])!= nullptr){ 
        
        dynamic_cast<EquipSpell*>(hand[indexinhand])->setboard(ownboard);
        
        playSpell(indexinhand); }

       normalizehand(indexinhand);
       displayhand();
  
    }


    void displaymonsterzone(){
        int i=0;
    std::cout<<"Displaying "<<Name<<"'s monsterzone:"<<std::endl;

    

    while (i<6)
    {
            ownboard->monsterzone[i]->Display();
 
        i++;
    }
    std::cout<<std::endl;
    }

    void displaybackrow(){
          int i=0;
    std::cout<<"Displaying "<<Name<<"'s backrow:"<<std::endl;
    while (i<6)
    {
            ownboard->spellzone[i]->Display();
 
        i++;
    }
    std::cout<<std::endl;
    }


 void displayboard(){
    
    displaymonsterzone();
    displaybackrow();
   
   }

    
    void displayhand(){
        int i = 0;
        std::cout<<"Displaying "<<Name<<"'s hand: \n"<<std::endl;
    while (i<6)
    {
     //   if(hand[i]->getname()!="DEFAULT"){
            
            hand[i]->Display();
   //     }
        i++;
    }
    std::cout<<std::endl;
    }
    
   bool hasbackrowat(int index){
    ownboard->hasbackrow(index);
   }

   Spell* getspellat(int index){
   ownboard->getspellat(index);
   }


   bool hasmonsterat(int index){

        ownboard->hasmonsterat(index);
    }

    Monster* getmonsterat(int index){

        ownboard->getmonsterat(index);
    }

    void addBPattacks(){
        int i=0;
        while(i<6){
            if(hasmonsterat(i)){
                if(getmonsterat(i)->getposition()==2){
                getmonsterat(i)->addnumberofattacks(1);
                }
            }
            i++;
        }
    }

    void resetnumberofattacks(){
         int i=0;
        while(i<6){
            if(hasmonsterat(i)){
            getmonsterat(i)->resetattacks();
            }
                

            i++;
        }
    }

 void playMonster(int indexinhand){

     

        if(dynamic_cast<Monster*>(hand[indexinhand])->getlevel()>4){
                        
                        if(dynamic_cast<Monster*>(hand[indexinhand])->getlevel()>7){
                            Tribute(2);
                        } else {
                            Tribute(1);
                        }
                    }

        int i=0;
         while(i<6){

        

           if(!hasmonsterat(i)){
          
                  delete ownboard->monsterzone[i];
                  ownboard->monsterzone[i]=dynamic_cast<Monster*>(hand[indexinhand]);
             

                int attackposition;
                std::cout<<"1 - attack position     2 - defense position"<<std::endl;
                std::cin>>attackposition;
                if(attackposition==1){
                    ownboard->monsterzone[i]->setpositiontoattack();
                } else{
                    ownboard->monsterzone[i]->setpositiontodef();
                    
                }

                std::cout<<Name<<" has summoned ";
            
                
                ownboard->monsterzone[i]->Display();
                subtractnormalsummon(1);

                hand[indexinhand]=new Card();
                return;
              
            }
            i++;
        }
        std::cout<<Name<<" cannot summon more monsters"<<std::endl;
    }


    void Tribute(int tributes){
        int i=0;
        int temp=tributes;
        while(i<6){
            if(ownboard->monsterzone[i]->getname()!="DEFAULT"){
               temp--;
            }
            i++;
        }
        if(temp>0){
            std::cout<<"Not enough tributes on field"<<std::endl;
            return;
        }else{
            for(int i=0;i<tributes;i++){
                bool valid=false;
                int index;
                while (!valid)
                {
               
                std::cout<<"Enter a valid index of monster to be tributed"<<std::endl;
                std::cin>>index;
                if(ownboard->monsterzone[index]->getname()!="DEFAULT"){valid=true;}
                }
                
                ownboard->destroymonster(index);
            }
        }
    }

    void playSpell(int indexinhand){

        int i =0;
        while (i<6)
        {
            if(!hasbackrowat(i)){
                delete ownboard->spellzone[i];
                ownboard->spellzone[i]=dynamic_cast<EquipSpell*>(hand[indexinhand]);
                
                std::cout<<Name<<" has activated ";
                ownboard->spellzone[i]->Display();
                
                if(dynamic_cast<EquipSpell*>(ownboard->spellzone[i])!=nullptr){

      
                    
                    hand[indexinhand]=new Card();
                    ownboard->triggerspell(i);
                    ownboard->spellzone[i]->Display();
                    return;
                }
                
                ownboard->spellzone[i]->effect();
                
                return;
            }
            i++;
        }
        

        std::cout<<Name<<" cannot play more spells"<<std::endl;
    }

    void destroymonster(int index){
        ownboard->destroymonster(index);
    }
    void destroybackrow(int index){
        ownboard->destroybackrow(index);
     
    }


void normalizehand(int index){
        int i=index;
        while (i<5)
        {
              if(hand[i+1]->getname()!="Default"){
        //    std::cout<<array[i+1]->getname()<<"is name of next"<<std::endl;

                if(dynamic_cast<Monster*>(hand[i+1])!= nullptr){
                
                delete hand[i];
                hand[i]=hand[i+1];
                //new Monster();
              //  dynamic_cast<Monster*>(hand[i])->copyMonster(dynamic_cast<Monster*>(hand[i+1]));


                }

                if(dynamic_cast<EquipSpell*>(hand[i+1])!=nullptr){
                

                delete hand[i];
                hand[i]=hand[i+1];
   
            
                }


             //  delete hand[i+1];
               hand[i+1]=new Card();
               i++;
}

        }


}

};


void randomizeseed();
void generateMonster(Player *owner);
void generateEquip(Player *owner);
void drawcard(Player* player);
void fillhand(Player* player);
void whogoesfirst(Player* player1, Player* player2);
bool playacard();
void MainPhase1(Player* player);
void getyourgameon(Player* player1, Player* player2);

int main(){

    std::string name;

    std::cout<<"Name of first player"<<std::endl;
    std::cin>>name; 
    Player player1(name);
  


    std::cout<<"Name of second player"<<std::endl;
    std::cin>>name; 
    Player player2(name);

    whogoesfirst(&player1,&player2);
    


  //  Monster a("Blue eyes white dragon",3000,2000,4,&player1);
 // player1.Draw(&a);




    return 0;
}
void randomizeseed(){
    srand(rand()%31+time(NULL));
}

    void generateMonster(Player *owner){

    int Atk = (rand()%20)*100;
    int Def = (rand()%20)*100;

    Monster* monster = new  Monster("Mysterious monster", Atk,Def, 4,owner);
    owner->Draw(monster);

}

    void generateEquip(Player *owner){

    int change = (rand()%6)*100+300;
    EquipSpell* equip = new EquipSpell("Empowering chant",change,0);
    owner->Draw(equip);

 }

    void drawcard(Player* player){
randomizeseed();
int type = rand()%3;
if(type==0){
    generateEquip(player);
} else {
    generateMonster(player);
}



}

void fillhand(Player* player){

  while (!player->ishandfull())
  {
    drawcard(player);
  }
  

};


void whogoesfirst(Player* player1, Player* player2){
bool turn = rand()%2;   //0 - player1 stays player1

std::cout<<"\n"<<std::endl;
if(turn){
    std::cout<<player2->getname()<<" will go first"<<std::endl;
    getyourgameon(player2,player1);
 

} else{
    std::cout<<player1->getname()<<" will go first"<<std::endl;
    getyourgameon(player1,player2);
}



}


bool playacard(){

 int play;
 std::cout<<"Play a card? 1 - yes    2 - no"<<std::endl;
 std::cin>>play;
    if(play==1){
        return true;
    } else {
        
        return false;
    }


}


void MainPhase1(Player* player){

    if(player->ishandempty()){
        std::cout<<player->getname()<<" has an empty hand"<<std::endl;
    }
   std::cout<<player->getlifepoints()<<std::endl;
    player->displayhand();
    player->displayboard();


    int index;
    player->addnormalsummon(1);
    while (playacard())
    {
        int index;
        std::cout<<"Which card do you want to play?"<<std::endl;
        std::cin>>index;
        index--;
       
          while (!(player->legalmove(index)))
         {
          std::cout<<"try a different move or return by entering 0"<<std::endl;
          std::cin>>index;
          index--;
          if(index==-1){
            break;
          }
         }
         if(index!=-1) {player->Play(index);}
    }
    
    std::cout<<player->getname()<<"'s MainPhaseOne has ended\n"<<std::endl;
    player->displayhand();
    player->displayboard();

}

bool declareattack(){
    int play;
 std::cout<<"Declare an attack? 1 - yes    2 - no"<<std::endl;
 std::cin>>play;
    if(play==1){
        return true;
    } else {
        
        return false;
    }

}


void BattlePhase(Player* attacker, Player* defender){

    attacker->addBPattacks();
    
    while (declareattack())
    {
        int attackindex;
        int defindex;
        bool valid = false;
        
        while (!valid)
        {   
               attacker->displayboard();

              std::cout<<"Which monster are you attacking with?"<<std::endl;
              std::cin>>attackindex;
              attackindex--;
              if(attackindex==-1){
                break;
              }
              if(attacker->hasmonsterat(attackindex)){
                if(attacker->getmonsterat(attackindex)->getnumberofattacks()>0){
                    valid=!valid;
                } else{
                    std::cout<<"This mosnter doesnt have any attacks left"<<std::endl;
                }
              } else {
                std::cout<<"Please enter a valid monster index or 0 to quit"<<std::endl;
              }

        }
            if(attackindex==-1){continue;}


        if(defender->ismonsterzoneempty()){
            std::cout<<attacker->getmonsterat(attackindex)->getname()<<" attacks directly for "<<attacker->getmonsterat(attackindex)->getattack()<<" damage"<<std::endl;
            defender->removelifepoints(attacker->getmonsterat(attackindex)->getattack());
            std::cout<<defender->getname()<<" has "<<defender->getlifepoints()<<" lifepoints left"<<std::endl;
            attacker->getmonsterat(attackindex)->resetattacks();
        } else {

        while (valid)
        {
            defender->displaymonsterzone();

            std::cout<<"Which monster do you want to attack?"<<std::endl;
              std::cin>>defindex;
              defindex--;
            if(defender->hasmonsterat(defindex)){
                valid=!valid;
            } else {
                 std::cout<<"Please enter a valid monster index"<<std::endl;
            }

        }
        

            int importantstat;
            bool takedamage;
            if(defender->getmonsterat(defindex)->getposition()==2){
                importantstat=defender->getmonsterat(defindex)->getattack();
                takedamage=true;
            } else {
                 importantstat=defender->getmonsterat(defindex)->getdef();
                 takedamage=false;
            }
        if(attacker->getmonsterat(attackindex)->getattack()>importantstat){

            if(takedamage){
                defender->removelifepoints(attacker->getmonsterat(attackindex)->getattack()-importantstat);
            }
            defender->destroymonster(defindex);
        } else {
            attacker->removelifepoints(importantstat-attacker->getmonsterat(attackindex)->getattack());
            if(attacker->getmonsterat(attackindex)->getattack()==importantstat){
            defender->destroymonster(defindex);
            }
            attacker->destroymonster(attackindex);
            
        }

         attacker->getmonsterat(attackindex)->resetattacks();
    }
    }
    std::cout<<attacker->getname()<<"'s battlephase has ended"<<std::endl;
    attacker->resetnumberofattacks();



}



void getyourgameon(Player* player1, Player* player2){


std::cout<<player1->getname()<<" versus " <<player2->getname()<<std::endl;
std::cout<<std::endl;

fillhand(player1);
//player1->displayhand();
Board p1board;
player1->setownboard(&p1board);

std::cout<<"\n"<<std::endl;
fillhand(player2);
//player2->displayhand();
Board p2board;
player2->setownboard(&p2board);

int turn=1;

while (player1->getlifepoints()>0 && player2->getlifepoints()>0)
{

    Player* attacker;
    Player* defender;


    if(turn%2==1){
        std::cout<<player1->getname()<<"'s turn."<<std::endl;
       attacker=player1;
       defender=player2;
    } else {
        std::cout<<player2->getname()<<"'s turn."<<std::endl;
        attacker=player2;
        defender=player1;
    }

    MainPhase1(attacker);
    BattlePhase(attacker,defender);
    turn++;

}

}
