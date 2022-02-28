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
    int index = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 7; j < 13; j++) {
            Card c(RANK_NAMES_BY_WEIGHT[j], SUIT_NAMES_BY_WEIGHT[i]);
            cards[index] = c;
            index++;
        }
    }
    
    next = 0;
    
}
// REQUIRES: pack_input contains a representation of a Pack in the
//           format required by the project specification
// MODIFIES: pack_input
// EFFECTS: Initializes Pack by reading from pack_input.
Pack::Pack(std::istream& pack_input) {
    std::string inpRank;
    std::string inpSuit;
    std::string trash;
    next = 0;
    for (int i = 0; i < PACK_SIZE; i++) {
        pack_input >> inpRank >> trash >> inpSuit;
        Card c(inpRank, inpSuit);
        cards[i] = c;
    }
    
}
// REQUIRES: cards remain in the Pack
// EFFECTS: Returns the next card in the pack and increments the next index
Card Pack::deal_one() {
    int index = next;
    next++;
    return cards[index];
}

void Pack::reset() {
    next = 0;
}

void Pack::shuffle() {
    std::array<Card, 12> top;
    std::array<Card, 12> bottom;
    for (int j = 0; j < 2; j++) {
        for (int i = 0; i < PACK_SIZE; i++) {
            if (i < 12) {
                top[i] = cards[i];
            }
            else if (i >= 12) {
                bottom[i - 12] = cards[i];
            }
        }
        int bottomIndex = 0;
        int topIndex = 0;
        for (int c = 0; c < 24; c++) {
            if (c % 2 == 0) {
                cards[c] = bottom[bottomIndex];
                bottomIndex++;
            }
            else {
                cards[c] = top[topIndex];
                topIndex++;
            }
        }
    }
    
    reset();
}

bool Pack::empty() const {
    return next > 23;
}
