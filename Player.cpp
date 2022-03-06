// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <iostream>
#include <string>
#include "Player.h"
#include <vector>
#include <cassert>
#include <algorithm>
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
    

    bool make_trump(const Card& upcard, bool is_dealer,
        int round, std::string& order_up_suit) const override {
        
        string trump = upcard.get_suit();
        int faceCount = 0;
        
        for (int i = 0; i < int(hand.size()); i++) {
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
                //cout << name << " passes" << endl;
                return false;
            }
        }
    
        
        faceCount = 0;
        for (int i = 0; i < int(hand.size()); i++) {
            if (round == 2 && !is_dealer && is_same_color(trump, hand[i]) &&
                hand[i].is_face()) {
                faceCount++;
                if (faceCount >= 1) {
                    order_up_suit = hand[i].get_suit();
                }
            }
        }
        if (faceCount >= 1) {
            return true;
        }
        
        else if (round == 2 && is_dealer) {
            order_up_suit = Suit_next(trump);
            return true;
        }
        //cout << name << " passes" << endl;
        return false;
            
    }

    void add_and_discard(const Card& upcard) override {
        hand.push_back(upcard);
        string trump = upcard.get_suit();
        int index_of_lowest = 0;
        for (int i = 0; i < int(hand.size()); i++) {
            if (Card_less(hand[i], hand[index_of_lowest], trump)) {
                index_of_lowest = i;
            }
        }
        hand.erase(hand.begin() + index_of_lowest);
        
    }

    Card lead_card(const std::string& trump) override {
        if (hand.size() == 1) {
            Card c = hand[0];
            hand.erase(hand.begin());
            return c;
        }
        vector<Card> handCopy;
        vector<Card> noTrump;
        for (int i = 0; i < int(hand.size()); i++) {
            handCopy.push_back(hand[i]);
        }
        sort(handCopy.begin(), handCopy.end());
        
        int trumpCount = 0;
        for (int i = 0; i < int(hand.size()); i++) {
            if (hand[i].is_trump(trump)) {
                trumpCount++;
            }
            else {
                noTrump.push_back(hand[i]);
            }

        }
        if (trumpCount == int(hand.size())) {
            for (int i = 0; i < int(hand.size()); i++) {
                if (hand[i].is_right_bower(trump)) {
                    Card c = hand[i];
                    hand.erase(hand.begin() + i);
                    return c;
                }
            }
            for (int i = 0; i < int(hand.size()); i++) {
                if (hand[i].is_left_bower(trump)) {
                    Card c = hand[i];
                    hand.erase(hand.begin() + i);
                    return c;
                }
            }
            for (int i = 0; i < int(hand.size()); i++) {
                if (handCopy[handCopy.size() - 1] == hand[i]) {
                    hand.erase(hand.begin() + i);
                }
            }
            return handCopy[handCopy.size() - 1];
        }
        else {
            sort(noTrump.begin(), noTrump.end());
            for (int i = 0; i < int(hand.size()); i++) {
                if (hand[i] == noTrump[noTrump.size() - 1]) {
                    hand.erase(hand.begin() + i);
                }
            }
            return noTrump[noTrump.size() - 1];
            
            }
    }

   
    Card play_card(const Card& led_card, const std::string& trump) override {
        vector<Card> sorted;
        for (int i = 0; i < int(hand.size()); i++) {
            sorted.push_back(hand[i]);
        }
        for (int i = 0; i < int(sorted.size()); i++) {
            for (int j = i + 1; j < int(sorted.size()); j++) {
                if (Card_less(sorted[j], sorted[i], led_card, trump)) {
                    Card temp = sorted[i];
                    sorted[i] = sorted[j];
                    sorted[j] = temp;
                }
            }
        }
        int suit_ind = 6;
        int index = 0;
        for (int i = 0; i < int(sorted.size()); i++) {
            if (sorted[i].get_suit(trump) == led_card.get_suit(trump)) {
                suit_ind = i;
            }
        }
        if (suit_ind != 6) {
            for (int i = 0; i < int(hand.size()); i++) {
                if (hand[i] == sorted[suit_ind]) {
                    index = i;
                    hand.erase(hand.begin() + index);
                    return sorted[suit_ind];
                }
            }
        }
        for (int i = 0; i < int(hand.size()); i++) {
            if (hand[i] == sorted[0]) {
                index = i;
            }
        }
        hand.erase(hand.begin() + index);
        return sorted[0];
        
        
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
    
    bool make_trump(const Card& upcard, bool is_dealer,
        int round, std::string& order_up_suit) const override {
        
        vector<Card> handCopy;
        for (int i = 0; i < int(hand.size()); i++) {
            handCopy.push_back(hand[i]);
        }

        sort(handCopy.begin(), handCopy.end());
        
        for (int i = 0; i < int(handCopy.size()); i++) {
            cout << "Human player " << name << "'s hand: [" << i << "] " <<
            handCopy[i] << endl;

        }
        
        string response;
        cout << "Human player " << name << ", please enter a suit, or \"pass\":" << endl;
        cin >> response;
        
        if (response == "pass") {
            //cout << name << " passes" << endl;
            return false;
        }
        else {
            order_up_suit = response;
            return true;
        }

    }

    void add_and_discard(const Card& upcard) override {
        vector<Card> cardcopy;
        
        for (int i = 0; i < int(hand.size()); i++) {
            cardcopy.push_back(hand[i]);
        }
        
        sort(cardcopy.begin(), cardcopy.end());
        
        for (int i = 0; i < int(cardcopy.size()); i++) {
            cout << "Human player " << name << "'s hand: [" << i << "] " <<
            cardcopy[i] << endl;
        }
        int answer;
        cout << "Discard upcard: [-1]" << endl;
        cout << "Human player " << name;
        cout << ", please select a card to discard:" << endl;
        cin >> answer;
        if (answer == -1) {
            return;
        }
        else {
            for (int i = 0; i < int(hand.size()); i++) {
                if (cardcopy[answer] == hand[i]) {
                    hand.erase(hand.begin() + i);
                }
            }
            hand.push_back(upcard);
        }
    }

    Card lead_card(const std::string& trump) override {
        vector<Card> handcopy;
        for (int i = 0; i < int(hand.size()); i++) {
            handcopy.push_back(hand[i]);
        }

        sort(handcopy.begin(), handcopy.end());
        
        for (int i = 0; i < int(handcopy.size()); i++) {
            cout << "Human player " << name << "'s hand: [" << i << "] " <<
            handcopy[i] << endl;
        }
        
        int answer;
        cout << "Human player " << name << ", please select a card:" << endl;
        cin >> answer;
        int index = 0;
        for (int i = 0; i < int(hand.size()); i++) {
            if (handcopy[answer] == hand[i]) {
                index = i;
            }
        }
        hand.erase(hand.begin() + index);
        return handcopy[answer];
    }


    Card play_card(const Card& led_card, const std::string& trump) override {
        vector<Card> copy;
        
        for (int i = 0; i < int(hand.size()); i++) {
            copy.push_back(hand[i]);
        }
        sort(copy.begin(), copy.end());
        for (int i = 0; i < int(copy.size()); i++) {
            cout << "Human player " << name << "'s hand: [" << i << "] " <<
            copy[i] << endl;
        }
        
        int answer;
        cout << "Human player " << name << ", please select a card:" << endl;
        cin >> answer;
        int index = 0;
        for (int i = 0; i < int(hand.size()); i++) {
            if (copy[answer] == hand[i]) {
                index = i;
            }
        }
        hand.erase(hand.begin() + index);
        return copy[answer];
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




