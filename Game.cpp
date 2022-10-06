// Game.cpp
// Sam Saxon s.saxon@wustl.edu
// Tess Jenkins jenkinstess@wustl.edu
// Contains the definition for the constructor of the Game class. 

#include "Game.h"
#define PLAYERNAMESTART 2

// The parameters will be passed directly from command line ***
Game::Game(int argc, const char* argv[]) {

    std::vector<std::string> temp;
    for (int i = PLAYERNAMESTART; i < argc; ++i) {
        players.push_back(argv[i]);
    }

    players = temp;
}