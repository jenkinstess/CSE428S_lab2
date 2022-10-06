// HoldEmDeck.h
// Sam Saxon s.saxon@wustl.edu
// Tess Jenkins jenkinstess@wustl.edu
// Contains shift and increment operator declarations, the inheritence of the deck class,
//   and the enumeration for the ranks of poker

#pragma once
#include "Card_T.h"
#include "Deck_T.h"
#include <vector>
#include <ostream>

enum class HoldEmRank{
    two, three, four, five, six, seven, eight, nine, ten, jack, queen, king, ace, undefined
};

class HoldEmDeck : public Deck <HoldEmRank, Suits> {
    public:
	    HoldEmDeck();
	
};

HoldEmRank operator++(HoldEmRank& _rank, int);

std::ostream& operator<<(std::ostream& os, const HoldEmRank& _rank);

