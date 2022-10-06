// PinochleDeck.h
// Sam Saxon s.saxon@wustl.edu
// Tess Jenkins jenkinstess@wustl.edu
// Contains shift and increment operator declarations, the inheritence of the deck class,
//   and the enumeration for the ranks of pinochle

#pragma once
#include "Card_T.h"
#include "Deck_T.h"
#include <vector>
#include <ostream>

enum class PinochleRank{
    nine, jack, queen, king, ten, ace, undefined
};

class PinochleDeck : public Deck<PinochleRank, Suits> {
    public:
	    PinochleDeck();

};

PinochleRank operator++(PinochleRank& _rank, int);

std::ostream& operator<<(std::ostream& os, const PinochleRank& pinRank);



