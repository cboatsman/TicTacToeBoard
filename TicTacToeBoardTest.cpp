/**
 * Unit Tests for TicTacToeBoard
**/

#include <gtest/gtest.h>
#include "TicTacToeBoard.h"
 
class TicTacToeBoardTest : public ::testing::Test
{
	protected:
		TicTacToeBoardTest(){} //constructor runs before each test
		virtual ~TicTacToeBoardTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor) 
};

/* EXAMPLE TEST FORMAT
TEST(TicTacToeBoardTest, sanityCheck)
{
	ASSERT_TRUE(true);
}
*/

TEST(TicTacToeBoardTest, boardIsBlank)
{
	TicTacToeBoard board;
	Piece piece;
	for(int i=0; i<BOARDSIZE; i++) {
		for(int j=0; j<BOARDSIZE; j++) {
			piece = board.getPiece(i,j);
			ASSERT_TRUE(piece == Blank);
		}
	}
}

TEST(TicTacToeBoardTest, placeOutOfBounds)
{
	TicTacToeBoard board;
	Piece piece = O;
	int overflow = BOARDSIZE+1;	
	piece = board.placePiece(overflow,overflow);
	ASSERT_TRUE(piece == Invalid);
}

TEST(TicTacToeBoardTest, attemptPlayOnExistingSpot)
{
	TicTacToeBoard board;
	Piece piece = O;
	int row = 0, column = 0;
	piece = board.placePiece(row,column);
	piece = board.placePiece(row,column);
	ASSERT_TRUE(piece == Invalid);

}

TEST(TicTacToeBoardTest, attemptPlay)
{
	TicTacToeBoard board;
	Piece piece;
	int row = 0, column = 0;
	piece = board.placePiece(row,column);
	ASSERT_TRUE( (piece == 0) || (piece == X) );

}
