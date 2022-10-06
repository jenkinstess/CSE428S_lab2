// Card_T.h
// Sam Saxon s.saxon@wustl.edu
// Tess Jenkins jenkinstess@wustl.edu
// Contains template declarations for card types as well as the 
//   shift operator. Creates the rank enumeration as well. 

#pragma once
#include "Suit.h"

enum class Rank{
    ace   = 1,
    two   = 2,
    three = 3,
    four  = 4,
    five  = 5,
    six   = 6,
    seven = 7,
    eight = 8,
    nine  = 9,
    ten   = 10,
    jack  = 11,
    queen = 12,
    king  = 13
};

template <typename R, typename S> 
struct Card{
    R rank;
    S suit;
    Card(R _rank, S _suit);
};

template <typename R, typename S> 
std::ostream& operator<<(std::ostream& os, const Card<R,S>& card);


#ifdef TEMPLATE_HEADERS_INCLUDE_SOURCE
#include "Card_T.cpp"
#endif
