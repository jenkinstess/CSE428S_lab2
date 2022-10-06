// lab1.cpp
// Sam Saxon s.saxon@wustl.edu
// Tess Jenkins jenkinstess@wustl.edu
// Contains the main function that takes the user input from the command line where the user specified the game they would
//   like to play and the players who will be playing the game, and then shows the cards of the players and shows the game  
//   itself occurring. The main function also allows the user the option to continue the game or stop playing. 
//   This file also contains the delcaration and definition of the create method.

#include "HoldEmGame.h"
#include "PinochleGame.h"
#include <iostream>
#include <memory>
#include <string.h>
#define SUCCESS 0
#define PINOCHLEPLAYERS 6 
#define MINHOLDEMPLAYERS 4
#define MAXHOLDEMPLAYERS 11
#define ARGSPASSED 2
#define GAMENAME 1
#define INCORRECTINPUT 5
#define NULLGAME 3

std::shared_ptr<Game> create(int argc, const char* argv[]);

int main(int argc, const char* argv[]) {

    if (argc < ARGSPASSED) {
        std::cout << "usage: filename gamename playername1 playername2 ..." << std::endl;
        return INCORRECTINPUT;
    }
    
    if (((strcmp(argv[GAMENAME],"Pinochle") == 0) && argc == PINOCHLEPLAYERS) 
        || (((strcmp(argv[GAMENAME], "HoldEm") == 0) && (argc >= MINHOLDEMPLAYERS && argc <= MAXHOLDEMPLAYERS)))) {
            
            std::shared_ptr<Game> gamePtr = create(argc, argv);

            if (gamePtr) {
                return gamePtr->play();
            }
            else {
                std::cout << "No game created" << std::endl;
                return NULLGAME;
            }
    }
    else{
        std::cout << "usage: ./lab1 gamename playername1 playername2 ..." << std::endl;
        return INCORRECTINPUT;
    }

    return SUCCESS; 
}

// Utilizes shared pointers to create instances of Pinochle or Texas Hold Em based on the users input
std::shared_ptr<Game> create(int argc, const char* argv[]) {
    
    std::shared_ptr<Game> game1;

    if (strcmp(argv[GAMENAME],"Pinochle") == 0 ) {
        game1 = std::make_shared<PinochleGame>(argc, argv);
    }
    else {
        game1 = std::make_shared<HoldEmGame>(argc, argv);
    }

    return game1;
}