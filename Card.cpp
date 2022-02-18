// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <string>
#include "Card.h"
#include <sstream>
// add any necessary #include or using directives here

// rank and suit names -- do not remove these
constexpr const char* const Card::RANK_TWO;
constexpr const char* const Card::RANK_THREE;
constexpr const char* const Card::RANK_FOUR;
constexpr const char* const Card::RANK_FIVE;
constexpr const char* const Card::RANK_SIX;
constexpr const char* const Card::RANK_SEVEN;
constexpr const char* const Card::RANK_EIGHT;
constexpr const char* const Card::RANK_NINE;
constexpr const char* const Card::RANK_TEN;
constexpr const char* const Card::RANK_JACK;
constexpr const char* const Card::RANK_QUEEN;
constexpr const char* const Card::RANK_KING;
constexpr const char* const Card::RANK_ACE;

constexpr const char* const Card::SUIT_SPADES;
constexpr const char* const Card::SUIT_HEARTS;
constexpr const char* const Card::SUIT_CLUBS;
constexpr const char* const Card::SUIT_DIAMONDS;

// add your code below

Card::Card() {
    this->rank = "Two";
    this->suit = "Spades";
}

Card::Card(const std::string &rank_in, const std::string &suit_in) {
    this->rank = rank_in;
    this->suit = suit_in;
}

std::string Card::get_rank() const {
    return rank;
}

std::string Card::get_suit() const {
    return suit;
}

std::string Card::get_suit(const std::string &trump) const {
    if (trump == SUIT_DIAMONDS) {
        if (this->suit == SUIT_HEARTS && this->rank == RANK_JACK) {
            return SUIT_DIAMONDS;
        }
    }
    else if (trump == SUIT_HEARTS) {
        if (this->suit == SUIT_DIAMONDS && this->rank == RANK_JACK) {
            return SUIT_HEARTS;
        }
    }
    else if (trump == SUIT_SPADES) {
        if (this->suit == SUIT_CLUBS && this->rank == RANK_JACK) {
            return SUIT_SPADES;
        }
    }
    else if (trump == SUIT_CLUBS) {
        if (this->suit == SUIT_SPADES && this->rank == RANK_JACK) {
            return SUIT_CLUBS;
        }
    }
    
    return this->suit;
}

bool Card::is_face() const {
    return this->rank == "Jack" || this->rank == "King" || this->rank == "Queen";
}

bool Card::is_right_bower(const std::string &trump) const {
    return this->suit == trump && this->rank == "Jack";
}

bool Card::is_left_bower(const std::string &trump) const {
    if (trump == "Diamonds") {
        if (this->suit == "Hearts" && this->rank == "Jack") {
            return true;
        }
    }
    else if (trump == "Hearts") {
        if (this->suit == "Diamonds" && this->rank == "Jack") {
            return true;
        }
    }
    else if (trump == "Spades") {
        if (this->suit == "Clubs" && this->rank == "Jack") {
            return true;
        }
    }
    else if (trump == "Clubs") {
        if (this->suit == "Spades" && this->rank == "Jack") {
            return true;
        }
    }
    
    return false;
}

bool Card::is_trump(const std::string &trump) const {
    return is_left_bower(trump) || (this->suit == trump);
}

