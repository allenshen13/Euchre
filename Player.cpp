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
                cout << name << " passes" << endl;
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
        cout << name << " passes" << endl;
        return false;
            
    }

    void add_and_discard(const Card& upcard) override {
        hand.push_back(upcard);
        string trump = upcard.get_suit();
        int index_of_lowest = 0;
        for (int i = 0; i < hand.size(); i++) {
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
        if (trumpCount == hand.size()) {
            for (int i = 0; i < hand.size(); i++) {
                if (hand[i].is_right_bower(trump)) {
                    Card c = hand[i];
                    hand.erase(hand.begin() + i);
                    return c;
                }
            }
            for (int i = 0; i < hand.size(); i++) {
                if (hand[i].is_left_bower(trump)) {
                    Card c = hand[i];
                    hand.erase(hand.begin() + i);
                    return c;
                }
            }
            for (int i = 0; i < hand.size(); i++) {
                if (handCopy[handCopy.size() - 1] == hand[i]) {
                    hand.erase(hand.begin() + i);
                }
            }
            return handCopy[handCopy.size() - 1];
        }
        else {
            sort(noTrump.begin(), noTrump.end());
            for (int i = 0; i < hand.size(); i++) {
                if (hand[i] == noTrump[noTrump.size() - 1]) {
                    hand.erase(hand.begin() + i);
                }
            }
            return noTrump[noTrump.size() - 1];
            
            }
    }

   
    Card play_card(const Card& led_card, const std::string& trump) override {
        if (hand.size() == 1) {
            Card c = hand[0];
            hand.erase(hand.begin());
            return c;
        }
        Card low;
        vector<Card> onlySuit;
        vector<Card> neither;
        for (int i = 0; i < hand.size(); i++) {
            if ((hand[i].get_suit() == led_card.get_suit(trump)) &&
                !hand[i].is_left_bower(trump)) {
                
                onlySuit.push_back(hand[i]);
            }
            if (!hand[i].is_trump(trump) &&
                hand[i].get_suit(trump) != led_card.get_suit(trump)) {
                neither.push_back(hand[i]);
            }
        }
        
        Card left_bower;
        int indexOfLeft = 20;
        if (led_card.get_suit(trump) == trump) {
            for (int i = 0; i < hand.size(); i++) {
                if (hand[i].is_right_bower(trump)) {
                    Card c = hand[i];
                    hand.erase(hand.begin() + i);
                    return c;
                }
                if (hand[i].is_left_bower(trump)) {
                    left_bower = hand[i];
                    indexOfLeft = i;
                }
            }
            if (indexOfLeft != 20) {
                hand.erase(hand.begin() + indexOfLeft);
                return left_bower;
            }
            
        }
        
        if (!onlySuit.empty()) {
            sort(onlySuit.begin(), onlySuit.end());
            for (int i = 0; i < hand.size(); i++) {
                if (hand[i] == onlySuit[onlySuit.size() - 1]) {
                    Card c = hand[i];
                    hand.erase(hand.begin() + i);
                    return c;;
                }
            }
        }
        if (neither.size() == hand.size()) {
            sort(neither.begin(), neither.end());
            for (int i = 0; i < hand.size(); i++) {
                if (hand[i] == neither[0]) {
                    hand.erase(hand.begin() + i);
                    return neither[0];
                }
            }
        }
        int lowest = 0;
        for (int i = 0; i < hand.size(); i++) {
            if (Card_less(hand[i], hand[lowest], led_card, trump)) {
                lowest = i;
            }
        }
        
        low = hand[lowest];
        hand.erase(hand.begin() + lowest);
        return low;
        
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
        
        for (int i = 0; i < handCopy.size(); i++) {
            cout << "Human player " << name << "'s hand: [" << i << "] " <<
            handCopy[i] << endl;

        }
        
        string response;
        cout << "Please select a suit, or \"pass\" ";
        cin >> response;
        
        if (response == "pass") {
            cout << name << " passes" << endl;
            return false;
        }
        else {
            order_up_suit = response;
            return true;
        }

    }

    void add_and_discard(const Card& upcard) override {
        vector<Card> cardcopy;
        
        for (int i = 0; i < hand.size(); i++) {
            cardcopy.push_back(hand[i]);
        }
        
        sort(cardcopy.begin(), cardcopy.end());
        
        for (int i = 0; i < cardcopy.size(); i++) {
            cout << "Human player " << name << "'s hand: [" << i << "] " <<
            hand[i] << endl;
        }
        int answer;
        cout << "Discard upcard: [-1]" << endl;
        cout << "please select a card to discard ";
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
        
        for (int i = 0; i < handcopy.size(); i++) {
            cout << "Human player " << name << "'s hand: [" << i << "] " <<
            handcopy[i] << endl;
        }
        
        int answer;
        cout << "Human player " << name << ", please select a card: ";
        cin >> answer;
        int index = 0;
        for (int i = 0; i < hand.size(); i++) {
            if (handcopy[answer] == hand[i]) {
                index = i;
            }
        }
        hand.erase(hand.begin() + index);
        return handcopy[answer];
    }


    Card play_card(const Card& led_card, const std::string& trump) override {
        vector<Card> handcopy;
        for (int i = 0; i < hand.size(); i++) {
            handcopy.push_back(hand[i]);
        }

        sort(handcopy.begin(), handcopy.end());
        
        for (int i = 0; i < handcopy.size(); i++) {
            cout << "Human player " << name << "'s hand: [" << i << "] " <<
            handcopy[i] << endl;
        }
        
        int answer;
        cout << "Human player " << name << ", please select a card: ";
        cin >> answer;
        int index = 0;
        for (int i = 0; i < hand.size(); i++) {
            if (handcopy[answer] == hand[i]) {
                index = i;
            }
        }
        hand.erase(hand.begin() + index);
        return handcopy[answer];
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



