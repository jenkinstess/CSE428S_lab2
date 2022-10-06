// HoldEmGame.h
// Sam Saxon s.saxon@wustl.edu
// Tess Jenkins jenkinstess@wustl.edu
// Contains public delcarations for the virtual play function as well as the constructor for the class. Has protected declarations
//  for a member variable of the holdem deck, of the holdem state, a cardset object representing the poker board, a vector of the current hands, 
//  the virtual function deal, the function that prints the players, and the collect all function. Also contains the enumeration for 
//  the states of Texas hold em.

#pragma once
#include "HoldEmDeck.h"
#include "Game.h"

enum class HoldEmState{
    preflop, flop, turn, river, undefined
};

class HoldEmGame : public Game {

    public:
        HoldEmGame(int argc, const char* argv[]);
        virtual int play();
    protected:
        HoldEmDeck deck; 
        HoldEmState state;
        virtual void deal();
        std::vector< CardSet<HoldEmRank, Suits> > hands;
        CardSet<HoldEmRank, Suits> board;
        void print_players();
        void collect_all();

};