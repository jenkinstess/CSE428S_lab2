// PinochleGame.cpp
// Sam Saxon s.saxon@wustl.edu
// Tess Jenkins jenkinstess@wustl.edu
// Contains the definition for the constructor, the deal method, the play method, the collect all method, and the method printing out the players.

#include "PinochleGame.h"
#include <bits/stdc++.h>
#include <vector>
#include <iostream>
#define SUCCESS 0
#define SIZESET 100
#define ACE 5
#define KING 3
#define QUEEN 2
#define JACK 1

const int PinochleGame::meld_values[] = {10, 20, 40, 40, 40, 60, 80, 100, 150, 300, 400, 600, 800, 1000, 1500};


// PinochleGame constructor. Pushes all the current players passed in via the command line onto the memeber variable that 
//  is a vector containing the hands of all the current players
PinochleGame::PinochleGame(int argc, const char* argv[]) : Game(argc, argv) {
    for(int i = 0; i < argc-2; ++i){
        CardSet<PinochleRank, Suits> cs;
        _curHand.push_back(cs);
    }
}

// Cards are dealt out 3 at a time to each player, repeats until the deck is empty
void PinochleGame::deal() {

    typename std::vector< CardSet<PinochleRank, Suits> >::iterator it;

    while (!_pDeck.is_empty()) {
        for (it = _curHand.begin(); it < _curHand.end(); it++) {
            try{
                _pDeck >> (*it);
                _pDeck >> (*it);
                _pDeck >> (*it);
            }
            catch (std::runtime_error &e){
                std::cout << "Runtime error: " << e.what();
            }
        }
    }
    
}

int PinochleGame::play() {
    
    _pDeck.shuffle();
    deal();

    //print player names and their cards
    print_players();

    //print different melds available for the different players
    //print_evaluation();

    //collect cards from players
    collect_all();

    std::string input;
    std::cout << "end game? " << std::endl;
    std::cin >> input;
    
    if (input == "yes") {
        return SUCCESS;
    }

    return play();
}

void PinochleGame::print_players() {
    typename std::vector< CardSet<PinochleRank, Suits> >::iterator it = _curHand.begin();
    std::vector<std::string>::iterator p = Game::players.begin();
    
    while (it < _curHand.end()) {
        std::cout << (*p) << std::endl;
        (*it).print(std::cout, SIZESET);

        std::vector<PinochleMelds> listMoves;
        suit_independent_evaluation(*it, listMoves);

        typename std::vector< PinochleMelds >::iterator pm;
        for (pm = listMoves.begin(); pm < listMoves.end(); pm++) {
            std::cout << (*pm) << " : " << meld_values[int(*pm)] << std:: endl; 
        }
        std::cout << std::endl;

        p++;
        it++;
    }
}

void PinochleGame::collect_all() {
    typename std::vector< CardSet<PinochleRank, Suits> >::iterator it;
    for (it = _curHand.begin(); it < _curHand.end(); it++) {
        _pDeck.collect(*it);
    }
}

std::ostream& operator<<(std::ostream& os, const PinochleMelds& pinmelds) {
   
    switch(pinmelds){

        case PinochleMelds::dix:
            os << "dix " ; //<< PinochleMelds::dix;
            break;

        case PinochleMelds::offsuitmarriage:
            os << "offsuitmarriage "; // << PinochleMelds::offsuitmarriage;
            break;

        case PinochleMelds::fortyjacks:
            os << "fortyjacks " ; //<< PinochleMelds::fortyjacks;
            break;

        case PinochleMelds::pinochle:
            os << "pinochle " ; //<< PinochleMelds::pinochle;
            break;

        case PinochleMelds::insuitmarriage:
            os << "insuitmarriage "; 
            break;

        case PinochleMelds::sixtyqueens:
            os << "sixtyqueens "; 
            break;

        case PinochleMelds::eightykings:
            os << "eightykings "; 
            break;

        case PinochleMelds::hundredaces:
            os << "hundredaces "; 
            break;

        case PinochleMelds::insuitrun:
            os << "insuitrun " ; 
            break;

        case PinochleMelds::doublepinochle:
            os << "doublepinochle "; 
            break;

        case PinochleMelds::fourhundredjacks:
            os << "fourhundredjacks "; 
            break;

        case PinochleMelds::sixhundredqueens:
            os << "sixhundredqueens " ; 
            break;

        case PinochleMelds::eighthundredkings:
            os << "eighthundredkings "; 
            break;

        case PinochleMelds::thousandaces:
            os << "thousandaces " ; 
            break;

        case PinochleMelds::insuitdoublerun:
            os << "insuitdoublerun "; 
            break;

        default:
            os << "?";
            break;

    }

    return os;
}

