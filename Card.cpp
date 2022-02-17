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
    if (trump == "Diamonds") {
        if (this->suit == "Hearts" && this->rank == "Jack") {
            return "Diamonds";
        }
    }
    else if (trump == "Hearts") {
        if (this->suit == "Diamonds" && this->rank == "Jack") {
            return "Hearts";
        }
    }
    else if (trump == "Spades") {
        if (this->suit == "Clubs" && this->rank == "Jack") {
            return "Spades";
        }
    }
    else if (trump == "Clubs") {
        if (this->suit == "Spades" && this->rank == "Jack") {
            return "Clubs";
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
    int rankLeft = 0;
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
}

bool Card_less(const Card &a, const Card &b, const Card &led_card,
               const std::string &trump) {
    assert(false);
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
