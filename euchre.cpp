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
    array<int, 2> score;
    int hand;
    bool shuffle;
    
public:
    
    Game(bool shuffle_in) : shuffle(shuffle_in) {
        score[0] = 0;
        score[1] = 0;
        hand = 0;
    }
    
    void add_player(string name, string type) {
        players.push_back(Player_factory(name, type));
    }
    
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
        if (cur_player == 4) {
            cur_player = 0;
        }
        
        return cur_player;
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
   
    //REQUIRES tricks_won >= 3
    //EFFECTS: updates score, takes in player who won trick, num tricks won in hand
    // and if the team ordered up
    
    //DOES NOT WORK
    void update_score(int team_index, int tricks_won, bool teamOrderedUp) {
        if (teamOrderedUp) {
            if (tricks_won == 5) {
                score[team_index] += 2;
            }
            else {
                score[team_index] += 1;
            }
        }
        //team didn't orderup so get 2 points regardless
        else {
            score[team_index] += 2;
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
        
        int player_index = next_player(lead_index);
        for (int i = 0; i < 3; i++) {
            tricks[player_index] = players[player_index]->play_card(led_card, trump);
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
    
    void play_hand(Game g, int dealer_index) {
        g.deal(dealer_index);
        Card upcard;
        for (int i = 0; i < 20; i++) {
            upcard = pack.deal_one();
        }
        bool is_dealer = false;
        int roundOfTrump = 1;
        string order_up_suit;
        
        //playerind needs to be player left of dealer
        int player_index = next_player(dealer_index);
        // makes trump, order_up_suit is updated
        while(!players[player_index]->
              make_trump(upcard, is_dealer, roundOfTrump, order_up_suit)) {
            player_index = next_player(player_index);
            if (player_index == dealer_index + 1) {
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
        //NEED TO DOUBLE CHECK ADD_DISCARD()
        if (roundOfTrump == 1) {
            players[dealer_index]->add_and_discard(upcard);
        }
        
        //Trump has been made
        // trick playing begins
        string trump = order_up_suit;
        //player index restarts at person left of dealer
        // need to consider after someone has one a trick what the index will be
        player_index = next_player(dealer_index);
        int winner_index;
        int trickCount = 0;
        int tricks_won[4] = {0, 0, 0, 0};
        Card led_card = players[player_index]->lead_card(trump);
        while (trickCount < 5) {
            winner_index = play_trick(player_index, led_card, trump);
            tricks_won[winner_index]++;
            trickCount++;
            //need to update led card for each trick
            player_index = winner_index;
            led_card = players[player_index]->lead_card(trump);
            //need to update hand after trick???
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
        if (teamOrderedUp) {
            if (team_tricks == 5) {
                score[team_index] = score[team_index] + 2;
            }
            else {
                score[team_index] = score[team_index] + 1;
            }
            
        }
        else {
            score[team_index] = score[team_index] + 2;
        }
        
    
    }
    

};


TEST(game_stuff) {
    Game g(false);
    g.add_player("Amy", "Simple");
    g.add_player("Barb", "Simple");
    g.add_player("Chi", "Simple");
    g.add_player("Dab", "Simple");
    
   /* g.get_player(1)->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    g.get_player(1)->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
    g.get_player(1)->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
    g.get_player(1)->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
    g.get_player(1)->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));
    
    g.get_player(2)->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
    g.get_player(2)->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
    g.get_player(2)->add_card(Card(Card::RANK_NINE, Card::SUIT_CLUBS));
    g.get_player(2)->add_card(Card(Card::RANK_TEN, Card::SUIT_CLUBS));
    g.get_player(2)->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));
    
    g.get_player(3)->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    g.get_player(3)->add_card(Card(Card::RANK_NINE, Card::SUIT_HEARTS));
    g.get_player(3)->add_card(Card(Card::RANK_TEN, Card::SUIT_HEARTS));
    g.get_player(3)->add_card(Card(Card::RANK_QUEEN, Card::SUIT_CLUBS));
    g.get_player(3)->add_card(Card(Card::RANK_KING, Card::SUIT_CLUBS));
    
    g.get_player(0)->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
    g.get_player(0)->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
    g.get_player(0)->add_card(Card(Card::RANK_ACE, Card::SUIT_CLUBS));
    g.get_player(0)->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
    g.get_player(0)->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
    */
    
    
    string trump = Card::SUIT_HEARTS;
    Card led_card(Card::RANK_JACK, Card::SUIT_SPADES);
    //ASSERT_EQUAL(g.get_player(1)->lead_card(trump), led_card);
    //ASSERT_EQUAL(g.get_player(2)->play_card(led_card, trump), Card(Card::RANK_KING, Card::SUIT_SPADES));
    
    //ASSERT_EQUAL(g.play_trick(1, led_card, trump), 3);
    //g.deal(0);
    
    g.play_hand(g, 0);
    
    
}

TEST_MAIN()

/*int main(int argc, char* argv[]) {
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
    
    
}*/

