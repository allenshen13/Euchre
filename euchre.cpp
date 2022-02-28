// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Pack.h"
#include "Player.h"
#include <vector>
#include <iostream>
#include <array>
#include "unit_test_framework.h"
#include <fstream>
#include <cstdlib>
using namespace std;

class Game {
    
private:
    vector<Player*> players;
    Pack pack;
    array<int, 4> score;
    int hand;
    bool shuffle;
    
public:
    
    Game(Pack p, bool shuffle_in) : pack(p), shuffle(shuffle_in) {
        for (int i = 0; i < 4; i++) {
            score[i] = 0;
        }
        hand = 0;
    }
    
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
        if (shuffle) {
            pack.shuffle();
        }
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
    
    Player * win_trick(vector<Card> tricks, vector<Player*> playerTricks, string trump,
                       Card led_card) {
        for (int i = 0; i < 4; i++) {
            if (tricks[i].is_right_bower(trump)) {
                return playerTricks[i];
            }
        }
        for (int i = 0; i < 4; i++) {
            if (tricks[i].is_left_bower(trump)) {
                return playerTricks[i];
            }
        }
        
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (j > i) {
                    if (!Card_less(tricks[i], tricks[j], led_card, trump)) {
                        Card temp = tricks[i];
                        tricks[i] = tricks[j];
                        tricks[j] = temp;
                        Player * temp2 = playerTricks[i];
                        playerTricks[i] = playerTricks[j];
                        playerTricks[j] = temp2;
                    }
                }
            }
        }
        
        return playerTricks[3];
    }
    
    //REQUIRES tricks_won >= 3
    //EFFECTS: updates score, takes in player who won trick, num trucks won in hand
    // and if the team ordered up
    void update_score(Player * won_trick, int tricks_won, bool teamOrderedUp) {
        assert(tricks_won >= 3);
        int index = 0;
        for (int i = 0; i < 4; i++) {
            if (players[i] == won_trick) {
                index = i;
            }
        }
        
        if (teamOrderedUp) {
            if (tricks_won == 5) {
                score[index] += 2;
            }
            else {
                score[index] += 1;
            }
            
        }
        else {
            score[index] += 2;
        }
        
        hand++;
    }
    
    //EFFECTS: Checks if a team as won the game
    bool has_won(int points_needed) {
        return ((score[1] + score[3]) >= points_needed ||
                (score[2] + score[4]) >= points_needed);
    }
    

};


int main(int argc, char* argv[]) {
    if (!strcmp(argv[2], "shuffle") || !strcmp(argv[2], "noshuffle") || argc != 12 ||
        (atoi(argv[3]) < 1 || atoi(argv[3]) > 100) || !strcmp(argv[5], "Simple") ||
        !strcmp(argv[5], "Human") || !strcmp(argv[7], "Simple") ||
        !strcmp(argv[7], "Human") || !strcmp(argv[9], "Simple") ||
        !strcmp(argv[9], "Human") || !strcmp(argv[11], "Simple") ||
        !strcmp(argv[11], "Human")) {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
             << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
             << "NAME4 TYPE4" << endl;
        return 1;
    }
    ifstream is(argv[1]);
    if (!is.is_open()) {
        cout << "Error opening " << argv[1] << endl;
        return 1;
    }
    bool shuff = true;
    Pack p(is);
    if (strcmp(argv[2], "noshuffle")) {
        shuff = false;
    }
    Game g(is, shuff);
    for (int i = 4; i <= 10; i += 2) {
        g.add_player(argv[i], argv[i + 1]);
    }
    while (!g.has_won(atoi(argv[3]))) {
        int dealer = 0;
        g.deal(dealer);
        
        
    }
    
    
    

    
    
  //  int points_to_win = argv[3];
    
    
}
