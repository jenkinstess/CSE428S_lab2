// CardSet_T.h
// Sam Saxon s.saxon@wustl.edu
// Tess Jenkins jenkinstess@wustl.edu
// Contains the template creation of the CardSet as well as the copy constructor for CardSet. Contains the public delcarations 
//   for the print method, the >> operator, the a method checking if the Card Set is empty, and the function that gives access
//   to the protected vector data member. Contains the protected declaration for a vector member variable containing the cards.

#pragma once
#include "Suit.h"
#include "Card_T.h"
#include "Deck_T.h"
#include <vector>

template <typename R, typename S> class CardSet{
    public:
        CardSet() = default;
        CardSet(const CardSet<R,S>& old);
        void print(std::ostream& os, size_t size);
        CardSet<R,S>& operator>>(CardSet<R,S>& cs);
        bool is_empty();
        static std::vector< Card <R,S> > CardSet<R,S>::* get_cards();
    protected:
        std::vector< Card <R, S> > cards;
};

#ifdef TEMPLATE_HEADERS_INCLUDE_SOURCE
#include "CardSet_T.cpp"
#endif