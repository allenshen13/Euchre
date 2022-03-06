// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Pack.h"
#include "Player.h"
#include <vector>
#include <iostream>
#include <array>
//#include "unit_test_framework.h"
#include <fstream>
#include <cstdlib>
using namespace std;

class Game {
    
private:
    vector<Player*> players;
    Pack pack;
    array<int, 2> score;
    int hand;
    bool shuffle;
    
public:
    
    Game(Pack p_in, bool shuffle_in) : pack(p_in), shuffle(shuffle_in) {
        score[0] = 0;
        score[1] = 0;
        hand = 0;
    }
    
    void add_player(string name, string type) {
        players.push_back(Player_factory(name, type));
    }
    
    //for testing only
    Player * get_player(int index) {
        return players[index];
    }
    
    int increment_dealer(int cur_dealer) {
        cur_dealer++;
        if (cur_dealer == 4) {
            cur_dealer = 0;
        }
        
        return cur_dealer;
    }
    
    int next_player(int cur_player) {
        cur_player++;
        if (cur_player >= 4) {
            cur_player = 0;
        }
        
        return cur_player;
    }

    
    void deal(int dealer_index, Pack& pack) {
        cout << *players[dealer_index];
        cout << " deals" << endl;
        if (shuffle) {
            pack.shuffle();
        }
        for (int i = 0; i < 2; i++) {
            if (i == 0) {
                int x = dealer_index;
                players[next_player(x)]->add_card(pack.deal_one());
                players[next_player(x)]->add_card(pack.deal_one());
                players[next_player(x)]->add_card(pack.deal_one());
            
                x = next_player(x);
                players[next_player(x)]->add_card(pack.deal_one());
                players[next_player(x)]->add_card(pack.deal_one());
                
                x = next_player(x);
                players[next_player(x)]->add_card(pack.deal_one());
                players[next_player(x)]->add_card(pack.deal_one());
                players[next_player(x)]->add_card(pack.deal_one());
                
                players[dealer_index]->add_card(pack.deal_one());
                players[dealer_index]->add_card(pack.deal_one());
            }
            else if (i == 1) {
                int x = dealer_index;
                players[next_player(x)]->add_card(pack.deal_one());
                players[next_player(x)]->add_card(pack.deal_one());
                
                x = next_player(x);
                players[next_player(x)]->add_card(pack.deal_one());
                players[next_player(x)]->add_card(pack.deal_one());
                players[next_player(x)]->add_card(pack.deal_one());
                
                x = next_player(x);
                players[next_player(x)]->add_card(pack.deal_one());
                players[next_player(x)]->add_card(pack.deal_one());
                
                players[dealer_index]->add_card(pack.deal_one());
                players[dealer_index]->add_card(pack.deal_one());
                players[dealer_index]->add_card(pack.deal_one());
            }
        }
        
    }

    //EFFECTS: Checks if a team as won the game
    bool has_won(int points_needed) {
        return (score[0] >= points_needed) || (score[1] >= points_needed);
    }
    
    // EFFECTS: (lead index is decided by who won the last trick)
    // Adds players play_card to their respective index in <players>
    // Plays out trick and Returns player who won the trick
    
    int play_trick(int lead_index, Card led_card, string trump) {
        Card tricks[4];
        tricks[lead_index] = led_card;
        //CHECK THIS
        //DealerIndex = 1, player[3] hand doesnt get fully deleted
        int player_index = next_player(lead_index);
        for (int i = 0; i < 3; i++) {
            tricks[player_index] = players[player_index]->play_card(led_card, trump);
            cout << tricks[player_index] << " played by " <<
            players[player_index]->get_name() << endl;
            player_index = next_player(player_index);
        }
    
        //now compare to see which card in tricks is highest
        // take into account which player won
        int highest_index = 0;
        for (int i = 0; i < 4; i++) {
            if (Card_less(tricks[highest_index], tricks[i], led_card, trump)) {
                highest_index = i;
            }
        }
        // index of winning player
        return highest_index;
        
    }
    
    int orderUp(int dealer_index, Card upcard, bool is_dealer,
                 string &order_up_suit) {
        int roundOfTrump = 1;
        int player_index = next_player(dealer_index);
        // makes trump, order_up_suit is updated
        int turn = 0;
        while(!players[player_index]->
              make_trump(upcard, is_dealer, roundOfTrump, order_up_suit)) {
            cout << *players[player_index] << " passes" << endl;
            player_index = next_player(player_index);
            turn++;
            if (turn == 4) {
                roundOfTrump++;
            }
            // checks if player is the dealer
            if (player_index == dealer_index) {
                is_dealer = true;
            }
            else {
                is_dealer = false;
            }

        }
        
        // ordered_up_index shows which team ordered up
        int ordered_up_index = player_index;
        cout << players[ordered_up_index]->get_name() << " orders up " << order_up_suit
        << endl << endl;
        
        //NEED TO DOUBLE CHECK ADD_DISCARD()
        if (roundOfTrump == 1) {
            players[dealer_index]->add_and_discard(upcard);
        }
        
        return ordered_up_index;
    }
    
