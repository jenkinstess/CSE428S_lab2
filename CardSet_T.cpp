// CardSet_T.cpp
// Sam Saxon s.saxon@wustl.edu
// Tess Jenkins jenkinstess@wustl.edu
// Contains the definitions for the print method, the >> operator, and the is_empty method.

#include "CardSet_T.h"
#include <iostream>
#include <iterator>

#define EMPTYSET 0

// Prints out the cards, checks that there are cards to print out to begin with. 
template <typename R, typename S>
void CardSet<R,S>::print(std::ostream& os, size_t size){
    
    typename std::vector< Card<R, S> >::iterator it;
    for(it = cards.begin(); it < cards.end(); it++){
        if (size == EMPTYSET) {break;}
        --size;

        os << *it << " ";
    }

    os << std::endl;

}

// Get the last element in the vector of cards, pushes that card onto the cardSet passed into the parameters, then deletes that card
//   off of the original cards. 
template <typename R, typename S>
CardSet<R,S>& CardSet<R,S>::operator>>(CardSet<R,S>& cs) {

    if (is_empty()) {
        throw std::runtime_error("card set empty");
    }
    

    // get the last element in the vector
    // push this element onto cs, the vector cardset
    // then do pop_back 
    cs.cards.push_back(cards.back());
    cards.pop_back();

    return *this;
}

// Checks if cards is empty or not. 
template <typename R, typename S>
bool CardSet<R,S>::is_empty() {
    return cards.empty();
}
