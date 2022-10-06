// Deck_T.cpp
// Sam Saxon s.saxon@wustl.edu
// Tess Jenkins jenkinstess@wustl.edu
// Contains the definitions for the shuffle and collect methods.

#include "Deck_T.h"
#include <random>
#include <algorithm>

// Randomizes the order of the cards, uses a Mersenne Twister pseudo-random generator to do so.
template<typename R,typename S>
void Deck<R,S>::shuffle() {
    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(CardSet<R,S>::cards.begin(), CardSet<R,S>::cards.end(), g);
}

template<typename R,typename S>
void Deck<R,S>::collect(CardSet<R,S>& cs) {
    while(!cs.is_empty()) {
        cs >> *this;
    }
}