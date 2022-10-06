// HoldEmGame.cpp
// Sam Saxon s.saxon@wustl.edu
// Tess Jenkins jenkinstess@wustl.edu
// Contains the definition for the constructor, the deal method, the play method, the collect all method, and the method printing out the players.

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