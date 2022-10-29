// HoldEmGame.cpp
// Sam Saxon s.saxon@wustl.edu
// Tess Jenkins jenkinstess@wustl.edu
// Contains the definition for the constructor, the deal method, the play method, the collect all method, and the method printing out the players.

#include <cstdint>
#include <algorithm>
#include <set>
#include "HoldEmGame.h"
#define HAND_SIZE 2
#define SUCCESS 0
#define SIZESET 100

// HoldEmGame constructor. Pushes all the current players passed in via the command line onto the memeber variable that 
//  is a vector containing the hands of the current players
HoldEmGame::HoldEmGame(int argc, const char* argv[]) : Game(argc, argv) {
    for(int i = 0; i < argc-HAND_SIZE; ++i){
        CardSet<HoldEmRank, Suits> cs;
        hands.push_back(cs);
    }

    state = HoldEmState::preflop;
}

//deals out cards to each player, then to each state that the Texas hold em game is in.
void HoldEmGame::deal() {

    switch (state) {
        case HoldEmState::preflop: {

            // deal 2 cards to each player
            typename std::vector< CardSet<HoldEmRank, Suits> >::iterator it;
            for (int i = 0; i < HAND_SIZE; ++i) {
                for (it = hands.begin(); it < hands.end(); ++it) {
                    try{
                        deck >> (*it);
                    }
                    catch (std::runtime_error &e){
                        std::cout << "Runtime error: " << e.what();
                    }
                }
            }

            state = HoldEmState::flop;
            break;
        }
        case HoldEmState::flop: {
            try{
                deck >> board;
                deck >> board;
                deck >> board;
            }
            catch (std::runtime_error &e){
                std::cout << "Runtime error: " << e.what();
            }

            state = HoldEmState::turn;
            break;
        }   
        case HoldEmState::turn: {

            try{
                deck >> board;
            }
            catch (std::runtime_error &e){
                std::cout << "Runtime error: " << e.what();
            }

            state = HoldEmState::river;
            break;
        }
        case HoldEmState::river: {

            try{
                deck >> board;
            }
            catch (std::runtime_error &e){
                std::cout << "Runtime error: " << e.what();
            }

            state = HoldEmState::undefined;
            break;
        }
        default:
            break;
    }

}

// Starts the play of the game, dealing out cards to the players and then simulating a game of poker.
int HoldEmGame::play() {
    deck.shuffle();
    state = HoldEmState::preflop;

    deal();
    print_players();

    deal();
    std::cout << "BOARD (flop): ";
    board.print(std::cout, SIZESET);

    deal();
    std::cout << "BOARD (turn): ";
    board.print(std::cout, SIZESET);

    deal();
    std::cout << "BOARD (river): ";
    board.print(std::cout, SIZESET);

    collect_all();

    std::string input;
    std::cout << "end game? " << std::endl;
    std::cin >> input;
    
    if (input == "yes") {
        return SUCCESS;
    }

    return play();
}


void HoldEmGame::print_players() {
    typename std::vector< CardSet<HoldEmRank, Suits> >::iterator it = hands.begin();
    std::vector<std::string>::iterator p = Game::players.begin();
    
    while (it < hands.end()) {
        std::cout << (*p) << std::endl;
        (*it).print(std::cout, SIZESET);
        std::cout << std::endl;

        p++;
        it++;
    }
}


void HoldEmGame::collect_all() {
    typename std::vector< CardSet<HoldEmRank, Suits> >::iterator it;
    for (it = hands.begin(); it < hands.end(); it++) {
        deck.collect(*it);
    }

    deck.collect(board);
}

HoldEmHandRank HoldEmGame::holdem_hand_evaluation(const CardSet<HoldEmRank,Suits>& cs) {
    std::vector< Card<HoldEmRank, Suits> > cards = cs.*(cs.get_cards());

    /* code to test hand evaluation DELETE AT END
    std::vector< Card<HoldEmRank, Suits> > v;
    v.push_back(Card<HoldEmRank,Suits>(HoldEmRank::ace, Suits::clubs));
    v.push_back(Card<HoldEmRank,Suits>(HoldEmRank::five, Suits::clubs));
    v.push_back(Card<HoldEmRank,Suits>(HoldEmRank::ace, Suits::diamonds));
    v.push_back(Card<HoldEmRank,Suits>(HoldEmRank::ace, Suits::hearts));
    v.push_back(Card<HoldEmRank,Suits>(HoldEmRank::ace, Suits::spades));
    cards = v;*/

    if (cards.size() != 5) {
        return HoldEmHandRank::undefined;
    }

    int16_t unique_cards = 0;
    uint64_t card_freq = 0;
    std::set<int> suits_present;

    std::vector< Card<HoldEmRank, Suits> >::iterator it;
    for (it = cards.begin(); it < cards.end(); it++) {
        int r = (int)((*it).rank);
        int s = (int)((*it).suit);
        
        unique_cards |= (1<<r);
        card_freq |= ( card_freq + ( 1ULL << (4*r) ) );

        suits_present.insert(s);

    }

    HoldEmHandRank res = HoldEmHandRank::undefined;
    switch (card_freq % 15) {
        case 1: // four of a kind
            res = HoldEmHandRank::fourofakind;
            break;
        case 10: // full house
            res = HoldEmHandRank::fullhouse;
            break;
        case 9: // three of a kind
            res = HoldEmHandRank::threeofakind;
            break;
        case 7: // two pair
            res = HoldEmHandRank::twopair;
            break;
        case 6: // pair
            res = HoldEmHandRank::pair;
            break;
        case 5: // high card
            res = HoldEmHandRank::xhigh;
            break;
        default:
            break;
    }

    bool is_straight = false;

    //normalize unique_cards to find straights
    int16_t lsb = unique_cards & (-unique_cards);
    if ( ((unique_cards / lsb) == 31) || (unique_cards == (15|(1<<12)))) {
        res = std::max(res, HoldEmHandRank::straight);
        is_straight = true;
    }

    if (suits_present.size() == 1) {
        if (is_straight) {
            return HoldEmHandRank::straightflush;
        }

        res = std::max(res, HoldEmHandRank::flush);
    }

    return res;
}

std::ostream& operator<<(std::ostream& os, const HoldEmHandRank& r) {
   
    switch(r){

        case HoldEmHandRank::xhigh:
            os << "xhigh ";
            break;

        case HoldEmHandRank::pair:
            os << "pair ";
            break;

        case HoldEmHandRank::twopair:
            os << "twopair ";
            break;

        case HoldEmHandRank::threeofakind:
            os << "threeofakind ";
            break;

        case HoldEmHandRank::straight:
            os << "straight ";
            break;

        case HoldEmHandRank::flush:
            os << "flush ";
            break;

        case HoldEmHandRank::fullhouse:
            os << "fullhouse ";
            break;

        case HoldEmHandRank::fourofakind:
            os << "fourofakind ";
            break;

        case HoldEmHandRank::straightflush:
            os << "straightflush ";
            break;

        default:
            os << "?";
            break;

    }

    return os;
}