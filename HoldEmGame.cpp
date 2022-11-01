// HoldEmGame.cpp
// Sam Saxon s.saxon@wustl.edu
// Tess Jenkins jenkinstess@wustl.edu
// Contains the definition for the constructor, the deal method, the play method, the collect all method, and the method printing out the players.

#include <cstdint>
#include <unordered_map>
#include <algorithm>
#include <set>
#include "HoldEmGame.h"
#define HAND_SIZE 2
#define SUCCESS 0
#define SIZESET 100

#define EVAL_SIZE 5
#define NUM_SUITS 4
#define RANK_BIT_WIDTH 4

#define ACE_LOW_STRAIGHT (15|(1<<12))
#define STRAIGHT 31

#define MAGIC_NUM 15
#define X_HIGH 5
#define PAIR 6
#define TWO_PAIR 7
#define THREE_OF_A_KIND 9
#define FULL_HOUSE 10
#define FOUR_OF_A_KIND 1

// HoldEmGame constructor. Pushes all the current players passed in via the command line onto the memeber variable that 
//  is a vector containing the hands of the current players
HoldEmGame::HoldEmGame(int argc, const char* argv[]) : Game(argc, argv) {
    for(int i = 0; i < argc-HAND_SIZE; ++i){
        CardSet<HoldEmRank, Suits> cs;
        hands.push_back(cs);
    }

    state = HoldEmState::preflop;
}

HoldEmGame::Player::Player(CardSet<HoldEmRank, Suits> cs, std::string& pn, HoldEmHandRank r) :
    hand(cs), player_name(pn), hand_rank(r) {}

//deals out cards to each player, then to each state that the Texas hold em game is in.
void HoldEmGame::deal() {

    switch (state) {
        case HoldEmState::preflop: {

            // deal 2 cards to each player
            typename std::vector< CardSet<HoldEmRank, Suits> >::iterator it;
            for (int i = 0; i < HAND_SIZE; ++i) {
                for (it = hands.begin(); it < hands.end(); ++it) {
                    try{
                        deck >> (*it);
                    }
                    catch (std::runtime_error &e){
                        std::cout << "Runtime error: " << e.what();
                    }
                }
            }

            state = HoldEmState::flop;
            break;
        }
        case HoldEmState::flop: {
            try{
                deck >> board;
                deck >> board;
                deck >> board;
            }
            catch (std::runtime_error &e){
                std::cout << "Runtime error: " << e.what();
            }

            state = HoldEmState::turn;
            break;
        }   
        case HoldEmState::turn: {

            try{
                deck >> board;
            }
            catch (std::runtime_error &e){
                std::cout << "Runtime error: " << e.what();
            }

            state = HoldEmState::river;
            break;
        }
        case HoldEmState::river: {

            try{
                deck >> board;
            }
            catch (std::runtime_error &e){
                std::cout << "Runtime error: " << e.what();
            }

            state = HoldEmState::undefined;
            break;
        }
        default:
            break;
    }

}

// Starts the play of the game, dealing out cards to the players and then simulating a game of poker.
int HoldEmGame::play() {
    deck.shuffle();
    state = HoldEmState::preflop;

    deal();
    print_players();

    deal();
    std::cout << "BOARD (flop): ";
    board.print(std::cout, SIZESET);

    std::cout << std::endl;
    std::vector<Player> p;
    for(long unsigned int i = 0; i < hands.size(); ++i) {
        CardSet<HoldEmRank, Suits> bd_cpy = board, hand = hands[i];

        bd_cpy >> hand;
        bd_cpy >> hand;
        bd_cpy >> hand;

        p.push_back( Player(hand, players[i], holdem_hand_evaluation(hand)) );
    }

    std::sort(p.rbegin(), p.rend());

    std::vector< Player >::iterator it;
    for (it = p.begin(); it < p.end(); ++it) {
        std::cout << (*it).player_name << ": " << (*it).hand_rank << std::endl;
        (*it).hand.print(std::cout, SIZESET);
        std::cout << std::endl;
    }

    deal();
    std::cout << "BOARD (turn): ";
    board.print(std::cout, SIZESET);

    deal();
    std::cout << "BOARD (river): ";
    board.print(std::cout, SIZESET);

    collect_all();

    std::string input;
    std::cout << "end game? " << std::endl;
    std::cin >> input;
    
    if (input == "yes") {
        return SUCCESS;
    }

    return play();
}


void HoldEmGame::print_players() {
    typename std::vector< CardSet<HoldEmRank, Suits> >::iterator it = hands.begin();
    std::vector<std::string>::iterator p = Game::players.begin();
    
    while (it < hands.end()) {
        std::cout << (*p) << std::endl;
        (*it).print(std::cout, SIZESET);
        std::cout << std::endl;

        p++;
        it++;
    }
}


void HoldEmGame::collect_all() {
    typename std::vector< CardSet<HoldEmRank, Suits> >::iterator it;
    for (it = hands.begin(); it < hands.end(); it++) {
        deck.collect(*it);
    }

    deck.collect(board);
}

