// Deck_T.h
// Sam Saxon s.saxon@wustl.edu
// Tess Jenkins jenkinstess@wustl.edu
// Contains the creation of the Deck class and the declaration for the public methods shuffle and collect.

#pragma once
#include "CardSet_T.h"

template <typename R, typename S> 
class Deck : public CardSet<R,S>{
public:
    void shuffle();
    void collect(CardSet<R,S>& cs);
};

#ifdef TEMPLATE_HEADERS_INCLUDE_SOURCE
#include "Deck_T.cpp"
#endif