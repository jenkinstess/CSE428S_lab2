// HoldEmDeck.cpp
// Sam Saxon s.saxon@wustl.edu
// Tess Jenkins jenkinstess@wustl.edu
// Contains shift and increment operator definitions, and the constructor for the poker deck.

#include "HoldEmDeck.h"
#define PRINT 13 

std::ostream& operator<<(std::ostream& os, const HoldEmRank& _rank){

    switch(_rank){

        case HoldEmRank::two:
            os << "2";
            break;

        case HoldEmRank::three:
            os << "3";
            break;

        case HoldEmRank::four:
            os << "4";
            break;

        case HoldEmRank::five:
            os << "5";
            break;

        case HoldEmRank::six:
            os << "6";
            break;

        case HoldEmRank::seven:
            os << "7";
            break;

        case HoldEmRank::eight:
            os << "8";
            break;

        case HoldEmRank::nine:
            os << "9";
            break;

        case HoldEmRank::ten:
            os << "10";
            break;

        case HoldEmRank::jack:
            os << "J";
            break;

        case HoldEmRank::queen:
            os << "Q";
            break;

        case HoldEmRank::king:
            os << "K";
            break;

        case HoldEmRank::ace:
            os << "A";
            break;

        default:
            os << "?";
            break;

    }

    return os;
}

HoldEmRank operator++(HoldEmRank& _rank, int){

    switch(_rank){

        case HoldEmRank::two:
            _rank = HoldEmRank::three;
            break;

        case HoldEmRank::three:
            _rank = HoldEmRank::four;
            break;

        case HoldEmRank::four:
            _rank = HoldEmRank::five;
            break;

        case HoldEmRank::five:
            _rank = HoldEmRank::six;
            break;

        case HoldEmRank::six:
            _rank = HoldEmRank::seven;
            break;

        case HoldEmRank::seven:
            _rank = HoldEmRank::eight;
            break;

        case HoldEmRank::eight:
            _rank = HoldEmRank::nine;
            break;

        case HoldEmRank::nine:
            _rank = HoldEmRank::ten;
            break;

        case HoldEmRank::ten:
            _rank = HoldEmRank::jack;
            break;

        case HoldEmRank::jack:
            _rank = HoldEmRank::queen;
            break;

        case HoldEmRank::queen:
            _rank = HoldEmRank::king;
            break;

        case HoldEmRank::king:
            _rank = HoldEmRank::ace;
            break;

        case HoldEmRank::ace:
            _rank = HoldEmRank::undefined;
            break;

        default:
            break;

    }

    return _rank;
}

// Ensures the correct number of and rank cards are properly added to the deck
HoldEmDeck::HoldEmDeck() {
    std::vector< Card<HoldEmRank, Suits> > temp;

    Suits curSuit = Suits::clubs;

    while (curSuit != Suits::undefined) {
	
        HoldEmRank curRank = HoldEmRank::two;
        while (curRank != HoldEmRank::undefined) {
            temp.push_back( Card<HoldEmRank, Suits>(curRank, curSuit));
            curRank++;
        }
        
        curSuit++;
    } 

    cards = temp;
}
