// Suit.cpp
// Sam Saxon s.saxon@wustl.edu
// Tess Jenkins jenkinstess@wustl.edu
// Contains shift and increment operator definitions


#include "Suit.h"

std::ostream& operator<<(std::ostream& os, const Suits& suit){

    switch(suit){

        case Suits::clubs:
            os << "C";
            break;

        case Suits::diamonds:
            os << "D";
            break;

        case Suits::hearts:
            os << "H";
            break;
        
        case Suits::spades:
            os << "S";
            break;

        default:
            os << "?";
            break;

    }

    return os;
}

Suits operator++(Suits& _suit, int){

    switch(_suit){

        case Suits::clubs:
            _suit = Suits::diamonds;
            break;

        case Suits::diamonds:
            _suit = Suits::hearts;
            break;

        case Suits::hearts:
            _suit = Suits::spades;
            break;
        
        case Suits::spades:
            _suit = Suits::undefined;
            break;

        default:
            break;

    }

    return _suit;
}
