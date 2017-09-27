#include <vector>
#include "TicTacToeBoard.h"

using std::vector;
/**
 * Class for representing a 3x3 Tic-Tac-Toe game board, using the Piece enum
 * to represent the spaces on the board.
**/

//Constructor sets an empty board and specifies it is X's turn first
TicTacToeBoard::TicTacToeBoard()
{
  turn = X;
  for(int i=0; i<BOARDSIZE; i++)
    for(int j=0; j<BOARDSIZE; j++)
      board[i][j] = Blank;
}

/**
 * Switches turn member variable to represent whether it's X's or O's turn
 * and returns whose turn it is
**/
Piece TicTacToeBoard::toggleTurn()
{
	if(turn == X) {
		turn = O;
	} else {
		turn = X;
	}
  return turn;
}

/**
 * Places the piece of the current turn on the board, returns what
 * piece is placed, and toggles which Piece's turn it is. placePiece does 
 * NOT allow to place a piece in a location where there is already a piece.
 * In that case, placePiece just returns what is already at that location. 
 * Out of bounds coordinates return the Piece Invalid value. When the game
 * is over, no more pieces can be placed so attempting to place a piece
 * should neither change the board nor change whose turn it is.
**/ 
Piece TicTacToeBoard::placePiece(int row, int column)
{
	Piece piece;
	piece = getPiece(row,column);

	if ( piece == Invalid ) { // out of bounds
		return Invalid;
	}
	else
	{
		if ( piece == Blank ) { // valid location

			// check for winner first
			Piece winner = getWinner();

			if ( winner == Blank ) {
				return Blank;
			}
			
			board[row][column] = turn;
			piece = turn;
			toggleTurn();
			
		}
	}	

	return piece;
}

/**
 * Returns what piece is at the provided coordinates, or Blank if there
 * are no pieces there, or Invalid if the coordinates are out of bounds
**/

/**
 * BUG: getPiece(int,int) contains a bug where the following code is wrong:
 * 	Piece piece = board[column][row];
 *
 *	The board is expecting to receive [row][column] but is instead
 *	receiving a column value for the intended row, and likewise a row
 *	value for the intended column.  This causes some (but not all) of my
 *	test cases to fail.
 *	
 *	EXAMPLE: 		getPiece(2,1) is called
 *	EXPECTED RETURN:	piece = board[2][1];
 *	ACTUAL RETURN:		piece = board[1][2];
 *
**/
Piece TicTacToeBoard::getPiece(int row, int column)
{
	if (!((row >= 0 && row < BOARDSIZE) && (column >= 0 && column < BOARDSIZE))) {
		return Invalid;
	}
	
	Piece piece = board[column][row];
  	return piece;
}

/**
 * Returns which Piece has won, if there is a winner, Invalid if the game
 * is not over, or Blank if the board is filled and no one has won.
**/
Piece TicTacToeBoard::getWinner()
{
	// Check winning conditions
	int playerX;
	int playerO;
	Piece winningPiece = Invalid;
	bool winner = false;

	// First we define and build a matrix using a multi-dimensional vector of
	// pieces which is defined by the BOARDSIZE.  Then we populate the vectors
	// by iterating over the board row by row.
	vector< vector<Piece> > pieces(BOARDSIZE, vector<Piece>(BOARDSIZE));
	for ( int i=0; i<BOARDSIZE; i++ ) {
		vector<Piece> row;
		for ( int j=0; j<BOARDSIZE; j++ ) {
			Piece piece;
			piece = getPiece(i,j);
			row.push_back(piece); // add piece to the row vector	
		}
		pieces.push_back(row); // add the row vector to the pieces matrix
	}


	// Now we perform various searches for winning conditions of the board

	// DIAGIONAL SEARCHES
	// X - -   - - X
	// - X -   - X -
	// - - X   X - -

	// check the Top-right-to-Bottom-left diagonal
	// i = 0, j = 2
	// i = 1, j = 1
	// i = 2, j = 0
	playerX = 0;	
	playerO = 0;
	int j = BOARDSIZE-1;
	for ( int i = 0; i < BOARDSIZE; i++ ) {
		if ( winner ) { break; }
		Piece piece = getPiece(i,j);
		if ( piece == X ) {
			playerX++;
			if ( playerX == BOARDSIZE) {
				winningPiece = X;
				winner = true;
				break;
			}
		}
		else if ( piece == O ) {
			playerO++;
			if ( playerO == BOARDSIZE) {
				winningPiece = O;
				winner = true;
				break;
			}
		}
		j--;
	}
	// check the Top-left-to-Bottom-right diagonal
	playerX = 0;
	playerO = 0;
	for ( int k = 0; k < BOARDSIZE; k++ ) {
		if ( winner ) { break; }
		Piece piece = getPiece(k,k);
		if ( piece == X ) {
			playerX++;
			if ( playerX == BOARDSIZE) {
				winningPiece = X;
				winner = true;
				break;
			}
		}
		else if ( piece == O ) {
			playerO++;
			if ( playerO == BOARDSIZE) {
				winningPiece = O;
				winner = true;
				break;
			}
		}
	}	

	// COL BY COL SEARCH
	// EXAMPLES:
	// *          *
	// X O O    X X O
	// X O X    O X O
	// X X O    X X O
	playerX = 0;
	playerO = 0;
	for ( int j = 0; j < BOARDSIZE; j++ ) {
		if ( winner ) { break; }
		playerX = 0;
		playerO = 0;
		for ( int i = 0; i < BOARDSIZE; i++ ) {
			if ( !winner ) {
				Piece piece;
				piece = getPiece(i,j);	
				if ( piece == X ) {
					playerX++;
					if ( playerX == BOARDSIZE) {
						winningPiece = X;
						winner = true;
						break;
					}
				}
				else if ( piece == O ) {
					playerO++;
					if ( playerO == BOARDSIZE) {
						winningPiece = O;
						winner = true;
						break;
					}
				}
			}
		}
	}

	// ROW BY ROW SEARCH
	// EXAMPLES:
	//
	// X X X *  X O O
	// O O X    O O X
	// O X O    X X X *
	playerX = 0;
	playerO = 0;
	for ( int i = 0; i < BOARDSIZE; i++ ) {
		if ( winner ) { break; }
		playerX = 0;
		playerO = 0;
		for ( int j = 0; j < BOARDSIZE; j++ ) {
			if ( !winner ) {
				Piece piece;
				piece = getPiece(i,j);	
				if ( piece == X ) {
					playerX++;
					if ( playerX == BOARDSIZE) {
						winningPiece = X;
						winner = true;
						break;
					}
				}
				else if ( piece == O ) {
					playerO++;
					if ( playerO == BOARDSIZE) {
						winningPiece = O;
						winner = true;
						break;
					}
				}
			}
		}
	}

	// Finally, we check to see if the board is full or not
	bool boardIsFull = true; // first we assume it's full
	for ( int i = 0; i < BOARDSIZE; i++ ) {
		if ( boardIsFull ) {
			for ( int j=0; j<BOARDSIZE; j++ ) {
				Piece piece = getPiece(i,j);
				if (piece == Blank) {
					boardIsFull = false; // it's not full
					break;
				}
			}
		}
	}

	if ( !winner && boardIsFull ) {
		winningPiece = Blank;
	}

  	return winningPiece;
}
