// PinochleGame.cpp
// Sam Saxon s.saxon@wustl.edu
// Tess Jenkins jenkinstess@wustl.edu
// Contains the definition for the constructor, the deal method, the play method, the collect all method, the suit independent evaluation method, 
//   and the method for printing out the players, their hands, and the evaluation of their hands. Overloads the left shift
//   operator to print out an appropriate string for the name of the label and the point values associated with the label. 

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
#define CLUBS 0
#define DIAMOND 1
#define HEART 2
#define SPADE 3
#define ALLPRESENT 8
#define FOURPRESENT 4
#define TWOPRESENT 2
#define ONEPRESENT 1
#define THOUSANDACES 13
#define HUNDREDACES 7
#define EIGHTHUNDREDKINGS 12
#define EIGHTYKINGS 6
#define SIXHUNDREDQUEENS 11
#define SIXTYQUEENS 5
#define FOURHUNDREDJACKS 10
#define FORTYJACKS 2
#define DOUBLEPINOCHLE 9
#define PINOCHLE 3

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

// Prints out the players, their hands, and an evalutation of their hands 
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
            std::cout << (*pm) << std:: endl; 
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

// Overloaded shift operator that prints out the appropriate string and integer value for a given meld
std::ostream& operator<<(std::ostream& os, const PinochleMelds& pinmelds) {
   
    switch(pinmelds){

        case PinochleMelds::dix:
            os << "dix : " << PinochleGame::meld_values[int(PinochleMelds::dix)]; 
            break;

        case PinochleMelds::offsuitmarriage:
            os << "offsuitmarriage : " << PinochleGame::meld_values[int(PinochleMelds::offsuitmarriage)]; 
            break;

        case PinochleMelds::fortyjacks:
            os << "fortyjacks : " << PinochleGame::meld_values[int(PinochleMelds::fortyjacks)]; 
            break;

        case PinochleMelds::pinochle:
            os << "pinochle : " << PinochleGame::meld_values[int(PinochleMelds::pinochle)]; 
            break;

        case PinochleMelds::insuitmarriage:
            os << "insuitmarriage : " << PinochleGame::meld_values[int(PinochleMelds::insuitmarriage)]; 
            break;

        case PinochleMelds::sixtyqueens:
            os << "sixtyqueens : " << PinochleGame::meld_values[int(PinochleMelds::sixtyqueens)]; 
            break;

        case PinochleMelds::eightykings:
            os << "eightykings : " << PinochleGame::meld_values[int(PinochleMelds::eightykings)]; 
            break;

        case PinochleMelds::hundredaces:
            os << "hundredaces : " << PinochleGame::meld_values[int(PinochleMelds::hundredaces)]; 
            break;

        case PinochleMelds::insuitrun:
            os << "insuitrun : " << PinochleGame::meld_values[int(PinochleMelds::insuitrun)]; 
            break;

        case PinochleMelds::doublepinochle:
            os << "doublepinochle : " << PinochleGame::meld_values[int(PinochleMelds::doublepinochle)];  
            break;

        case PinochleMelds::fourhundredjacks:
            os << "fourhundredjacks : " << PinochleGame::meld_values[int(PinochleMelds::fourhundredjacks)]; 
            break;

        case PinochleMelds::sixhundredqueens:
            os << "sixhundredqueens : " << PinochleGame::meld_values[int(PinochleMelds::sixhundredqueens)]; 
            break;

        case PinochleMelds::eighthundredkings:
            os << "eighthundredkings : " << PinochleGame::meld_values[int(PinochleMelds::eighthundredkings)]; 
            break;

        case PinochleMelds::thousandaces:
            os << "thousandaces : " << PinochleGame::meld_values[int(PinochleMelds::thousandaces)]; 
            break;

        case PinochleMelds::insuitdoublerun:
            os << "insuitdoublerun : " << PinochleGame::meld_values[int(PinochleMelds::insuitdoublerun)]; 
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
        if ((*it).rank == PinochleRank(ACE)) { 
            ++numAce;
            aceSuits.push_back((*it).suit);
        }
        else if ((*it).rank == PinochleRank(KING)) { 
            ++numKing;
            kingSuits.push_back((*it).suit);
        }
        else if ((*it).rank == PinochleRank(QUEEN)) { 
            ++numQueen;
            queenSuits.push_back((*it).suit);
        }
        else if ((*it).rank == PinochleRank(JACK)) { 
            ++numJack;
            jackSuits.push_back((*it).suit);
        }
    }

    if (numAce == ALLPRESENT) {
        combList.push_back(PinochleMelds(THOUSANDACES)); 
    }
    else if (numAce >= FOURPRESENT) {
        //testing if the suit is found in the vector of suits. if all are found then the meld is added
        if (std::find(aceSuits.begin(), aceSuits.end(), Suits(CLUBS)) != aceSuits.end()) { 
            if (std::find(aceSuits.begin(), aceSuits.end(), Suits(DIAMOND)) != aceSuits.end()) { 
                if (std::find(aceSuits.begin(), aceSuits.end(), Suits(HEART)) != aceSuits.end()) { 
                    if (std::find(aceSuits.begin(), aceSuits.end(), Suits(SPADE)) != aceSuits.end()) { 
                        combList.push_back(PinochleMelds(HUNDREDACES)); 
                    }
                }
            }
        }
    }

    if (numKing == ALLPRESENT) {
        combList.push_back(PinochleMelds(EIGHTHUNDREDKINGS)); 
    }  
    else if (numKing >= FOURPRESENT) {
        if (std::find(kingSuits.begin(), kingSuits.end(), Suits(CLUBS)) != kingSuits.end()) { 
            if (std::find(kingSuits.begin(), kingSuits.end(), Suits(DIAMOND)) != kingSuits.end()) { 
                if (std::find(kingSuits.begin(), kingSuits.end(), Suits(HEART)) != kingSuits.end()) { 
                    if (std::find(kingSuits.begin(), kingSuits.end(), Suits(SPADE)) != kingSuits.end()) { 
                        combList.push_back(PinochleMelds(EIGHTYKINGS)); 
                    }
                }
            }
        }
    }
    
    if (numQueen == ALLPRESENT) {
        combList.push_back(PinochleMelds(SIXHUNDREDQUEENS)); 
    }
    else if (numQueen >= FOURPRESENT) {
        if (std::find(queenSuits.begin(), queenSuits.end(), Suits(CLUBS)) != queenSuits.end()) { 
            if (std::find(queenSuits.begin(), queenSuits.end(), Suits(DIAMOND)) != queenSuits.end()) { 
                if (std::find(queenSuits.begin(), queenSuits.end(), Suits(HEART)) != queenSuits.end()) { 
                    if (std::find(queenSuits.begin(), queenSuits.end(), Suits(SPADE)) != queenSuits.end()) { 
                        combList.push_back(PinochleMelds(SIXTYQUEENS));
                    }
                }
            }
        }
    }

    if (numJack == ALLPRESENT) {
        combList.push_back(PinochleMelds(FOURHUNDREDJACKS)); 
    }
    else if (numJack >= FOURPRESENT) {
        if (std::find(jackSuits.begin(), jackSuits.end(), Suits(CLUBS)) != jackSuits.end()) { 
            if (std::find(jackSuits.begin(), jackSuits.end(), Suits(DIAMOND)) != jackSuits.end()) { 
                if (std::find(jackSuits.begin(), jackSuits.end(), Suits(HEART)) != jackSuits.end()) { 
                    if (std::find(jackSuits.begin(), jackSuits.end(), Suits(SPADE)) != jackSuits.end()) {
                        combList.push_back(PinochleMelds(FORTYJACKS)); 
                    }
                }
            }
        }
    }

    if (numJack >= TWOPRESENT && numQueen >= TWOPRESENT){
        //counts the number of the jack of diamonds and the queen of spades. if two of each found then the meld is added
        if((std::count(jackSuits.begin(), jackSuits.end(), Suits(DIAMOND)) == TWOPRESENT)
            && (std::count(queenSuits.begin(), queenSuits.end(), Suits(SPADE)) == TWOPRESENT)) {
                combList.push_back(PinochleMelds(DOUBLEPINOCHLE)); 
            }
    }
    else if (numJack >= ONEPRESENT && numQueen >= ONEPRESENT){
        if (std::find(jackSuits.begin(), jackSuits.end(), Suits(DIAMOND)) != jackSuits.end()) {
            if (std::find(queenSuits.begin(), queenSuits.end(), Suits(SPADE)) != queenSuits.end()) {
                combList.push_back(PinochleMelds(PINOCHLE)); 
            }
        }
    }
}