HoldEmHandRank HoldEmGame::holdem_hand_evaluation(const CardSet<HoldEmRank,Suits>& cs) {
    std::vector< Card<HoldEmRank, Suits> > cards = cs.*(cs.get_cards());

    if (cards.size() != EVAL_SIZE) {
        return HoldEmHandRank::undefined;
    }

    int16_t unique_cards = 0;
    uint64_t card_freq = 0;
    std::set<int> suits_present;

    // iterate through cards and construct unique_cards and card_freq
    std::vector< Card<HoldEmRank, Suits> >::iterator it;
    for (it = cards.begin(); it < cards.end(); it++) {
        int r = (int)((*it).rank);
        int s = (int)((*it).suit);
        
        unique_cards |= (1<<r);
        card_freq |= ( card_freq + ( 1ULL << (NUM_SUITS*r) ) );

        suits_present.insert(s);

    }

    HoldEmHandRank res = HoldEmHandRank::undefined;
    switch (card_freq % MAGIC_NUM) {
        case FOUR_OF_A_KIND:
            res = HoldEmHandRank::fourofakind;
            break;
        case FULL_HOUSE:
            res = HoldEmHandRank::fullhouse;
            break;
        case THREE_OF_A_KIND: 
            res = HoldEmHandRank::threeofakind;
            break;
        case TWO_PAIR: 
            res = HoldEmHandRank::twopair;
            break;
        case PAIR:
            res = HoldEmHandRank::pair;
            break;
        case X_HIGH:
            res = HoldEmHandRank::xhigh;
            break;
        default:
            break;
    }

    bool is_straight = false;

    //normalize unique_cards to find straights
    int16_t lsb = unique_cards & (-unique_cards);
    if ( ((unique_cards / lsb) == STRAIGHT) || (unique_cards == ACE_LOW_STRAIGHT)) {
        res = std::max(res, HoldEmHandRank::straight);
        is_straight = true;
    }

    //flush if only 1 suit is present
    if (suits_present.size() == 1) {
        if (is_straight) {
            return HoldEmHandRank::straightflush;
        }

        res = std::max(res, HoldEmHandRank::flush);
    }

    return res;
}

bool operator<(const HoldEmGame::Player& p1, const HoldEmGame::Player& p2) {

    if (p1.hand_rank < p2.hand_rank) {
        return true;
    }

    if (p1.hand_rank > p2.hand_rank) {
        return false;
    }

    //more in depth comparison when the evaluation is equal
    std::vector< Card<HoldEmRank, Suits> > p1_cards = p1.hand.*(p1.hand.get_cards());
    std::vector< Card<HoldEmRank, Suits> > p2_cards = p2.hand.*(p2.hand.get_cards());

    std::vector<int> p1_ranks;
    std::vector<int> p2_ranks;

    std::vector< Card<HoldEmRank, Suits> >::iterator it1;
    for (it1 = p1_cards.begin(); it1 < p1_cards.end(); it1++) {
        int r = (int)((*it1).rank);
        p1_ranks.push_back(r);

    }

    std::vector< Card<HoldEmRank, Suits> >::iterator it2;
    for (it2 = p2_cards.begin(); it2 < p2_cards.end(); it2++) {
        int r = (int)((*it2).rank);
        p2_ranks.push_back(r);

    }

    // sort ranks by increasing frequency then increasing value
    frequency_sort(p1_ranks);
    frequency_sort(p2_ranks);

    int p1_value = 0, p2_value = 0;
    for (int i = 0; i < EVAL_SIZE; i++) {
        p1_value |= (p1_ranks[i] << (RANK_BIT_WIDTH*i));
        p2_value |= (p2_ranks[i] << (RANK_BIT_WIDTH*i));
    }

    return p1_value < p2_value;
}

// frequency sort helper function, credit to: https://coderscat.com/leetcode-sort-array-by-increasing-frequency/
// sorts array by increasing frequency, then by increasing value
void frequency_sort(std::vector<int>& nums) {
        std::unordered_map<int, int> cnt;

        for (auto n : nums) {
            cnt[n]++;
        }

        sort(nums.begin(), nums.end(), [&cnt](int a, int b) {
            return (cnt[a] == cnt[b]) ? a < b : cnt[a] < cnt[b];
        });
    }

std::ostream& operator<<(std::ostream& os, const HoldEmHandRank& r) {
   
    switch(r){

        case HoldEmHandRank::xhigh:
            os << "xhigh ";
            break;

        case HoldEmHandRank::pair:
            os << "pair ";
            break;

        case HoldEmHandRank::twopair:
            os << "twopair ";
            break;

        case HoldEmHandRank::threeofakind:
            os << "threeofakind ";
            break;

        case HoldEmHandRank::straight:
            os << "straight ";
            break;

        case HoldEmHandRank::flush:
            os << "flush ";
            break;

        case HoldEmHandRank::fullhouse:
            os << "fullhouse ";
            break;

        case HoldEmHandRank::fourofakind:
            os << "fourofakind ";
            break;

        case HoldEmHandRank::straightflush:
            os << "straightflush ";
            break;

        default:
            os << "?";
            break;

    }

    return os;
}