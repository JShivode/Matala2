#include "player.hpp"
#include "game.hpp"
//#include "Card.cpp"
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <sstream> //for std::stringstream 

 using namespace ariel;
        

        
        Game::Game(Player& p1_, Player& p2_)
        {
            p1 = &p1_;
            p2 = &p2_;            
            war_cards_size =0;                    
            winner = 0;
            turns=0;
            std::string log;
            for (int suit = Card::Hearts; suit <= Card::Spades; ++suit) 
            for (int rank = Card::Two; rank <= Card::Ace; ++rank) 
                g_cards.push_back(Card(static_cast<Card::Suit>(suit), static_cast<Card::Rank>(rank)));
                                          
            dealCards();                                    
        
            cout<<" Dealt Card Deck."<<p1->getName()<<") stacksize("<<p1->stacksize()<<")"<<endl;    
        }
        

        void Game::printLastTurn(){
           cout<< lastTurnStats<<endl;
        }

        

        void Game::printWiner(){
            if(p1->cardesTaken() == p2->cardesTaken() && p1->stacksize() == 0 )
               throw std::invalid_argument("Two players looted the same amount of cards.");
            if(winner == 0)
               cout<<"No winner yet!"<<endl;
            else if(winner == 1)
                 cout<<" Player "<<p1->getName()<<" wins";
            else if (winner ==2)
                 cout<<" Player "<<p2->getName()<<" wins";
                 else throw std::invalid_argument(" Game finished at a tie! ");
        }

       void Game::printLog(){
          cout<<LOG;
        }

       void Game::printStats(){
             cout<<"Player1 "<<p1->getName()<<" cards:"<<p1->stacksize()<<" loots:"<<p1->cardesTaken()<<endl;
             cout<<"Player2 "<<p2->getName()<<" cards:"<<p2->stacksize()<<" loots:"<<p2->cardesTaken()<<endl;
             cout<<"Last turn: "<<endl;
             printLastTurn();
        }

       void Game::printCards(){
           for(int i=0;i<g_cards.size();i++)
               cout<<" #"<<i<<"["<<g_cards[static_cast<std::deque<int>::size_type>(i)]<<"] ";
           cout<<endl;
       }
        void Game::shuffleCards() {
        int seed = chrono::system_clock::now().time_since_epoch().count();
        //int seed = std::default_random_engine {};std::linear_congruential_engine<unsigned int, 48271, 0, 2147483647>::result_type`
        shuffle(g_cards.begin(), g_cards.end(), default_random_engine(static_cast<std::linear_congruential_engine<unsigned int, 48271, 0, 2147483647>::result_type>(seed)));
        //std::random_shuffle(g_cards.begin(), g_cards.end());
        }

        Card Game::dealCard() {
        Card card = Card(g_cards.back());
        g_cards.pop_back();
        return card;
       }

       void Game::dealCards(){
           shuffleCards();   // shuffle card stack.
           for(int i=0; i<26; i++){  //slpit stack between the two players evenly.               
               p1->addCardToStack(Card(dealCard()));
               p2->addCardToStack(Card(dealCard()));               
           }
           cout<<"dealCards: Player1("<<p1->getName()<<") stacksize("<<p1->stacksize()<<")"<<endl;
       }

        void Game::playAll(){            
                    if(winner !=0 || p1->stacksize() == 0 || p2->stacksize() == 0)
                      return;                      
                    while (winner == 0)
                    {             
                        if(turns > 26)
                          throw std::invalid_argument("Can't play more than 26 turns!");
                        if(winner!=0)
                          throw std::invalid_argument("Game already concluded!");
             
                        playTurn();                        
                        printLastTurn();
                        //cout<< endl<<" Player1 cards "<<p1->stacksize()<< " Player2 cards: "<<p2->stacksize()<<endl;
                        if(winner != 0)
                           break;
                    }  
                    playedAll = true; 
                             
        }
       void Game::playTurn(){
        std::stringstream ss;
        ss<<"Turn #"<<turns<<" stats:1 "<<p1->getName()<<" cards "<<p1->stacksize()<<" and loots "<<p1->cardesTaken()<<endl;        
        LOG += ss.str();
        ss<<"Turn #"<<turns<<" stats:2 "<<p2->getName()<<" cards "<<p2->stacksize()<<" and loots "<<p2->cardesTaken()<<endl;           
        LOG += ss.str();
        ss<<"War Cards on Deck = "<<getWarCardsSize()<<endl;  
        LOG += ss.str();
         
        //temp
        cout <<"Turn #"<<turns<<" stats:1 "<<p1->getName()<<" cards "<<p1->stacksize()<<" and loots "<<p1->cardesTaken()<<endl;        
        cout <<"Turn #"<<turns<<" stats:2 "<<p2->getName()<<" cards "<<p2->stacksize()<<" and loots "<<p2->cardesTaken()<<endl;           
        cout <<"War Cards on Deck = "<<getWarCardsSize()<<endl; 
        printLastTurn(); 
        //
        
           if(playedAll)
           {
              if(winner == 0)
                winner =3;
              throw std::invalid_argument("Game already concluded!");              
           }
           if(winner != 0 )
           {
              cout<<"We have a winner, you can't play more!"<<endl;
              return;
           }
           if(p1 == p2)
              throw std::invalid_argument("Can't play with only one player!");                       

           if(p1->stacksize() == 0 )  //if player1 has no cards left, then player2 has non left as well.
             {
                 if(p2->cardesTaken()>p1->cardesTaken()){
                 winner = 2;                 
                 }else if(p1->cardesTaken()>p2->cardesTaken()){
                 winner =1;
                 }else{
                    winner = 3;
                 }
                
                 return;                
             }                  

           turns++;   //At this point number of turns played will be incremented.
           lastTurnStats = " " + p1->getName() + " played " +  p1->firstCard().toString(p1->firstCard()) + " and " + p2->getName()+ " played " + p2->firstCard().toString(p2->firstCard()) + ", ";
           if(p1->firstCard().getRank() > p2->firstCard().getRank()){
              if(getWarCardsSize() == 0){
              p1->lootCard(p2);
              p1->lootCard(p1);              
              }else {
              for(int i=0;i<getWarCardsSize();i++){
                        Card temp = war_cards.back();
                        war_cards.pop_back();
                        p1->lootCard(temp);
                    }
                war_cards_size =0;
                }
                lastTurnStats += p1->getName()+" won. ";
              }
           else if(p1->firstCard().getRank() < p2->firstCard().getRank()){
              if(war_cards_size == 0){
              p2->lootCard(p1);
              p2->lootCard(p2);              
              }else {
              for(int i=0;i<war_cards_size;i++){
                        Card temp = war_cards.back();
                        war_cards.pop_back();
                        p2->lootCard(temp);
                    }
                war_cards_size =0;
                }
                lastTurnStats += p2->getName()+" won. ";
              }
           else {
               lastTurnStats += "Draw! ";
               gotoWar();               
           }
       }

       void Game::gotoWar(){                      
              // if both players have less than 4 cards
             if(p1->stacksize()<4 && p2->stacksize()<4 ){
              //turns++;

               //when cards are nearly finished, players split loots:
               for(int i=0; i < p1->stacksize()/2; i++)
                  {
                    p1->lootCard(p2->looseCard());
                    p2->lootCard(p1->looseCard());
                  }
                for(int i=0; i<war_cards_size/2; i++)
                  {
                    Card temp = war_cards.back();
                        war_cards.pop_back();
                        p1->lootCard(temp);
                    temp = war_cards.back();
                        war_cards.pop_back();
                        p2->lootCard(temp);
                  }
                  war_cards_size = 0;     
                  if(p1->cardesTaken() > p2->cardesTaken())
                    winner = 1;
                  else if(p2->cardesTaken() > p1->cardesTaken())           
                    winner = 2;
                  else
                    winner = 3;
                return;
             }// if both players' cards less than 4. loots are split!


           if(p1->stacksize() != 0)//if these are not the last 4 cards.
           {
                for(int i=0;i<4;i++){ //pull 4 cards off each player to deck.
                war_cards.push_back(p1->looseCard());
                war_cards.push_back(p2->looseCard());                     
                }
                war_cards_size+=8; 
           } 
           else
           {
            turns++;
            if(p1->firstCard().getRank() > p2->firstCard().getRank())
            {
              for(int i=0;i<4;i++){ //pull 4 cards off each player to deck.
                p1->lootCard(p1->looseCard());
                p1->lootCard(p2->looseCard()); 
                winner = 1;               
                }
            }else if(p1->firstCard().getRank() < p2->firstCard().getRank()) {
              for(int i=0;i<4;i++){ //pull 4 cards off each player to deck.
                p2->lootCard(p1->looseCard());
                p2->lootCard(p2->looseCard());   
                winner = 2;             
                }
            }else{//split loots
                 for(int i=0; i<p1->stacksize(); i++)
                  {
                    p1->lootCard(p2->looseCard());
                    p2->lootCard(p1->looseCard());
                  }
                  if(p1->cardesTaken() > p2->cardesTaken())
                    winner = 1;
                  else if(p2->cardesTaken() > p1->cardesTaken())           
                    winner = 2;
                  else
                    winner = 3; 
            }
           }
           //Game::playTurn();
       }



