// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "unit_test_framework.h"
#include <iostream>

using namespace std;


TEST(test_card_ctor) {
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::RANK_ACE, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, c.get_suit());
    ASSERT_EQUAL(Card::SUIT_HEARTS, c.get_suit(Card::SUIT_DIAMONDS));
    
    Card c2(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::SUIT_DIAMONDS, c2.get_suit(Card::SUIT_DIAMONDS));
    
    Card c3(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(Card::SUIT_HEARTS, c3.get_suit(Card::SUIT_HEARTS));
    
    Card c4(Card::RANK_JACK, Card::SUIT_CLUBS);
    ASSERT_EQUAL(Card::SUIT_SPADES, c4.get_suit(Card::SUIT_SPADES));
    
    Card c5(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_EQUAL(Card::SUIT_CLUBS, c5.get_suit(Card::SUIT_CLUBS));
    ASSERT_TRUE(c5.is_face());
    
    Card c6(Card::RANK_SIX, Card::SUIT_SPADES);
    ASSERT_EQUAL(Card::SUIT_SPADES, c6.get_suit(Card::SUIT_DIAMONDS));
    
    Card c7(Card::RANK_ACE, Card::SUIT_CLUBS);
    ASSERT_FALSE(c7.is_face());
    
    Card c8(Card::RANK_KING, Card::SUIT_HEARTS);
    ASSERT_TRUE(c8.is_face());
}

TEST(test_card_get_rank_suit) {
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(c.get_rank(), Card::RANK_ACE);
    
}

TEST(test_get_suit_trump) {
    Card c(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(c.get_suit(Card::SUIT_HEARTS), Card::SUIT_HEARTS);

}

TEST(test_is_right_bower) {
    Card c(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    ASSERT_TRUE(c.is_right_bower(Card::SUIT_DIAMONDS));
    ASSERT_FALSE(c.is_right_bower(Card::SUIT_HEARTS));
    ASSERT_FALSE(c.is_right_bower(Card::SUIT_CLUBS));
    ASSERT_FALSE(c.is_right_bower(Card::SUIT_SPADES));

    Card c1(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    ASSERT_FALSE(c1.is_right_bower(Card::SUIT_DIAMONDS));
    ASSERT_FALSE(c1.is_right_bower(Card::SUIT_HEARTS));
    ASSERT_FALSE(c1.is_right_bower(Card::SUIT_CLUBS));
    ASSERT_FALSE(c1.is_right_bower(Card::SUIT_SPADES));

    Card c2(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    ASSERT_FALSE(c2.is_right_bower(Card::SUIT_DIAMONDS));
    ASSERT_FALSE(c2.is_right_bower(Card::SUIT_HEARTS));
    ASSERT_FALSE(c2.is_right_bower(Card::SUIT_CLUBS));
    ASSERT_FALSE(c2.is_right_bower(Card::SUIT_SPADES));

}

TEST(test_is_left_bower) {
    Card c(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    ASSERT_TRUE(c.is_left_bower(Card::SUIT_HEARTS));
    ASSERT_FALSE(c.is_left_bower(Card::SUIT_DIAMONDS));
    ASSERT_FALSE(c.is_left_bower(Card::SUIT_CLUBS));
    ASSERT_FALSE(c.is_left_bower(Card::SUIT_SPADES));

    Card c1(Card::RANK_JACK, Card::SUIT_CLUBS);
    ASSERT_TRUE(c1.is_left_bower(Card::SUIT_SPADES));
    ASSERT_FALSE(c1.is_left_bower(Card::SUIT_DIAMONDS));
    ASSERT_FALSE(c1.is_left_bower(Card::SUIT_CLUBS));
    ASSERT_FALSE(c1.is_left_bower(Card::SUIT_HEARTS));

    Card c2(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    ASSERT_FALSE(c2.is_left_bower(Card::SUIT_DIAMONDS));
    ASSERT_FALSE(c2.is_left_bower(Card::SUIT_CLUBS));
    ASSERT_FALSE(c2.is_left_bower(Card::SUIT_HEARTS));
    ASSERT_FALSE(c2.is_left_bower(Card::SUIT_HEARTS));

}

TEST(test_less_than_operator) {
    Card c(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card c1(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_TRUE(operator<(c1, c));


    Card c2(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card c3(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_TRUE(operator<(c2, c3));


    Card c4(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card c5(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_TRUE(operator<(c4, c5));


    Card c6(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    Card c7(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_TRUE(operator<(c6, c7));

    Card c8(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card c9(Card::RANK_TEN, Card::SUIT_HEARTS);
    ASSERT_FALSE(operator<(c8, c9));
    


}

TEST(test_less_than_equal_operator) {
    Card c(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card c1(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_TRUE(operator<=(c1, c));


    Card c2(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card c3(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_TRUE(operator<=(c2, c3));


    Card c4(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card c5(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_TRUE(operator<=(c4, c5));


    Card c6(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    Card c7(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_TRUE(operator<=(c6, c7));

    Card c8(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card c9(Card::RANK_TEN, Card::SUIT_HEARTS);
    ASSERT_TRUE(operator<=(c8, c9));
}
TEST(test_greater_than_operator) {
    Card c(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card c1(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_FALSE(operator>(c1, c));


    Card c2(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card c3(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_FALSE(operator>(c2, c3));


    Card c4(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card c5(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_FALSE(operator>(c4, c5));


    Card c6(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    Card c7(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_FALSE(operator>(c6, c7));

    Card c8(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card c9(Card::RANK_TEN, Card::SUIT_HEARTS);
    ASSERT_FALSE(operator>(c8, c9));
}

TEST(test_greater_than_equal_operator) {
    Card c(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card c1(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_FALSE(operator>=(c1, c));


    Card c2(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card c3(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_FALSE(operator>=(c2, c3));


    Card c4(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card c5(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_FALSE(operator>=(c4, c5));


    Card c6(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    Card c7(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_FALSE(operator>=(c6, c7));

    Card c8(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card c9(Card::RANK_TEN, Card::SUIT_HEARTS);
    ASSERT_TRUE(operator>=(c8, c9));
}
TEST(test_equal_operator) {
    Card c(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card c1(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_FALSE(operator==(c1, c));


    Card c2(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card c3(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    ASSERT_TRUE(operator==(c2, c3));

    Card c4(Card::RANK_KING, Card::SUIT_DIAMONDS);
    Card c5(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    ASSERT_FALSE(operator==(c4, c5));
}

TEST(test_not_equal_operator) {
    Card c(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card c1(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_TRUE(operator!=(c1, c));


    Card c2(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card c3(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    ASSERT_FALSE(operator!=(c2, c3));

    Card c4(Card::RANK_KING, Card::SUIT_DIAMONDS);
    Card c5(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    ASSERT_TRUE(operator!=(c4, c5));
}
TEST(test_card_less) {
    Card c(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card c1(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_TRUE(Card_less(c, c1, Card::SUIT_HEARTS));
    ASSERT_TRUE(Card_less(c, c1, Card::SUIT_DIAMONDS));

    Card c2(Card::RANK_KING, Card::SUIT_DIAMONDS);
    Card c3(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    ASSERT_TRUE(Card_less(c2, c3, Card::SUIT_DIAMONDS));
    ASSERT_TRUE(Card_less(c2, c3, Card::SUIT_HEARTS));

    Card c4(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card c5(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    ASSERT_TRUE(Card_less(c4, c5, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(c4, c5, Card::SUIT_DIAMONDS))

    Card c6(Card::RANK_NINE, Card::SUIT_HEARTS);
    Card c7(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    ASSERT_TRUE(Card_less(c6, c7, Card::SUIT_CLUBS));
    ASSERT_TRUE(Card_less(c6, c7, Card::SUIT_DIAMONDS))

}
TEST(test_card_less_led) {
    Card c(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card c1(Card::RANK_JACK, Card::SUIT_SPADES);
    Card led(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    ASSERT_TRUE(Card_less(c, c1, led, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(c, c1, led, Card::SUIT_CLUBS));

    Card c2(Card::RANK_ACE, Card::SUIT_CLUBS);
    Card c3(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    Card led2(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    ASSERT_TRUE(Card_less(c2, c3, led2, Card::SUIT_SPADES));
    ASSERT_FALSE(Card_less(c2, c3, led2, Card::SUIT_CLUBS));

    Card c4(Card::RANK_ACE, Card::SUIT_SPADES);
    Card c5(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card led3(Card::RANK_NINE, Card::SUIT_SPADES);
    ASSERT_TRUE(Card_less(c4, c5, led3, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(c4, c5, led3, Card::SUIT_CLUBS));

    Card c6(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card c7(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card led4(Card::RANK_NINE, Card::SUIT_SPADES);
    ASSERT_TRUE(Card_less(c6, c7, led4, Card::SUIT_HEARTS));
    ASSERT_FALSE(Card_less(c6, c7, led4, Card::SUIT_SPADES));

}
// Add more test cases here

TEST_MAIN()
