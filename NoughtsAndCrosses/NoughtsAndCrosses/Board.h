#ifndef BOARD_H
#define BOARD_H

#include <random>
#include <iostream>

const int BOARD_SIZE = 3;

enum Square
{
	Blank,
	Nought,
	Cross
};

enum WinType
{
	NoughtsWin,
	CrossesWin,
	Draw,
	NoResult
};

class Board
{
private :

	Square _squares[BOARD_SIZE][BOARD_SIZE];

public :

	// CONSTRUCTORS

	Board();
	Board(const Board&);

	// GETTERS

	Square GetSquare(const int, const int) const;

	// SETTERS

	void SetSquare(const int, const int, const Square);

	// METHODS

	WinType CheckWin() const;
	void ResetBoard();
	int WaysOfWinning(const Square) const;

	// OPERATOR OVERLOADS

	void operator= (const Board&);
	friend std::ostream& operator<< (std::ostream&, const Board&);
};

#endif