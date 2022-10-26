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

enum class PinochleMelds{
    dix, offsuitmarriage, fortyjacks, pinochle,
    insuitmarriage, sixtyqueens, eightykings, 
    hundredaces, insuitrun, doublepinochle,
    fourhundredjacks, sixhundredqueens, 
    eighthundredkings, thousandaces, insuitdoublerun
};

const int meld_values[] = {10, 20, 40, 40, 40, 60, 80, 100, 150, 300, 400, 600, 800, 1000, 1500};

std::ostream& operator<<(std::ostream& os, const PinochleMelds&);

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

    private:
        void suit_independent_evaluation(const CardSet<PinochleRank, Suits>&, std::vector<PinochleMelds>);
};