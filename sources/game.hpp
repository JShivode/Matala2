#ifndef GAME_HPP
#define GAME_HPP
#include "player.hpp"
#include "card.hpp"
#include <vector>
namespace ariel{
class Game
{
   private: Player* p1;
            Player* p2;
            string lastTurnStats;
            string LOG;
            vector<Card> g_cards;        
            vector <Card> war_cards;
            int winner;
            bool playedAll = false;
            int turns;
            int war_cards_size;

            
    
 public: 
         Game(Player& p1_, Player& p2_);

        
         
  void printLastTurn();// print the last turn stats. For example:
                                                    // Alice played Queen of Hearts Bob played 5 of Spades. Alice wins.
                                                    // Alice played 6 of Hearts Bob played 6 of Spades. Draw. Alice played 10 of Clubs Bob played 10 of Diamonds. draw. Alice played Jack of Clubs Bob played King of Diamonds. Bob wins.
   //int stacksize(); //prints the amount of cards left. should be 21 but can be less if a draw was played
   //int cardesTaken(); // prints the amount of cards this player has won. 
   void playAll(); //playes the game untill the end
   void printWiner(); // prints the name of the winning player
   void printLog(); // prints all the turns played one line per turn (same format as game.printLastTurn())
   void printStats();
   void shuffleCards();
   Card dealCard();
   void dealCards();
   void playTurn();
   void gotoWar();
   int getWarCardsSize() const{return war_cards_size;}
   void setWarCardsSize(int war){war_cards_size = war;}
   int getTurns() const{return turns;}
   void setTurns(int turn){turns =turn;}
   Player* getP1(){return p1;}
   Player* getP2(){return p2;}
   
   void printCards();

};
}

#endif




