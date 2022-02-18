// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include <array>
#include <string>
#include "Pack.h"

// EFFECTS: Initializes the Pack to be in the following standard order:
//          the cards of the lowest suit arranged from lowest rank to
//          highest rank, followed by the cards of the next lowest suit
//          in order from lowest to highest rank, and so on.
// NOTE: The standard order is the same as that in pack.in.
// NOTE: Do NOT use pack.in in your implementation of this function
Pack::Pack() {
    Card c1(Card::RANK_NINE, Card::SUIT_SPADES);
    Card c2(Card::RANK_TEN, Card::SUIT_SPADES);
    Card c3(Card::RANK_JACK, Card::SUIT_SPADES);
    Card c4(Card::RANK_QUEEN, Card::SUIT_SPADES);
    Card c5(Card::RANK_KING, Card::SUIT_SPADES);
    Card c6(Card::RANK_ACE, Card::SUIT_SPADES);
    



    assert(false);

}

Pack::Pack(std::istream& pack_input) {
    assert(false);
    assert(next);
}

Card Pack::deal_one() {
    assert(false);
    assert(next);
}

void Pack::reset() {
    assert(false);
    assert(next);
}

void Pack::shuffle() {


    assert(false);
    assert(next);
}

bool Pack::empty() const {
    assert(false);
    assert(next);
}
