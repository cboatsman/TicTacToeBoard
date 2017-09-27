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

TEST(TicTacToeBoardTest, newBoardIsBlank)
{
	TicTacToeBoard board;
	Piece piece;
	bool boardIsBlank = true;
	for(int i=0; i<BOARDSIZE; i++) {
		for(int j=0; j<BOARDSIZE; j++) {
			piece = board.getPiece(i,j);
			if(piece != Blank) {
				boardIsBlank = false;
				break;
			}
		}
	}
	
	ASSERT_TRUE(boardIsBlank);
}

/**
 * BUG: getPiece(int,int) contains a bug, and the following test
 *	specifically tests for said bug.
 *	
 *	EXPECTED OUTCOME: TRUE -- Piece should be equal to X (if getPiece is working)
 *	ACTUAL OUTCOME:	FALSE -- Location is blank because getPiece is calling getPiece(column,row)
 *				as opposed to getPiece(row,column)
*/
TEST(TicTacToeBoardTest, getPieceBuggy)
{
	TicTacToeBoard board;
	int row=1, column=2;
	Piece piece;
	board.placePiece(row,column); // place piece at row 1, column 2
	piece = board.getPiece(row,column);
	ASSERT_TRUE(piece == X);
}


TEST(TicTacToeBoardTest, getPieceAtLocation)
{
	TicTacToeBoard board;
	int row=0, column=0;
	Piece piece;
	board.placePiece(row,column);
	piece = board.getPiece(row,column);
	ASSERT_TRUE(piece == X);
	piece = board.getPiece(row+1,column);
	ASSERT_TRUE(piece == Blank);
}

TEST(TicTacToeBoardTest, getPieceBlank)
{
	TicTacToeBoard board;
	int row=0, column=0;
	Piece piece;
	piece = board.getPiece(row,column);
	ASSERT_TRUE(piece == Blank);
}

TEST(TicTacToeBoardTest, getPieceInvalid)
{
	TicTacToeBoard board;
	int row=BOARDSIZE+1, column=BOARDSIZE+1;
	Piece piece;
	piece = board.getPiece(row,column);
	ASSERT_TRUE(piece == Invalid);
}

TEST(TicTacToeBoardTest, placePieceOutOfBounds)
{
	TicTacToeBoard board;
	Piece piece;
	int overflow = BOARDSIZE+1;	
	piece = board.placePiece(overflow,overflow);
	ASSERT_TRUE(piece == Invalid);
}

TEST(TicTacToeBoardTest, placePieceAttemptExistingThenBlank)
{
	TicTacToeBoard board;
	int row = 0, column = 0;
	Piece piece;
	piece = board.placePiece(row,column); // X first play
	ASSERT_TRUE(piece == X);
	piece = board.placePiece(row,column); // O first attempt
	ASSERT_TRUE(piece == X);
	piece = board.placePiece(row+1,column+1); // O first play
	// assertion to verify turn did not switch back to X
	ASSERT_TRUE(piece == O);
}

TEST(TicTacToeBoardTest, placePiece)
{
	TicTacToeBoard board;
	int row = 0, column = 0;
	Piece piece;
	piece = board.placePiece(row,column);
	ASSERT_TRUE(piece == X);

}

TEST(TicTacToeBoardTest, placePieceAfterWinner)
{
	TicTacToeBoard board;
	Piece piece;
	
	board.placePiece(0,0);
	board.placePiece(2,0);
	board.placePiece(0,1);
	board.placePiece(2,1);
	board.placePiece(1,1);
	board.placePiece(2,2);

	piece = board.getWinner();
	ASSERT_TRUE(piece == O);

	board.placePiece(0,2); // currently blank spot
	piece = board.getPiece(0,2);

	ASSERT_TRUE(piece == Blank); // should be BLANK since already a winner
}

TEST(TicTacToeBoardTest, toggleTurnVerification)
{
	TicTacToeBoard board;
	int row=0, column = 0;
	Piece piece;
	piece = board.placePiece(row,column);
	ASSERT_TRUE(piece == X);
	piece = board.placePiece(row+1,column+1);
	ASSERT_TRUE(piece == O);
	piece = board.placePiece(row,column+1);
	ASSERT_TRUE(piece == X);
	piece = board.placePiece(row+1,column);
	ASSERT_TRUE(piece == O);
}

TEST(TicTacToeBoardTest, getWinnerOfFullBoardDraw)
{
	TicTacToeBoard board;
	Piece piece;
	/*
	X O X
    	O O X
	X X O
	*/
	board.placePiece(0,0);
	board.placePiece(0,1);
	board.placePiece(0,2);
	board.placePiece(1,0);
	board.placePiece(1,2);
	board.placePiece(1,1);
	board.placePiece(2,0);	
	board.placePiece(2,2);
	board.placePiece(2,1);

	piece = board.getWinner();
	ASSERT_TRUE(piece == Blank);
}

TEST(TicTacToeBoardTest, getWinnerByRowA)
{
	TicTacToeBoard board;
	Piece piece;
	/*
	X X X
	O O X
	O X O
	*/
	
	board.placePiece(0,0);
	board.placePiece(1,0);
	board.placePiece(0,1);
	board.placePiece(1,1);
	board.placePiece(0,2);
	board.placePiece(2,0);
	board.placePiece(1,2);
	board.placePiece(2,2);
	board.placePiece(2,1);

	piece = board.getWinner();
	ASSERT_TRUE(piece == X);
}

TEST(TicTacToeBoardTest, getWinnerByRowB)
{
	TicTacToeBoard board;
	Piece piece;
	/*
	X X -
	O O O
	- - X
	*/
	
	board.placePiece(0,0);
	board.placePiece(1,0);
	board.placePiece(0,1);
	board.placePiece(1,1);
	board.placePiece(2,2);
	board.placePiece(1,2);

	piece = board.getWinner();
	ASSERT_FALSE(piece == X);
	ASSERT_FALSE(piece == Blank);
	ASSERT_FALSE(piece == Invalid);
	ASSERT_TRUE(piece == O);
}

TEST(TicTacToeBoardTest, getWinnerByColC)
{
	TicTacToeBoard board;
	Piece piece;
	
	board.placePiece(0,0);
	board.placePiece(2,0);
	board.placePiece(0,1);
	board.placePiece(2,1);
	board.placePiece(1,1);
	board.placePiece(2,2);

	piece = board.getWinner();
	ASSERT_TRUE(piece == O);
}

TEST(TicTacToeBoardTest, getWinnerDiagonallyA)
{
	TicTacToeBoard board;
	Piece piece;

	board.placePiece(0,0);
	board.placePiece(0,1);
	board.placePiece(1,1);
	board.placePiece(1,2);
	board.placePiece(2,2);

	piece = board.getWinner();
	ASSERT_TRUE(piece == X);
}

TEST(TicTacToeBoardTest, getWinnerDiagonallyB)
{
	TicTacToeBoard board;
	Piece piece;

	board.placePiece(0,2);
	board.placePiece(0,1);
	board.placePiece(1,1);
	board.placePiece(1,2);
	board.placePiece(2,0);

	piece = board.getWinner();
	ASSERT_TRUE(piece == X);
}

TEST(TicTacToeBoardTest, getWinnerWhenGameIsntOver)
{
	TicTacToeBoard board;
	Piece piece;

	board.placePiece(0,0);
	board.placePiece(0,1);
	
	piece = board.getWinner();
	ASSERT_FALSE(piece == Blank);
	ASSERT_FALSE(piece == X);
	ASSERT_FALSE(piece == O);
	ASSERT_TRUE(piece == Invalid);
}