// evaluates the passed hand to determine which possible melds can be derived from the given players hand.
void PinochleGame::suit_independent_evaluation(const CardSet<PinochleRank, Suits>& hand, std::vector<PinochleMelds>& combList) {
    CardSet<PinochleRank, Suits> locHand(hand);

    int numAce = 0;
    std::vector<Suits> aceSuits;
    int numKing = 0;
    std::vector<Suits> kingSuits;
    int numQueen = 0;
    std::vector<Suits> queenSuits;
    int numJack = 0;
    std::vector<Suits> jackSuits;

    std::vector< Card <PinochleRank, Suits> > t_cards = locHand.*(locHand.get_cards());

    std::vector< Card<PinochleRank, Suits> >::iterator it;
    for (it = t_cards.begin(); it < t_cards.end(); it++) {
        if ((*it).rank == PinochleRank(5)) { // 5 = ace
            ++numAce;
            aceSuits.push_back((*it).suit);
        }
        else if ((*it).rank == PinochleRank(3)) { // 3 = king
            ++numKing;
            kingSuits.push_back((*it).suit);
        }
        else if ((*it).rank == PinochleRank(2)) { // 2 = queen
            ++numQueen;
            queenSuits.push_back((*it).suit);
        }
        else if ((*it).rank == PinochleRank(1)) { // 1 = jack
            ++numJack;
            jackSuits.push_back((*it).suit);
        }
    }

    if (numAce == 8) {
        combList.push_back(PinochleMelds(13)); // 13 = thousandaces
    }
    else if (numAce >= 4) {
        //testing if the suit is found in the vector of suits. if all are found then the combincation is added
        if (std::find(aceSuits.begin(), aceSuits.end(), Suits(0)) != aceSuits.end()) { // Suits(0) = clubs
            if (std::find(aceSuits.begin(), aceSuits.end(), Suits(1)) != aceSuits.end()) { // Suits(1) = diamonds
                if (std::find(aceSuits.begin(), aceSuits.end(), Suits(2)) != aceSuits.end()) { // Suits(2) = hearts
                    if (std::find(aceSuits.begin(), aceSuits.end(), Suits(3)) != aceSuits.end()) { // Suits(3) = spades
                        combList.push_back(PinochleMelds(7));
                    }
                }
            }
        }
    }

    if (numKing == 8) {
        combList.push_back(PinochleMelds(12));
    }  
    else if (numKing >= 4) {
        //testing if the suit is found in the vector of suits. if all are found then the combincation is added
        if (std::find(kingSuits.begin(), kingSuits.end(), Suits(0)) != kingSuits.end()) { // Suits(0) = clubs
            if (std::find(kingSuits.begin(), kingSuits.end(), Suits(1)) != kingSuits.end()) { // Suits(1) = diamonds
                if (std::find(kingSuits.begin(), kingSuits.end(), Suits(2)) != kingSuits.end()) { // Suits(2) = hearts
                    if (std::find(kingSuits.begin(), kingSuits.end(), Suits(3)) != kingSuits.end()) { // Suits(3) = spades
                        combList.push_back(PinochleMelds(6));
                    }
                }
            }
        }
    }
    
    if (numQueen == 8) {
        combList.push_back(PinochleMelds(11));
    }
    else if (numQueen >= 4) {
        if (std::find(queenSuits.begin(), queenSuits.end(), Suits(0)) != queenSuits.end()) { // Suits(0) = clubs
            if (std::find(queenSuits.begin(), queenSuits.end(), Suits(1)) != queenSuits.end()) { // Suits(1) = diamonds
                if (std::find(queenSuits.begin(), queenSuits.end(), Suits(2)) != queenSuits.end()) { // Suits(2) = hearts
                    if (std::find(queenSuits.begin(), queenSuits.end(), Suits(3)) != queenSuits.end()) { // Suits(3) = spades
                        combList.push_back(PinochleMelds(5));
                    }
                }
            }
        }
    }

    if (numJack == 8) {
        combList.push_back(PinochleMelds(10));
    }
    else if (numJack >= 4) {
        if (std::find(jackSuits.begin(), jackSuits.end(), Suits(0)) != jackSuits.end()) { // Suits(0) = clubs
            if (std::find(jackSuits.begin(), jackSuits.end(), Suits(1)) != jackSuits.end()) { // Suits(1) = diamonds
                if (std::find(jackSuits.begin(), jackSuits.end(), Suits(2)) != jackSuits.end()) { // Suits(2) = hearts
                    if (std::find(jackSuits.begin(), jackSuits.end(), Suits(3)) != jackSuits.end()) { // Suits(3) = spades
                        combList.push_back(PinochleMelds(2));
                    }
                }
            }
        }
    }

    if (numJack >= 2 && numQueen >= 2){
        if((std::count(jackSuits.begin(), jackSuits.end(), Suits(1)) == 2)
            && (std::count(queenSuits.begin(), queenSuits.end(), Suits(3)) == 2)) {
                combList.push_back(PinochleMelds(9));
            }
    }
    else if (numJack >= 1 && numQueen >= 1){
        if (std::find(jackSuits.begin(), jackSuits.end(), Suits(1)) != jackSuits.end()) {
            if (std::find(queenSuits.begin(), queenSuits.end(), Suits(3)) != queenSuits.end()) {
                combList.push_back(PinochleMelds(3));
            }
        }
    }
}