//EFFECTS Returns true if lhs is lower value than rhs.
//  Does not consider trump.
//(A > K > Q > J > 10 > 9), with ties broken by suit (D > C > H > S)
bool operator<(const Card &lhs, const Card &rhs) {
    int lhsCardVal = 0;
    int rhsCardVal = 0;

    if (lhs.get_rank() == RANK_NINE) {
        lhsCardVal += 10;
    }
    else if (lhs.get_rank() == RANK_TEN){
        lhsCardVal += 20;
    }
    else if (lhs.get_rank() == RANK_JACK){
        lhsCardVal += 30;
    }
    else if(lhs.get_rank() == RANK_QUEEN){
        lhsCardVal += 40;
    }
    else if (lhs.get_rank() == RANK_KING) {
        lhsCardVal += 50;
    }
    else if (lhs.get_rank() == RANK_ACE) {
        lhsCardVal += 60;
    }

    if (lhs.get_suit() == SUIT_SPADES) {
        lhsCardVal += 1;
    }
    else if (lhs.get_suit() == SUIT_HEARTS) {
        lhsCardVal += 2;
    }
    else if (lhs.get_suit() == SUIT_CLUBS) {
        lhsCardVal += 3;
    }
    else if (lhs.get_suit() == SUIT_DIAMONDS) {
        lhsCardVal += 4;
    }




    if (rhs.get_rank() == RANK_NINE) {
        rhsCardVal += 10;
    }
    else if (rhs.get_rank() == RANK_TEN) {
        rhsCardVal += 20;
    }
    else if (rhs.get_rank() == RANK_JACK) {
        rhsCardVal += 30;
    }
    else if (rhs.get_rank() == RANK_QUEEN) {
        rhsCardVal += 40;
    }
    else if (rhs.get_rank() == RANK_KING) {
        rhsCardVal += 50;
    }
    else if (rhs.get_rank() == RANK_ACE) {
        rhsCardVal += 60;
    }

    if (rhs.get_suit() == SUIT_SPADES) {
        rhsCardVal += 1;
    }
    else if (rhs.get_suit() == SUIT_HEARTS) {
        rhsCardVal += 2;
    }
    else if (rhs.get_suit() == SUIT_CLUBS) {
        rhsCardVal += 3;
    }
    else if (rhs.get_suit() == SUIT_DIAMONDS) {
        rhsCardVal += 4;
    }

    if (lhsCardVal < rhsCardVal) {
        return true;
    }
    else {
        return false;
    }
    /*int rankLeft = 0;
    if (lhs.get_rank() != "Ace" && lhs.get_rank() != "Jack" && lhs.get_rank() != "Queen" && lhs.get_rank() != "King") {
        std::stringstream ss(lhs.get_rank());
        ss >> rankLeft;
    }
    int rankRight = 0;
    if (rhs.get_rank() != "Ace" && rhs.get_rank() != "Jack" && rhs.get_rank() != "Queen" && rhs.get_rank() != "King") {
        std::stringstream ss(rhs.get_rank());
        ss >> rankRight;
    }
    
    if (rankLeft != 0 && rankRight != 0) {
        if (rankLeft < rankRight) {
            return true;
        }
        else if (rankLeft == rankRight) {
            if (lhs.get_suit() == "Diamonds") {
                return false;
            }
            else if (lhs.get_suit() == "Clubs") {
                if (rhs.get_suit() == "Diamonds") {
                    return true;
                }
                else return false;
            }
            else if (lhs.get_suit() == "Hearts") {
                if (rhs.get_suit() == "Diamonds" || rhs.get_suit() == "Clubs") {
                    return true;
                }
                else return false;
            }
            else if (lhs.get_suit() == "Spades") {
                if (rhs.get_suit() == "Spades") {
                    return false;
                }
                else return true;
            }
        }
    }
    
    else if (rankLeft ==  0 && rankRight != 0) {
        return false;
    }
    else if (rankLeft != 0 && rankRight == 0) {
        return true;
    }
    else if (rankLeft == 0 && rankRight == 0) {
        if (lhs.get_suit() == "Ace") {
            if (rhs.get_suit() == "Ace") {
                if (lhs.get_suit() == "Diamonds") {
                    return false;
                }
                else if (lhs.get_suit() == "Clubs") {
                    if (rhs.get_suit() == "Diamonds") {
                        return true;
                    }
                    else return false;
                }
                else if (lhs.get_suit() == "Hearts") {
                    if (rhs.get_suit() == "Diamonds" || rhs.get_suit() == "Clubs") {
                        return true;
                    }
                    else return false;
                }
                else if (lhs.get_suit() == "Spades") {
                    if (rhs.get_suit() == "Spades") {
                        return false;
                    }
                    else return true;
                }
            }
            else return false;
        }
        else if (lhs.get_suit() == "King") {
            if (rhs.get_suit() == "Ace") {
                return true;
            }
            else return false;
        }
        else if (lhs.get_suit() == "Queen") {
            if (rhs.get_suit() == "Ace" || rhs.get_suit() == "King") {
                return true;
            }
            else return false;
        }
        else if (lhs.get_suit() == "Jack") {
            if (rhs.get_suit() == "Jack") {
                return false;
            }
            else return true;
        }
    }
    
    return false;
}

bool operator<=(const Card &lhs, const Card &rhs) {
    return operator<(lhs, rhs) || operator==(lhs, rhs);
}

bool operator>(const Card &lhs, const Card &rhs) {
    return !operator==(lhs, rhs) && !operator<(lhs, rhs);
}

bool operator>=(const Card &lhs, const Card &rhs) {
    return (!operator<(lhs, rhs)) || (operator==(lhs, rhs));
}

bool operator==(const Card &lhs, const Card &rhs) {
    return (lhs.get_suit() == rhs.get_suit()) && (lhs.get_rank() == rhs.get_rank());
}

bool operator!=(const Card &lhs, const Card &rhs) {
    return !operator==(lhs, rhs);
}

std::string Suit_next(const std::string &suit) {
    if (suit == "Hearts") {
        return "Diamonds";
    }
    else if (suit == "Diamonds") {
        return "Hearts";
    }
    else if (suit == "Clubs") {
        return "Spades";
    }
    else return "Clubs";
}

std::ostream & operator<<(std::ostream &os, const Card &card) {
    os << card.get_rank() << " of " << card.get_suit();
    return os;
}

bool Card_less(const Card &a, const Card &b, const std::string &trump) {
    if (a.is_trump(trump) && !b.is_trump(trump)) {
        return false;
    }
    else if (!a.is_trump(trump) && b.is_trump(trump)) {
        return true;
    }
    else if (a.is_trump(trump) && b.is_trump(trump)) {
        if (operator<(a, b)) {
            return true;
        }
        else return false;
    }
    else if (operator>=(a, b)) {
        return false;
    }
    
    return true;
    */

}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses both the trump suit
//  and the suit led to determine order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const Card &led_card,
               const std::string &trump) {
    if (a.is_trump(trump) && b.is_trump(trump)) {
        if (operator<(a, b)) {
            return true;
        }
        else return false;
    }
    else if (a.is_trump(trump) && !b.is_trump(trump)) {
        return false;
    }
    else if (!a.is_trump(trump) && b.is_trump(trump)) {
        return true;
    }
    else if (a.get_suit() == led_card.get_suit()) {
        return false;
    }
    else if (a.get_suit() != led_card.get_suit()) {
        if (b.get_suit() == led_card.get_suit()) {
            return true;
        }
    }
    else if (operator>=(a, b)) {
        return false;
    }
    
    return true;
    
}


// NOTE: We HIGHLY recommend you check out the operator overloading
// tutorial in the project spec (see the appendices) before implementing
// the following operator overload functions:
//   operator<<
//   operator<
//   operator<=
//   operator>
//   operator>=
//   operator==
//   operator!=
