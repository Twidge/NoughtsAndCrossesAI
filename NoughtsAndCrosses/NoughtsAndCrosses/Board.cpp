#include "Board.h"

Square OppositeSymbol(Square s)
{
	if (s == Nought)
	{
		return Cross;
	}

	else
	{
		return Nought;
	}
}

// CONSTRUCTORS

Board::Board()
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			_squares[i][j] = Blank;
		}
	}
}

Board::Board(const Board& b)
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			_squares[i][j] = b.GetSquare(i, j);
		}
	}
}

// GETTERS

Square Board::GetSquare(const int x, const int y) const
{
	return _squares[x][y];
}

// SETTERS

void Board::SetSquare(const int x, const int y, const Square s)
{
	if (_squares[x][y] != Blank)
	{
		std::cout << "Error: rewriting a square.\n";
		std::cin.get();
	}

	_squares[x][y] = s;
}

// METHODS

WinType Board::CheckWin() const // Checks to see who has won or if the game should continue
{
	// Check if there's BOARD_SIZE of the same type in any row or column

	for (int i = 0; i < BOARD_SIZE; i++)
	{
		bool isWin = true;

		for (int j = 1; j < BOARD_SIZE; j++)
		{
			if (_squares[i][j] != _squares[i][j - 1])
			{
				isWin = false;
			}
		}

		if (_squares[i][0] == Blank)
		{
			isWin = false;
		}

		if (isWin && _squares[i][0] == Nought)
		{
			return NoughtsWin;
		}

		else if (isWin)
		{
			return CrossesWin;
		}
	}

	for (int i = 0; i < BOARD_SIZE; i++)
	{
		bool isWin = true;

		for (int j = 1; j < BOARD_SIZE; j++)
		{
			if (_squares[j][i] != _squares[j - 1][i])
			{
				isWin = false;
			}
		}

		if (_squares[0][i] == Blank)
		{
			isWin = false;
		}

		if (isWin && _squares[0][i] == Nought)
		{
			return NoughtsWin;
		}

		else if (isWin)
		{
			return CrossesWin;
		}
	}

	// Check if there's BOARD_SIZE of the same type in either of the diagonals

	bool isWin = true;

	for (int i = 1; i < BOARD_SIZE; i++)
	{
		if (_squares[i][i] != _squares[i - 1][i - 1])
		{
			isWin = false;
		}
	}

	if (_squares[0][0] == Blank)
	{
		isWin = false;
	}

	if (isWin && _squares[0][0] == Nought)
	{
		return NoughtsWin;
	}

	else if (isWin)
	{
		return CrossesWin;
	}

	isWin = true;

	for (int i = 1; i < BOARD_SIZE; i++)
	{
		if (_squares[BOARD_SIZE - 1 - i][i] != _squares[BOARD_SIZE - i][i - 1])
		{
			isWin = false;
		}
	}

	if (_squares[BOARD_SIZE - 1][0] == Blank)
	{
		isWin = false;
	}

	if (isWin && _squares[BOARD_SIZE - 1][0] == Nought)
	{
		return NoughtsWin;
	}

	else if (isWin)
	{
		return CrossesWin;
	}

	// Check if there's a blank square - if yes, return NoResult; if no, return Draw

	bool isBlank = true;

	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (_squares[i][j] == Blank)
			{
				return NoResult;
			}
		}
	}

	return Draw;
}

// Finds all blank squares on the board and adds them to a vector

std::vector<Position> Board::FindBlankSquares()
{
	blankSquares = std::vector<Position>();

	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (_squares[i][j] == Square::Blank)
			{
				blankSquares.push_back({ i, j });
			}
		}
	}

	return blankSquares;
}

void Board::ResetBoard() // Resets the board to blank state
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			_squares[i][j] = Blank;
		}
	}
}

int Board::WaysOfWinning(const Square s) const // Returns the number of ways in which s (Noughts/Crosses) can win if they go next
{
	int returnValue = 0;

	if (s == Blank)
	{
		std::cout << "Error: no side chosen for WaysOfWinning().\n";
		return 0;
	}

	for (int i = 0; i < BOARD_SIZE; i++) // For each square, check if placing the appropriate symbol there would win
	{
		WinType win = NoResult;

		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (_squares[i][j] == Blank)
			{
				Board test = Board(*this);

				test._squares[i][j] = s;

				win = test.CheckWin();

				if (win == NoughtsWin && s == Nought)
				{
					returnValue++;
				}

				else if (win == CrossesWin && s == Cross)
				{
					returnValue++;
				}
			}
		}
	}

	return returnValue;
}

// OPERATOR OVERLOADS

void Board::operator= (const Board& b)
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			_squares[i][j] = b.GetSquare(i, j);
		}
	}
}

std::ostream& operator<< (std::ostream& os, const Board& b)
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			os << b._squares[i][j] << " ";
		}

		os << "\n";
	}

	return os;
}