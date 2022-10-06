// Game.h
// Sam Saxon s.saxon@wustl.edu
// Tess Jenkins jenkinstess@wustl.edu
// Contains public declarations for the Game class constructor and the pure virtual play method. Contains a protected declaration
//  of a vector memeber variable containing the names of the players of the current game. 

#pragma once
#include <string>
#include <vector>

class Game {
public:
    Game(int argc, const char* argv[]);
    virtual int play() = 0;
protected:
    std::vector<std::string> players;
};