// PinochleDeck.cpp
// Sam Saxon s.saxon@wustl.edu
// Tess Jenkins jenkinstess@wustl.edu
// Contains shift and increment operator definitions, the constructor for pinochle.

#include "PinochleDeck.h"
#define NUM_COPIES 2

std::ostream& operator<<(std::ostream& os, const PinochleRank& pinRank){

    switch(pinRank){

        case PinochleRank::nine:
            os << "9";
            break;

        case PinochleRank::jack:
            os << "J";
            break;

        case PinochleRank::queen:
            os << "Q";
            break;
        
        case PinochleRank::king:
            os << "K";
            break;

        case PinochleRank::ten:
            os << "10";
            break;
        
        case PinochleRank::ace:
            os << "A";
            break;

        default:
            os << "?";
            break;

    }

    return os;
}

PinochleRank operator++(PinochleRank& _rank, int){

    switch(_rank){

        case PinochleRank::nine:
            _rank = PinochleRank::jack;
            break;

        case PinochleRank::jack:
            _rank = PinochleRank::queen;
            break;

        case PinochleRank::queen:
            _rank = PinochleRank::king;
            break;
        
        case PinochleRank::king:
            _rank = PinochleRank::ten;
            break;

        case PinochleRank::ten:
            _rank = PinochleRank::ace;
            break;
        
        case PinochleRank::ace:
            _rank = PinochleRank::undefined;
            break;

        default:
            break;

    }

    return _rank;
}

// Ensures the correct number of and rank cards are properly added to the deck 
PinochleDeck::PinochleDeck() {
    std::vector< Card<PinochleRank, Suits> > temp;

    //create 2 copies of each card
    for (int i = 0; i < NUM_COPIES; ++i) {

        Suits curSuit = Suits::clubs;

        while (curSuit != Suits::undefined) {
        
            PinochleRank curRank = PinochleRank::nine;

            while (curRank != PinochleRank::undefined) {
                temp.push_back( Card<PinochleRank, Suits>(curRank, curSuit) );
                curRank++;
            }

            curSuit++;

        }

    }

    cards = temp;
}
