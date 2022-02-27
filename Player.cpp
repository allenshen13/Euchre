// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <iostream>
#include <string>
#include "Player.h"
#include <vector>
using namespace std;

class SimplePlayer : public Player {
private:
    vector<Card> hand;
    const string name;

public:
    
    SimplePlayer(std::string name_in) : name(name_in) { }
 
    const std::string& get_name() const override{
        return name;
    }

    void add_card(const Card& c) override {
        hand.push_back(c);
    }
    
    bool is_same_color(const std::string &trump, const Card &c) const {
        if (trump == Card::SUIT_DIAMONDS) {
            if (c.get_suit() == Card::SUIT_HEARTS) {
                return true;
            }
        }
        else if (trump == Card::SUIT_HEARTS) {
            if (c.get_suit() == Card::SUIT_DIAMONDS) {
                return true;
            }
        }
        else if (trump == Card::SUIT_SPADES) {
            if (c.get_suit() == Card::SUIT_CLUBS) {
                return true;
            }
        }
        else if (trump == Card::SUIT_CLUBS) {
            if (c.get_suit() == Card::SUIT_SPADES) {
                return true;
            }
        }
        
        return false;
    
    }
    
    string opposite_color(const std::string &trump) const {
        if (trump == Card::SUIT_DIAMONDS) {
            return Card::SUIT_HEARTS;
        }
        else if (trump == Card::SUIT_HEARTS) {
            return Card::SUIT_DIAMONDS;
        }
        else if (trump == Card::SUIT_SPADES) {
            return Card::SUIT_CLUBS;
        }
        else return Card::SUIT_SPADES;
    
    }

    bool make_trump(const Card& upcard, bool is_dealer,
        int round, std::string& order_up_suit) const override {
        
        
        string trump = upcard.get_suit();
        int faceCount = 0;
        
        for (int i = 0; i < hand.size(); i++) {
            if (hand[i].is_trump(trump) && hand[i].is_face()) {
                faceCount++;
            }
        }
        
        if (round == 1) {
            if (faceCount >= 2) {
                order_up_suit = trump;
                return true;
            }
            else {
                return false;
            }
        }
        else if (round == 2 && !is_dealer) {
            faceCount = 0;
            for (int i = 0; i < hand.size(); i++) {
                if (is_same_color(trump, hand[i]) && hand[i].is_face()) {
                    faceCount++;
                    if (faceCount >= 1) {
                        order_up_suit = hand[i].get_suit();
                    }
                }
            }
            if (faceCount >= 1) {
                return true;
            }
        }
        
        else if (round == 2 && is_dealer) {
            order_up_suit = opposite_color(trump);
            return true;
        }
        
        return false;
            
    }

    void add_and_discard(const Card& upcard) override {
        vector<Card> handCopy;
        for (int i = 0; i < hand.size(); i++) {
            handCopy.push_back(hand[i]);
        }
        handCopy.push_back(upcard);
        sort(handCopy.begin(), handCopy.end());
        
        for (int i = 1; i < handCopy.size(); i++) {
            hand[i - 1] = handCopy[i];
            
            
        }
        
    }

