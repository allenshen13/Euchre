// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Pack.h"
#include "unit_test_framework.h"
#include "euchre.cpp"
#include "Player.h"


#include <iostream>

using namespace std;

TEST(test_pack_default_ctor) {
   /* Pack pack;
    Card first = pack.deal_one();
    ASSERT_EQUAL(Card::RANK_NINE, first.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, first.get_suit());
    Card second = pack.deal_one();
    ASSERT_EQUAL(Card::RANK_TEN, second.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, second.get_suit());
    */
    Pack pack;
    Game g(pack, true);
    g.add_player("Amy", "Simple");
    g.add_player("Barb", "Simple");
    g.add_player("Chi", "Simple");
    g.add_player("Dab", "Simple");
    
    g.get_player(1)->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
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
    
    string trump = Card::SUIT_HEARTS;
    Card led_card(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_EQUAL(g.get_player(1)->lead_card(trump), led_card);
    
    
    
}


// Add more tests here

//TEST_MAIN()
