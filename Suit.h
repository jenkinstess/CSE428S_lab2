// Suit.h
// Sam Saxon s.saxon@wustl.edu
// Tess Jenkins jenkinstess@wustl.edu
// Contains shift and increment operator declarations and the enumeration for the suits of the cards

#pragma once
#include <iostream>

enum class Suits{
    clubs, diamonds, hearts, spades, undefined
};

Suits operator++(Suits& suit, int);

std::ostream& operator<<(std::ostream& os, const Suits& suit);

