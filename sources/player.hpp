#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <string>
#include <deque>
#include "card.hpp"
#include <sstream> 
//#include "Card.cpp"
using namespace std;
namespace ariel
{
    class Player
    {
        string name;
        
        vector <Card> cards_won;   //player's loots.
        deque <Card> card_stack;   //player's playing cards.    
        
        public:         
        
        Player(const string& name);

        //Player(Player &player) ;      //copy constructor
        //~Player(){
        
        //}
      
        Player(){}

        const string& getName() const {
        return name;
        }
        int stacksize();  //returns number of playing cards.
        int cardesTaken(); //returns number of looted(won) cards.
        void lootCard(Player* otherPlayer); //adds a card to the stack of won cards.
        void lootCard(const Card &card); //add card to loots.
        const Card looseCard();     //loose a card by popping it off the playing cards stack.
        void addCardToStack(Card card); // add a card to the playing stack.
        Card firstCard(){   //return the first card in the playing stack.
            return card_stack.front();
        }
        void printCards();   //print player's playing cards.
        void reuseLoots();   //dump all cards from player's loots to his playing cards' stack for reuse.
        
    };            
} // namespace ariel

#endif