    Card lead_card(const std::string& trump) override {
        vector<Card> handCopy;
        vector<Card> noTrump;
        for (int i = 0; i < MAX_HAND_SIZE; i++) {
            handCopy.push_back(hand[i]);
        }
        sort(handCopy.begin(), handCopy.end());
        
        int trumpCount = 0;
        for (int i = 0; i < hand.size(); i++) {
            if (hand[i].is_trump(trump)) {
                trumpCount++;
            }
            else {
                noTrump.push_back(hand[i]);
            }

        }
        if (trumpCount == MAX_HAND_SIZE) {
            return handCopy[MAX_HAND_SIZE - 1];
        }
        else {
            sort(noTrump.begin(), noTrump.end());
            return noTrump[noTrump.size() - 1];
            
            }
    }

   
    Card play_card(const Card& led_card, const std::string& trump) override {
        int hasSuit = 0;
        int numTrumps = 0;
        int neitherCount = 0;
        vector<Card> trumpOnly;
        vector<Card> neither;
        vector<Card> onlySuit;
        
        for (int i = 0; i < MAX_HAND_SIZE; i++) {
            if (hand[i].get_suit() == led_card.get_suit()) {
                hasSuit = 1;
                onlySuit.push_back(hand[i]);
            }
            if (hand[i].is_trump(trump)) {
                numTrumps++;
                trumpOnly.push_back(hand[i]);
            }
            if ((hand[i].get_suit() != led_card.get_suit()) && !hand[i].is_trump(trump)) {
                neither.push_back(hand[i]);
                neitherCount++;
            }
        }
        
        if (hasSuit != 0) {
            sort(onlySuit.begin(), onlySuit.end());
            return onlySuit[onlySuit.size() - 1];
        }
        else {
            if (numTrumps != 0 && neitherCount == 0) {
                sort(trumpOnly.begin(), trumpOnly.end());
                return trumpOnly[0];
            }
            else {
                sort(neither.begin(), neither.end());
                return neither[0];
            }
        }
        
    }

};

class Human : public Player {
    
private:
    vector<Card> hand;
    const string name;

public:
    
    Human(std::string name_in) : name(name_in) { }
    
    const std::string& get_name() const override {
        return name;
    }

    void add_card(const Card& c) override{
        hand.push_back(c);
    }
    
    Card find_min(vector<Card> hands, int start) {
        Card min = hands[0];
        for (int i = start; i < hands.size(); i++) {
            if (operator<(hand[i], min)) {
                min = hands[i];
            }
        }
        return min;
    }
    

    bool make_trump(const Card& upcard, bool is_dealer,
        int round, std::string& order_up_suit) const override {
        
        vector<Card> handCopy;
        for (int i = 0; i < hand.size(); i++) {
            handCopy.push_back(hand[i]);
        }

        sort(handCopy.begin(), handCopy.end());
        
        for (int i = 0; i < hand.size(); i++) {
            operator<<(cout, hand[i]);
            cout << endl;
        }
        
        string response;
        cout << "Please select a suit or \"pass\" ";
        cin >> response;
        
        if (response == "pass") {
            return false;
        }
        else {
            order_up_suit = response;
            return true;
        }

    }

    void add_and_discard(const Card& upcard) override {
        for (int i = 0; i < hand.size(); i++) {
            operator<<(cout, hand[i]);
            cout << endl;
        }
        int answer;
        cout << "Which card would you like to discard? ";
        cin >> answer;
        if (answer == -1) {
            return;
        }
        else {
            hand[answer] = upcard;
        }
    }

    Card lead_card(const std::string& trump) override {
        vector<Card> handcopy;
        for (int i = 0; i < hand.size(); i++) {
            handcopy.push_back(hand[i]);
        }

        sort(handcopy.begin(), handcopy.end());
        
        for (int i = 0; i < hand.size(); i++) {
            operator<<(cout, hand[i]);
            cout << endl;
        }
        
        int answer;
        cout << "please select a card ";
        cin >> answer;
        
        return hand[answer];
    }


    Card play_card(const Card& led_card, const std::string& trump) override {
        vector<Card> handcopy;
        for (int i = 0; i < hand.size(); i++) {
            handcopy.push_back(hand[i]);
        }

        sort(handcopy.begin(), handcopy.end());
        
        for (int i = 0; i < hand.size(); i++) {
            operator<<(cout, hand[i]);
            cout << endl;
        }
        
        int answer;
        cout << "please select a card ";
        cin >> answer;
        
        return hand[answer];
    }


};

Player * Player_factory(const std::string &name, const std::string &strategy) {
    if (strategy == "Simple") {
        return new SimplePlayer(name);
    }
    
    if (strategy == "Human") {
        return new Human(name);
    }
    
    assert(false);
    return nullptr;
}
std::ostream & operator<<(std::ostream &os, const Player &p) {
    os << p.get_name();
    return os;
}



