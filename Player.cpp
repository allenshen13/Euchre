// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <iostream>
#include <string>
#include "Player.h"

Class simple:public Player{
private:
    std::vector<Card> hand;
    cont std::string name;

public: 
 
    const std::string& get_name() override {
        return name;
    }

    void add_card(const Card& c) override {
        hand.push_back(c);
    }

    bool make_trump(const Card& upcard, bool is_dealer,
        int round, std::string& order_up_suit) override {

        string trump = upcard.get_suit();
        int faceCount = 0;
        for (int i = 0; i < hand.size(); i++) {
            if (hand[i].get_suit == trump && hand[i].is_face()) {
                faceCount++;
            }
        }
        if (faceCount >= 2) {
            order_up_suit == trump;
            return true;
        }
        else {
            return false;
        }
    }

    void add_and_discard(const Card& upcard) {
        string trumpSuit = upcard.get_suit();

        int lowCard = 0;
        for (int i = 0; i < hand.size() - 1; i++) {
            if (Card_less(hand[i + 1], hand[i], trumpSuit) {
                lowCard = i + 1;
            }
        }
        hand[lowCard] = upCard;
    }

    Card lead_card(const std::string& trump) override {
        int trumpCount = 0;
        for (int i = 0; i < hand.size(); i++) {
            if (hand[i].get_suit() == trump) {
                trumpCount++
            }

        }
        
        int highCard = 0;
        if (trumpCount == hand.size()) {
            for (int i = 0; i < hand.size() - 1; i++) {
                if (Card_less(hand[i], hand[i + 1], trumpSuit) {
                    highCard = i + 1;
                }
            }
            return hand[highCard];
        }
        else {
            int lowCard = 0;
                for (int i = hand.size() - 1; i > 0; i--) {
                    if (Card_less(hand[i - 1], hand[i], trumpSuit) {
                        lowCard = i - 1;
                    }
                }
            for (int i = lowCard; i < hand.size() - 1; i++) {
                if (Card_less(hand[i], hand[i + 1], trumpSuit) {
                    if (trumpSuit != hand[i + 1]) {
                        highCard = i + 1;
                    }
                }
            }
            return hand[highCard];
        }
    }

   
    Card play_card(const Card& led_card, const std::string& trump) override {
        string ledSuit = led_card.get_suit();
        bool hasSuit = false;

        for (int i = 0; i < hand.size() - 1; i++) {
            if (hand[i].get_suit() == ledSuit) {
                hasSuit = true;
            }
        }

        if (hasSuit) {
            for (int i = 0; i < hand.size() - 1; i++) {
                if (Card_less(hand[i], hand[i + 1], trumpSuit) {
                    highCard = i + 1;
                }
            }
            return hand[highCard];
        }
        else {
            int lowCard = 0;
            for (int i = 0; i < hand.size() - 1; i++) {
                if (Card_less(hand[i + 1], hand[i], trumpSuit) {
                        lowCard = i + 1;
                }
            }
            return hand[lowCard];
        }

    }

}
Class human : public Player{
private: 
    std::vector<Card> hand;
    cont std::string name;

public: 
    const std::string& get_name() override {
        return name;
    }

    void add_card(const Card& c) override {
        hand.push_back(c);
    }

    bool make_trump(const Card& upcard, bool is_dealer,
        int round, std::string& order_up_suit) override {

    }

    void add_and_discard(const Card& upcard) {

    }

    Card lead_card(const std::string& trump) override {

    }


    Card play_card(const Card& led_card, const std::string& trump) override {


    }


}

Player * Player_factory(const std::string &name, const std::string &strategy) {
  assert(false);
}
std::ostream & operator<<(std::ostream &os, const Player &p) {
  assert(false);
}

const std::string & Player::get_name() const {
    assert(false);
    
}
virtual Card lead_card(const std::string& trump) {

}

void Player::add_card(const Card &c) {
    assert(false);
    
}
