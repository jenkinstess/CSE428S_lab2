// Card_T.cpp
// Sam Saxon s.saxon@wustl.edu
// Tess Jenkins jenkinstess@wustl.edu
// Contains template and shift operator definitions. 

#include "Card_T.h"

template <typename R, typename S>
Card<R,S>::Card(R _rank, S _suit) : rank (_rank), suit (_suit) {
}

template <typename R, typename S>
std::ostream& operator<<(std::ostream& os, const Card<R, S>& card){
    os << card.rank << card.suit;
    return os;
}

template <typename R, typename S> 
bool lessThanRank(const Card<R,S>& a, const Card<R,S>& b) {
    if (a._rank < b._rank || (a._rank == b._rank) && (a._suit < b._suit)) {
        return true;
    }
    else{
        return false;
    }
}

template <typename R, typename S> 
bool lessThanSuit(const Card<R,S>& a, const Card<R,S>& b) {
    if (a._suit < b._suit || (a._rank < b._rank) && (a._suit == b._suit)) {
        return true;
    }
    else{
        return false;
    }
}