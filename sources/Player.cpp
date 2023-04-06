#include "player.hpp"
#include "game.hpp"
#include "card.hpp"
#include <string>
#include <sstream> //for std::stringstream 
#include <algorithm>
#include <random>
#include <chrono>


using namespace std;
using namespace ariel;

        
        
        Player::Player(const string& name) : name(name) {  //constructor that takes name constant.
             
         }   
        
        /*Player::Player(Player& player)       //copy constructor
            {
               name = player.name;
               cards_won = player.cards_won;
               card_stack = player.card_stack;
              
            }  */
          
        int Player::stacksize(){
           return card_stack.size();//num_card_stack;
        }

        int Player::cardesTaken(){
           return cards_won.size();
        }
        void Player::addCardToStack(Card card) {                        
            card_stack.push_front(Card(card)); // add the card to the front of the stack.
            cout<<" added "<<card_stack.front()<<" size now "<<card_stack.size()<<"="<<card_stack.size();
       }

       void Player::lootCard(Player* otherPlayer){
            if(otherPlayer == this){
               cards_won.push_back(looseCard());
            }else
               cards_won.push_back(otherPlayer->looseCard());                        
       }
       void Player::lootCard(const Card &card){
            cards_won.push_back(card);        
       }
       const Card Player::looseCard(){            
            Card card = Card(card_stack[0]);
            card_stack.pop_front();            
            return card;
       }
       void Player::reuseLoots(){
            if(stacksize() == 0)
               for(int i=0; i< cardesTaken(); i++)
               {
                  Card temp = cards_won[static_cast<std::vector<int>::size_type>(cardesTaken()-1)];  
                  cards_won.pop_back();
                  card_stack.push_back(Card(temp));
               }
               if(stacksize()>2)  //shuffle the stack if it's size is three or more.
               {
               int seed = chrono::system_clock::now().time_since_epoch().count();        
               shuffle(card_stack.begin(), card_stack.end(), default_random_engine(static_cast<std::linear_congruential_engine<unsigned int, 48271, 0, 2147483647>::result_type>(seed)));
               }
       }
       void Player::printCards(){
            for(int i=0;i< card_stack.size();i++)
                cout<<" ["<<card_stack[static_cast<std::vector<int>::size_type>(i)]<<"] ";               
            cout<<endl;       
      }
       


