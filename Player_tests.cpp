// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "unit_test_framework.h"
#include "Card.h"
#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());
    delete alice;
    
    Player * h = Player_factory("h", "Human");
    ASSERT_EQUAL("h", h->get_name());
    delete h;
    
}

TEST(test_player_make_trump) {
    Player * alice = Player_factory("Alice", "Simple");
    alice->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
    alice->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));
    alice->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    alice->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
    alice->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
    Card upcard(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    string order_up_suit;
    ASSERT_TRUE(alice->make_trump(upcard, false, 2, order_up_suit));
    ASSERT_EQUAL(order_up_suit, Card::SUIT_HEARTS);
    ASSERT_FALSE(alice->make_trump(upcard, false, 1, order_up_suit));
    order_up_suit = "hello";
    ASSERT_TRUE(alice->make_trump(upcard, true, 2, order_up_suit));
    ASSERT_EQUAL(Card::SUIT_HEARTS, order_up_suit);
    ASSERT_FALSE(alice->make_trump(upcard, true, 1, order_up_suit));
    
    delete alice;
    
    
}

TEST(test_player_add_discard) {
    Player * alice = Player_factory("Alice", "Simple");
    alice->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
    alice->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));
    alice->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    alice->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
    alice->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
    
    alice->add_and_discard(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
    

    delete alice;
}

TEST(test_player_lead_card) {
    Player * alice = Player_factory("Alice", "Simple");
    alice->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
    alice->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));
    alice->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    alice->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
    alice->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
    Card expected(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(alice->lead_card(Card::SUIT_SPADES), expected);
    Card new_expected(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_EQUAL(alice->lead_card(Card::SUIT_HEARTS), new_expected);
    
    delete alice;
}

TEST(test_player_play_card) {
    Player * alice = Player_factory("Alice", "Simple");
    alice->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
    alice->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
    alice->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    alice->add_card(Card());
    alice->add_card(Card(Card::RANK_FIVE, Card::SUIT_CLUBS));
    
    ASSERT_EQUAL(alice->play_card(Card(Card::RANK_TEN, Card::SUIT_HEARTS),
                                  "Diamonds"), Card());
    Card expected(Card::RANK_ACE, Card::SUIT_SPADES);
    ASSERT_EQUAL(alice->play_card(Card(Card::RANK_TEN, Card::SUIT_SPADES), "Clubs"),
                 expected);

    ASSERT_EQUAL(alice->play_card(Card(Card::RANK_SIX, Card::SUIT_HEARTS), "Hearts"),
                 Card());
    
    delete alice;
    
    Player * bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
    bob->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
    bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    bob->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
    bob->add_card(Card(Card::RANK_FIVE, Card::SUIT_SPADES));
    
    Card new_expected(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(bob->play_card(Card(Card::RANK_ACE, Card::SUIT_CLUBS), "Spades"),
                 new_expected);
    ASSERT_EQUAL(bob->play_card(Card(Card::RANK_ACE, Card::SUIT_SPADES), "Diamonds"),
                 expected);
    Card new_expected2(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(bob->play_card(Card(Card::RANK_ACE, Card::SUIT_DIAMONDS), "Spades"),
                 new_expected2);
    
    
    delete bob;
}



TEST_MAIN()
