// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Pack.h"
#include "Player.h"
#include <vector>
#include <iostream>
using namespace std;

class Game {
    
private:
    vector<Player*> players;
    Pack pack;
    int score;
    
public:
    
    void add_player(string name, string type) {
        players.push_back(Player_factory(name, type));
    }
    
    int increment_dealer(int cur_dealer) {
        cur_dealer++;
        if (cur_dealer == 4) {
            cur_dealer = 0;
        }
        
        return cur_dealer;
    }
    
    void deal(int dealer_index) {
        pack.shuffle();
        for (int i = 0; i < 2; i++) {
            if (i == 0) {
                players[dealer_index + 1]->add_card(pack.deal_one());
                players[dealer_index + 1]->add_card(pack.deal_one());
                players[dealer_index + 1]->add_card(pack.deal_one());
                players[dealer_index + 2]->add_card(pack.deal_one());
                players[dealer_index + 2]->add_card(pack.deal_one());
                players[dealer_index + 3]->add_card(pack.deal_one());
                players[dealer_index + 3]->add_card(pack.deal_one());
                players[dealer_index + 3]->add_card(pack.deal_one());
                players[dealer_index]->add_card(pack.deal_one());
                players[dealer_index]->add_card(pack.deal_one());
            }
            else if (i == 1) {
                players[dealer_index + 1]->add_card(pack.deal_one());
                players[dealer_index + 1]->add_card(pack.deal_one());
                players[dealer_index + 2]->add_card(pack.deal_one());
                players[dealer_index + 2]->add_card(pack.deal_one());
                players[dealer_index + 2]->add_card(pack.deal_one());
                players[dealer_index + 3]->add_card(pack.deal_one());
                players[dealer_index + 3]->add_card(pack.deal_one());
                players[dealer_index]->add_card(pack.deal_one());
                players[dealer_index]->add_card(pack.deal_one());
                players[dealer_index]->add_card(pack.deal_one());
            }
        }
    }
    
    
    
    
    
    
    
    
};


int main() {
    cout << "hi";
}
