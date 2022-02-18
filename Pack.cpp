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
    
    Card c7(Card::RANK_NINE, Card::SUIT_HEARTS);
    Card c8(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card c9(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card c10(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card c11(Card::RANK_KING, Card::SUIT_HEARTS);
    Card c12(Card::RANK_ACE, Card::SUIT_HEARTS);
    
    Card c13(Card::RANK_NINE, Card::SUIT_CLUBS);
    Card c14(Card::RANK_TEN, Card::SUIT_CLUBS);
    Card c15(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card c16(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    Card c17(Card::RANK_KING, Card::SUIT_CLUBS);
    Card c18(Card::RANK_ACE, Card::SUIT_CLUBS);
    
    Card c19(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card c20(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    Card c21(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card c22(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card c23(Card::RANK_KING, Card::SUIT_DIAMONDS);
    Card c24(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    
    cards[0] = c1;
    cards[1] = c2;
    cards[2] = c3;
    cards[3] = c4;
    cards[4] = c5;
    cards[5] = c6;
    cards[6] = c7;
    cards[7] = c8;
    cards[8] = c9;
    cards[9] = c10;
    cards[10] = c11;
    cards[11] = c12;
    cards[12] = c13;
    cards[13] = c14;
    cards[14] = c15;
    cards[15] = c16;
    cards[16] = c17;
    cards[17] = c18;
    cards[18] = c19;
    cards[19] = c20;
    cards[20] = c21;
    cards[21] = c22;
    cards[22] = c23;
    cards[23] = c24;
}
// REQUIRES: pack_input contains a representation of a Pack in the
//           format required by the project specification
// MODIFIES: pack_input
// EFFECTS: Initializes Pack by reading from pack_input.
Pack::Pack(std::istream& pack_input) {
    std::string inpRank;
    std::string inpSuit;
    std::string trash;
    
    for (int i = 0; i < PACK_SIZE; i++) {
        pack_input >> inpRank >> trash >> inpSuit;
        Card c(inpRank, inpSuit);
        cards[i] = c;
    }
    
}
// REQUIRES: cards remain in the Pack
// EFFECTS: Returns the next card in the pack and increments the next index
Card Pack::deal_one() {
    int index = this->next;
    this->next++;
    return cards[index];
}

void Pack::reset() {
    this->next = 0;
}

void Pack::shuffle() {
    assert(false);
    assert(next);

    
}

bool Pack::empty() const {
    return this->next > 23;
}
