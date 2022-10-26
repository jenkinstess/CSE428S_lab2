// PinochleGame.cpp
// Sam Saxon s.saxon@wustl.edu
// Tess Jenkins jenkinstess@wustl.edu
// Contains the definition for the constructor, the deal method, the play method, the collect all method, and the method printing out the players.

#include "PinochleGame.h"
#define SUCCESS 0
#define SIZESET 100

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

void PinochleGame::print_players() {
    typename std::vector< CardSet<PinochleRank, Suits> >::iterator it = _curHand.begin();
    std::vector<std::string>::iterator p = Game::players.begin();
    
    while (it < _curHand.end()) {
        std::cout << (*p) << std::endl;
        (*it).print(std::cout, SIZESET);
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
            os << "dix " << PinochleMelds::dix;
            break;

        case PinochleMelds::offsuitmarriage:
            os << "offsuitmarriage " << PinochleMelds::offsuitmarriage;
            break;

        case PinochleMelds::fortyjacks:
            os << "fortyjacks " << PinochleMelds::fortyjacks;
            break;

        case PinochleMelds::pinochle:
            os << "pinochle " << PinochleMelds::pinochle;
            break;

        case PinochleMelds::insuitmarriage:
            os << "insuitmarriage " << PinochleMelds::insuitmarriage;
            break;

        case PinochleMelds::sixtyqueens:
            os << "sixtyqueens " << PinochleMelds::sixtyqueens;
            break;

        case PinochleMelds::eightykings:
            os << "eightykings " << PinochleMelds::eightykings;
            break;

        case PinochleMelds::hundredaces:
            os << "hundredaces " << PinochleMelds::hundredaces;
            break;

        case PinochleMelds::insuitrun:
            os << "insuitrun " << PinochleMelds::insuitrun;
            break;

        case PinochleMelds::doublepinochle:
            os << "doublepinochle " << PinochleMelds::doublepinochle;
            break;

        case PinochleMelds::fourhundredjacks:
            os << "fourhundredjacks " << PinochleMelds::fourhundredjacks;
            break;

        case PinochleMelds::sixhundredqueens:
            os << "sixhundredqueens " << PinochleMelds::sixhundredqueens;
            break;

        case PinochleMelds::eighthundredkings:
            os << "eighthundredkings " << PinochleMelds::eighthundredkings;
            break;

        case PinochleMelds::thousandaces:
            os << "thousandaces " << PinochleMelds::thousandaces;
            break;

        case PinochleMelds::insuitdoublerun:
            os << "insuitdoublerun " << PinochleMelds::insuitdoublerun;
            break;

        default:
            os << "?";
            break;

    }

    return os;
}

void PinochleGame::suit_independent_evaluation(const CardSet<PinochleRank, Suits>& hand, std::vector<PinochleMelds> combList) {
    //CardSet<PinochleRank, Suits> locHand(hand);

    //std::vector<int> 
}