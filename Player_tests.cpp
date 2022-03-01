// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "unit_test_framework.h"
#include "Card.h"
#include <iostream>
//#include "euchre.cpp"
#include "Pack.h"

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
    
    Player * rishi = Player_factory("Rishi", "Simple");
    rishi->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
    rishi->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
    rishi->add_card(Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));
    rishi->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
    rishi->add_card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
    // test for right bower when all trumps in lead card
    ASSERT_EQUAL(rishi->lead_card(Card::SUIT_DIAMONDS),
                 Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
    
    delete rishi;
    
    Player * rishi2 = Player_factory("Rishi", "Simple");
    rishi2->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
    rishi2->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
    rishi2->add_card(Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));
    rishi2->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
    rishi2->add_card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
    
    //test for left bower when all trumps in lead card
    ASSERT_EQUAL(rishi2->lead_card(Card::SUIT_DIAMONDS),
                 Card(Card::RANK_JACK, Card::SUIT_HEARTS));
    
    delete rishi2;
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
                 Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
    
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
    Card new_expected2(Card::RANK_FIVE, Card::SUIT_SPADES);
    
    ASSERT_EQUAL(bob->play_card(Card(Card::RANK_ACE, Card::SUIT_DIAMONDS), "Spades"),
                 new_expected2);

    delete bob;
    
    Player * shen = Player_factory("Shen", "Simple");
    shen->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    shen->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));
    //left bower is considered trump suit
    Card expected3(Card(Card::RANK_JACK, Card::SUIT_CLUBS));
    ASSERT_EQUAL(shen->play_card(Card(), Card::SUIT_SPADES), expected3);


    delete shen;
    
    // case of left bower, right bower, and ace of trump, with non-trump led card
    // should return ace of trump since its lowest
    Player * shenal = Player_factory("Shenal", "Simple");
    shenal->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    shenal->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));
    shenal->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
    //left bower is considered trump suit
    Card expected4(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    ASSERT_EQUAL(shenal->play_card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS),
                                 Card::SUIT_SPADES), expected4);
    delete shenal;
    
    Player * shenal2 = Player_factory("Shenal", "Simple");
    shenal2->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    shenal2->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));
    //left bower is considered trump suit
    Card expected5(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    ASSERT_EQUAL(shenal2->play_card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS),
                                 Card::SUIT_SPADES), expected5);


    delete shenal2;

}
/*
TEST(game_Stuff) {
    Pack pack;
    Game g(pack, true);
    g.add_player("Amy", "Simple");
    g.add_player("Barb", "Simple");
    g.add_player("Chi", "Simple");
    g.add_player("Dab", "Simple");*/
    /*
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
    Player * bob = Player_factory("Bob", "Simple");
    Player * r = Player_factory("r", "Simple");
    Player * b = Player_factory("b", "Simple");
    Player * bb = Player_factory("Bb", "Simple");
    
    
    bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
    bob->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
    bob->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
    bob->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));
    
    r->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
    r->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
    r->add_card(Card(Card::RANK_NINE, Card::SUIT_CLUBS));
    r->add_card(Card(Card::RANK_TEN, Card::SUIT_CLUBS));
    r->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));
    
    b->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    b->add_card(Card(Card::RANK_NINE, Card::SUIT_HEARTS));
    b->add_card(Card(Card::RANK_TEN, Card::SUIT_HEARTS));
    b->add_card(Card(Card::RANK_QUEEN, Card::SUIT_CLUBS));
    b->add_card(Card(Card::RANK_KING, Card::SUIT_CLUBS));
    //bb is dealer
    bb->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
    bb->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
    bb->add_card(Card(Card::RANK_ACE, Card::SUIT_CLUBS));
    bb->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
    bb->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
    
    
    string trump = Card::SUIT_HEARTS;
    Card led_card(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_EQUAL(bob->lead_card(trump), led_card);
    
    delete r;
    delete bob;
    delete b;
    delete bb;
}*/



TEST_MAIN()
