#ifndef CARD_HPP
#define CARD_HPP
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;
namespace ariel
{
   class Card
  {                     
   
                
    public: 
         enum Suit { Hearts=0, Diamonds, Clubs, Spades };
         enum Rank { Two=2, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King, Ace };
        
            
            
            Card();
           
            Card(Suit suit, Rank rank) : suit(suit), rank(rank) {}  
            
            int getRank() const {
               return rank;
             }
    
            Suit getSuit() const {
               return suit;
             }
            
     
        friend ostream& operator<<(ostream& oss, const Card& card) {
                switch (card.rank)
                {
                case Ace:
                        oss << "Ace ";
                        break;

                case Two:
                        oss << "Two ";
                        break;
        
                case Three:
                        oss << "Three ";
                        break;  

                case Four:
                        oss << "Four ";
                        break;

                case Five:
                        oss << "Five ";
                        break;
        
                case Six:
                        oss << "Six ";
                        break;

                case Seven:
                        oss << "Seven ";
                        break;

                case Eight:
                        oss << "Eight ";
                        break;
        
                case Nine:
                        oss << "Nine ";
                        break;  
                case Ten:
                        oss << "Ten ";
                        break;

                case Jack:
                        oss << "Jack ";
                        break;  
                case Queen:
                        oss << "Queen ";
                        break;  
                case King:
                        oss << "King ";
                        break;                  
                default:
                        break;
                }
                oss<< "of";
                switch (card.suit) {
                case Hearts:
                        oss << " Hearts";
                        break;
                case Diamonds:
                        oss << " Diamonds";
                        break;
                case Clubs:
                        oss << " Clubs";
                        break;
                case Spades:
                        oss << " Spades";
                        break;
                }
                
                return oss;
        }  

       static string toString(const Card& card){
                string str = std::string();
                switch (card.rank)
                {
                case Ace:
                        str+= " Ace ";
                        break;

                case Two:
                        str+= " Two ";
                        break;
        
                case Three:
                        str+= " Three ";
                        break;  

                case Four:
                        str+= " Four ";
                        break;

                case Five:
                        str+= " Five ";
                        break;
        
                case Six:
                        str+= " Six ";
                        break;

                case Seven:
                        str+= " Seven ";
                        break;

                case Eight:
                        str+= " Eight ";
                        break;
        
                case Nine:
                        str+= " Nine ";
                        break;  
                case Ten:
                        str+= " Ten ";
                        break;

                case Jack:
                        str+= " Jack ";
                        break;  
                case Queen:
                        str+= " Queen ";
                        break;  
                case King:
                        str+= " King ";
                        break;                  
                default:
                        break;
                }
                str+= " of ";
                switch (card.suit) {
                case Hearts:
                        str+= " Hearts ";
                        break;
                case Diamonds:
                        str+= " Diamonds ";
                        break;
                case Clubs:
                        str+= " Clubs ";
                        break;
                case Spades:
                        str+= " Spades ";
                        break;
                }
                return str;

        } 
        private:
           
    Rank rank;
    Suit suit;
    string str;      
   };
}

#endif