    void print_score_updates(Game &g, bool teamOrderedUp, int teamIndex,
                             int team_tricks) {
        if (teamIndex == 0) {
            cout << players[0]->get_name() << " and " << players[2]->get_name()
            << " win the hand" << endl;
        }
        else {
            cout << players[1]->get_name() << " and " << players[3]->get_name()
            << " win the hand" << endl;
        }
            
        if (teamOrderedUp) {
            if (team_tricks == 5) {
                cout << "march!" << endl;
                score[teamIndex] = score[teamIndex] + 2;
                
            }
            else {
                score[teamIndex] = score[teamIndex] + 1;
            }
        }
        else {
            cout << "euchred!" << endl;
            score[teamIndex] = score[teamIndex] + 2;
        }
        cout << players[0]->get_name() << " and " << players[2]->get_name() << " have "
        << score[0] << " points" << endl;
        cout << players[1]->get_name() << " and " << players[3]->get_name() << " have "
        << score[1] << " points" << endl << endl;
        
    }
    
    Card dealOut(Game &g, int dealer_index) {
        g.deal(dealer_index, pack);
        const Card upcard = pack.deal_one();
        cout << upcard << " turned up" << endl;
        pack.reset();
        return upcard;
    }
    
    void play_hand(Game &g, int dealer_index) {
        Card upcard = dealOut(g, dealer_index);
        bool is_dealer = false;
        string order_up_suit;
        int ordered_up_index;
        ordered_up_index = orderUp(dealer_index, upcard, is_dealer, order_up_suit);
        
        string trump = order_up_suit;
        int player_index = next_player(dealer_index);
        int winner_index;
        int trickCount = 0;
        int tricks_won[4] = {0, 0, 0, 0};
        
        Card led_card;
        while (trickCount < 5) {
            led_card = players[player_index]->lead_card(trump);
            cout << led_card;
            cout << " led by " << players[player_index]->get_name() << endl;
            winner_index = play_trick(player_index, led_card, trump);
            cout << players[winner_index]->get_name() << " takes the trick\n" << endl;
            tricks_won[winner_index]++;
            trickCount++;
            //need to update led card for each trick
            player_index = winner_index;
        }
        
        // sees which team won the hand
        bool teamOrderedUp = false;
        int team_index;
        int team_tricks;
        if ((tricks_won[0] + tricks_won[2]) > (tricks_won[1] + tricks_won[3])) {
            team_tricks = (tricks_won[0] + tricks_won[2]);
            team_index = 0;
            if (ordered_up_index == 0 || ordered_up_index == 2) {
                teamOrderedUp = true;
            }
        }
        else {
            team_tricks = (tricks_won[1] + tricks_won[3]);
            team_index = 1;
            if (ordered_up_index == 1 || ordered_up_index == 3) {
                teamOrderedUp = true;
            }
        }
        
        print_score_updates(g, teamOrderedUp, team_index, team_tricks);
        
 
    }
    
    int get_winner() {
        if (score[0] > score[1]) {
            return 0;
        }
        
        return 1;
    }
  
    void play_game(Game g, int points_to_win) {
        int dealer_index = 0;
        int hand_count = 0;
        while (!has_won(points_to_win)) {
            cout << "Hand " << hand_count << endl;
            play_hand(g, dealer_index);
            dealer_index = increment_dealer(dealer_index);
            hand_count++;
        }
        
        if (get_winner() == 0) {
            cout << players[0]->get_name() << " and " << players[2]->get_name()
            << " win!" << endl;
        }
        else {
            cout << players[1]->get_name() << " and " << players[3]->get_name()
            << " win!" << endl;
        }
        
        for (int i = 0; i < int(players.size()); ++i) {
            delete players[i];
        }
    }

};


int main(int argc, char* argv[]) {
    if (argc != 12) {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
        "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 NAME4 TYPE4";
    }
    for (int i = 0; i < argc; i++) {
        cout << argv[i] << " ";
    }
    cout << endl;
    string p1(argv[5]), p2(argv[7]), p3(argv[9]), p4(argv[11]), shuffle(argv[2]);
    if (!((shuffle == "shuffle" || shuffle == "noshuffle") &&
        (p1 == "Human" || p1 == "Simple") && (p2 == "Human" || p2 == "Simple") &&
        (p3 == "Human" || p3 == "Simple") && (p4 == "Human" || p4 == "Simple")
          && (atoi(argv[3]) >= 1 && atoi(argv[3]) <= 100))) {
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
    Pack p(is);
    bool shuff = true;
    if (shuffle == "noshuffle") {
        shuff = false;
    }
    Game g(p, shuff);
    for (int i = 4; i <= 10; i += 2) {
        g.add_player(argv[i], argv[i + 1]);
    }
    g.play_game(g, atoi(argv[3]));
}
