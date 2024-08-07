#include <iostream>
#include <time.h>  

class Card;
class Monster;
class Spell;
class Player;
class Equipspell;


class Card{

    std::string Name;
protected:
    Player *Owner;
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
        std::string position;
        if(attackposition==2){ position= " in attack";}
        else if(attackposition==1){ position=" in defense";}
        else {
            position="";
        }
        


        std::cout<<getname()<<": Atk - "<<getattack()<<" Def - "<<getdef()<<" Level: "<<getlevel()<<position<<std::endl;
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

             // 0 - normal , 1 - equip , 2 - draw

    int Change;

public:

    Spell(std::string Name){
            setname(Name);
       
    }

    Spell(){
        setname("DEFAULT");
    }


    void copyspell(Spell* target){
        setname(target->getname());
        setowner(target->getowner());
        setchange(target->getchange());
    }

    void Display(){
        std::cout<<getname();
      
        
        std::cout<<std::endl;
    }
    


  
    void setchange(int change){
        Change=change;
    }
    int getchange(){
        return Change;
    }


    void equip(int monsterindex){

      //  if(Owner->hasmonsterat(monsterindex)){
            
       //  Owner->getmonsterat(monsterindex)->changeattack(Change);

        }



    };






class Player{
    
    std::string Name;
    int lifepoints=0;
   
    Spell spellzone[6];
    Monster monsterzone[6];
    Player *Enemy;

    public:

     Card *hand[6];

    Player(std::string name){

        setname(name);
        for(int i=0;i<6;i++){
            hand[i]=new Card();

        }

    }

    void setenemy(Player* enemy){
        Enemy=enemy;
    }

    void setname(std::string name){
        Name=name;
        addlifepoints(8000);
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

    void Draw(Card *card){
        int i=0;


        while (i<6)
        {   
            if(hand[i]->getname()=="DEFAULT"){

                hand[i]=card;
           //     std::cout<<Name<<" has drawn "<<hand[i]->getname()<<i<<std::endl;
                  std::cout<<Name<<" has drawn ";
                  DisplayCard(i);
                return;
            }
            i++;
        }
        std::cout<<Name<<" has a full hand and cant draw."<<std::endl;
    }

    virtual void DisplayCard(int index){
        hand[index]->Display();
    }


   void Play(int indexinhand){

        if(indexinhand<0 || indexinhand>5 || hand[indexinhand]->getname()=="DEFAULT")
        {
            std::cout<<"This is an illegal move"<<std::endl;
            return;
        }

       if(dynamic_cast<Monster*>(hand[indexinhand])!= nullptr){ playMonster(indexinhand); }
      //if(dynamic_cast<Spell*>(hand[indexinhand])!= nullptr){ playSpell(indexinhand);
      std::cout<<"IS PROBLEM HERE?"<<std::endl;
      // normalizehand(indexinhand);
    }

    void displayboard(){
    int i=0;
    std::cout<<"Displaying "<<Name<<"'s board:"<<std::endl;
    while (i<6)
    {
      //  if(monsterzone[i].getname()!="DEFAULT"){
            
            monsterzone[i].Display();
            
    //    }
        i++;
    }
   
   }

    void displayhand(){
    int i=0;
    std::cout<<"Displaying "<<Name<<"'s hand:"<<std::endl;
    while (i<6)
    {
     //   if(hand[i]->getname()!="DEFAULT"){
            
            hand[i]->Display();
   //     }
        i++;
    }

    }

    bool hasmonsterat(int index){
        if(monsterzone[index].getname()=="DEFAULT"){
            return false;
        } return true;
    }

    Monster* getmonsterat(int index){

        if(hasmonsterat(index)){

        return &monsterzone[index];
        }

        return nullptr;
    }




 ~Player(){
    std::cout<<"deleting"<<std::endl;
    for(int i =0;i<6;i++){
      //  std::cout<<hand[i]<<std::endl;
        delete hand[i];
    }
   
    }


    private:        

   

    
    void playEquip(int indexinhand, int targetindex){
        
        dynamic_cast<EquipSpell*>(hand[indexinhand])->equip(targetindex);

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
          
                monsterzone[i].copyMonster(dynamic_cast<Monster*>(hand[indexinhand]));
               

                dynamic_cast<Monster*>(hand[indexinhand])->empty();

                int attackposition;
                std::cout<<"1 - attack position     2 - defense position"<<std::endl;
                std::cin>>attackposition;
                if(attackposition==1){
                    monsterzone[i].setpositiontoattack();
                } else{
                    monsterzone[i].setpositiontodef();
                    
                }

                std::cout<<Name<<" has summoned ";
             //   dynamic_cast<Monster*>(&monsterzone[i])->Display();
                monsterzone[i].Display();

                std::cout<<"WE RETURN FROM SUMMON"<<std::endl;
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
            if(monsterzone[i].getname()!="DEFAULT"){
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
                if(monsterzone[index].getname()!="DEFAULT"){valid=true;}
                }
                
                DestroyMonster(index);
            }
        }
    }

   void DestroyMonster(int indexonfield){

    monsterzone[indexonfield]=Monster();
   } 






};

