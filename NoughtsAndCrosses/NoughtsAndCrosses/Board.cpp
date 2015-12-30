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
			squares[i][j] = Blank;
		}
	}
}

Board::Board(const Board& b)
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			squares[i][j] = b.GetSquare(i, j);
		}
	}
}

// GETTERS

Square Board::GetSquare(const int x, const int y) const
{
	return squares[x][y];
}

// SETTERS

void Board::SetSquare(const int x, const int y, const Square s)
{
	if (squares[x][y] != Blank)
	{
		std::cout << "Error: rewriting a square.\n";
		std::cin.get();
	}

	squares[x][y] = s;
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
			if (squares[i][j] != squares[i][j - 1])
			{
				isWin = false;
			}
		}

		if (squares[i][0] == Blank)
		{
			isWin = false;
		}

		if (isWin && squares[i][0] == Nought)
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
			if (squares[j][i] != squares[j - 1][i])
			{
				isWin = false;
			}
		}

		if (squares[0][i] == Blank)
		{
			isWin = false;
		}

		if (isWin && squares[0][i] == Nought)
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
		if (squares[i][i] != squares[i - 1][i - 1])
		{
			isWin = false;
		}
	}

	if (squares[0][0] == Blank)
	{
		isWin = false;
	}

	if (isWin && squares[0][0] == Nought)
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
		if (squares[BOARD_SIZE - 1 - i][i] != squares[BOARD_SIZE - i][i - 1])
		{
			isWin = false;
		}
	}

	if (squares[BOARD_SIZE - 1][0] == Blank)
	{
		isWin = false;
	}

	if (isWin && squares[BOARD_SIZE - 1][0] == Nought)
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
			if (squares[i][j] == Blank)
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
			if (squares[i][j] == Square::Blank)
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
			squares[i][j] = Blank;
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
			if (squares[i][j] == Blank)
			{
				Board test = Board(*this);

				test.squares[i][j] = s;

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
			squares[i][j] = b.GetSquare(i, j);
		}
	}
}

std::ostream& operator<< (std::ostream& os, const Board& b)
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			os << b.squares[i][j] << " ";
		}

		os << "\n";
	}

	return os;
}