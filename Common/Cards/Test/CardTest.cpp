#include "gtest/gtest.h"
#include "CardTest.h"
#include "Card.h"
#include "Hand.h"
#include "CardShoe.h"


TEST(cards, UsageTest)
{
    Card card1(Ranks::A, Suits::Spades);
    Card card2 = card1;

//    ASSERT_EQ(card1.Rank(), Ranks::A);
//    ASSERT_EQ(card1.Suit(), Suits::Spades);

    Hand hand1;
    hand1.AddCard(Card(A, Spades));

    CardShoe shoe1(4);
    CardShoe shoe2(4, 15);

    ASSERT_EQ(card1, card2);
}

TEST(cards, CardShoe)
{
    CardShoe shoe(4);
    ASSERT_EQ(shoe.GetRemainingCardCount(), 52*4);
    for (int rank = Ranks::A; rank < Ranks::HiddenRank; rank++)
    {
        for (int suit = Suits::Spades; suit < Suits::HiddenSuit; suit++)
        {

        }
    }
}

TEST(cards, card)
{
    Card card1(Ranks::A, Suits::Spades);
    Card card2 = card1;

        ASSERT_EQ(card1.Rank(), Ranks::A);
    ASSERT_EQ(card1.Suit(), Suits::Spades);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}