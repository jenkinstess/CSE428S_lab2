// PinochleGame.h
// Sam Saxon s.saxon@wustl.edu
// Tess Jenkins jenkinstess@wustl.edu
// Contains public delcarations for the virtual play function as well as the constructor for the class. Has protected declarations
//  for a member variable of the pinochle deck, a vector of the current hands, the virtual function deal, the function that prints
//  the players, and the collect all function. 

#pragma once
#include "PinochleDeck.h"
#include "CardSet_T.h"
#include "Game.h"

class PinochleGame : public Game{
    public:
        PinochleGame(int argc, const char* argv[]);
        virtual int play();
    protected:
        PinochleDeck _pDeck; 
        virtual void deal();
        std::vector< CardSet<PinochleRank, Suits> > _curHand;
        void print_players();
        void collect_all();
};