class EquipSpell : public Spell{

int Change;
int linkedindex;
bool Effectsenemy;  

public:

    EquipSpell(int change, bool enemy){

        setchange(change);
        settarget(enemy);
    }

    EquipSpell(){
        setname("DEFAULT");
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


    void equip(int monsterindex){

        if(Owner->hasmonsterat(monsterindex)){
            Owner->getmonsterat(monsterindex)->changeattack(Change);
            linkedindex=monsterindex;
        }


    }

    ~EquipSpell(){
        Owner->getmonsterat(linkedindex)->changeattack(-Change);
    }


};



Monster* generateMonster(Player* owner);
/*
void equip(int monsterindex, Player* target, Spell* equipspell){

     if(target->hasmonsterat(monsterindex)){
        target->getmonsterat(monsterindex)->changeattack(equipspell->getchange());

     }
}
*/

 void normalizehand(Player* owner,int index){
        int i=index;
        while (i<5)
        {
              if(owner->hand[i+1]->getname()!="Default"){
        //    std::cout<<array[i+1]->getname()<<"is name of next"<<std::endl;

                if(dynamic_cast<Monster*>(owner->hand[i+1])!= nullptr){
                
                delete owner->hand[i];
                owner->hand[i]=new Monster();
                dynamic_cast<Monster*>(owner->hand[i])->copyMonster(dynamic_cast<Monster*>(owner->hand[i+1]));
                }

                if(dynamic_cast<EquipSpell*>(owner->hand[i+1])!=nullptr){
                delete owner->hand[i];
                owner->hand[i]=new EquipSpell();
                dynamic_cast<EquipSpell*>(owner->hand[i])->copyspell(dynamic_cast<Spell*>(owner->hand[i+1]));
                }


               delete owner->hand[i+1];
               owner->hand[i+1]=new Card();
               i++;
}

        }


}


int main() {

      
   
    std::string name;

    std::cout<<"Name of first player"<<std::endl;
    std::cin>>name; 
    Player player1(name);
    std::cout<<"Name of second player"<<std::endl;
    std::cin>>name; 
    Player player2(name);

    player1.setenemy(&player2);
    player2.setenemy(&player1);

    std::cout<<player1.getname()<<" versus " <<player2.getname()<<std::endl;
    


    Monster a("Blue eyes white dragon",3000,2000,6,&player1);
    player1.Draw(&a);
    /*
    Monster *monsterptr = generateMonster();
    player1.Draw(monsterptr);
    free(monsterptr);
    std::cout<<monsterptr<<std::endl;

    monsterptr = generateMonster();
    player1.Draw(monsterptr);
     free(monsterptr);
    std::cout<<monsterptr<<std::endl;

    monsterptr = generateMonster();
    player1.Draw(monsterptr);
   // free(monsterptr);
std::cout<<monsterptr<<std::endl;
*/
    srand (time(NULL));
    player1.Draw(generateMonster(&player1));
    srand (time(NULL)*22);
    player1.Draw(generateMonster(&player1));
    srand (time(NULL)+5381);
    player1.Draw(generateMonster(&player1));
    Spell swordandshield("Sword and shield");
    swordandshield.setchange(800);
    player1.Draw(&swordandshield);

    int index=0;
    std::cout<<"Summon a monster? "<<std::endl;
    std::cin>>index;
    player1.Play(index);

    

    
    player1.displayhand();
    player1.displayboard();

     std::cout<<"Summon a monster? "<<std::endl;
    std::cin>>index;
    player1.Play(index);

     player1.displayhand();
    player1.displayboard();
    

   // delete monsterptr;
   // free(monsterptr);
   

    return 0;
}

 Monster* generateMonster(Player *owner){

  

    int Atk = (rand()%20)*100;
    int Def = (rand()%20)*100;

    //void* buffer = malloc(sizeof(Monster));
    //new (buffer)
    Monster* monster = new  Monster("Mysterious monster", Atk,Def, 4,owner);



  //  monster->~Monster();
    return monster;

}