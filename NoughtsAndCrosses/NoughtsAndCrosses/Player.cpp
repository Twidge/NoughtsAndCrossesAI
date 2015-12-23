#include "Player.h"

// CONSTRUCTORS

Player::Player()
{
	level = Joe;
}

Player::Player(const Player& p)
{
	level = p.level;
	symbol = p.symbol;
	oppositeSymbol = p.oppositeSymbol;
}

Player::Player(const Standard st, const Square s)
{
	level = st;
	symbol = s;

	if (s == Nought)
	{
		oppositeSymbol = Cross;
	}

	else
	{
		oppositeSymbol = Nought;
	}
}

// GETTERS

// SETTERS

void Player::SetSymbol(const Square s)
{
	symbol = s;

	if (s == Nought)
	{
		oppositeSymbol = Cross;
	}

	else
	{
		oppositeSymbol = Nought;
	}
}

// METHODS

void Player::MakeMove(Board& b) const
{
	if (level == Joe) // If not a pro, pick a square at random
	{
		int x, y;

		do
		{
			x = rand() % BOARD_SIZE;
			y = rand() % BOARD_SIZE;

		} while (b.GetSquare(x, y) != Blank);

		b.SetSquare(x, y, symbol);
	}

	else if (level == Pro)
	{
		bool symbolPlaced = false;

		if (b.GetSquare(1, 1) == Blank) // If the centre square is empty, place a nought there
		{
			b.SetSquare(1, 1, symbol);
			symbolPlaced = true;
		}

		if (!symbolPlaced) // If noughts wins by placing something somewhere, do it
		{
			for (int i = 0; i < BOARD_SIZE; i++)
			{
				WinType willWin = NoResult;

				for (int j = 0; j < BOARD_SIZE; j++)
				{
					if (b.GetSquare(i, j) == Blank)
					{
						Board testBoard = Board(b);

						testBoard.SetSquare(i, j, symbol);

						willWin = testBoard.CheckWin();

						if ((willWin == NoughtsWin && symbol == Nought) || (willWin == CrossesWin && symbol == Cross))
						{
							b.SetSquare(i, j, symbol);
							symbolPlaced = true;
							break;
						}
					}
				}

				if (symbolPlaced)
					break;
			}
		}

		if (!symbolPlaced) // If noughts will lose by not placing something somewhere, do that
		{
			for (int i = 0; i < BOARD_SIZE; i++)
			{
				WinType willLose = NoResult;

				for (int j = 0; j < BOARD_SIZE; j++)
				{
					if (b.GetSquare(i, j) == Blank)
					{
						Board testBoard = Board(b);

						testBoard.SetSquare(i, j, oppositeSymbol);

						willLose = testBoard.CheckWin();

						if ((willLose == CrossesWin && symbol == Nought) || (willLose == NoughtsWin && symbol == Cross))
						{
							b.SetSquare(i, j, symbol);
							symbolPlaced = true;
							break;
						}
					}
				}

				if (symbolPlaced)
					break;
			}
		}

		if (!symbolPlaced) // If noughts can place something so that there are two ways of winning next turn, do that
		{
			for (int i = 0; i < BOARD_SIZE; i++)
			{
				int ways = 0;

				for (int j = 0; j < BOARD_SIZE; j++)
				{
					if (b.GetSquare(i, j) == Blank)
					{
						Board testBoard = Board(b);

						testBoard.SetSquare(i, j, symbol);

						ways = testBoard.WaysOfWinning(symbol);

						if (ways >= 2)
						{
							b.SetSquare(i, j, symbol);
							symbolPlaced = true;
							break;
						}
					}
				}

				if (symbolPlaced)
					break;
			}
		}

		if (!symbolPlaced) // If crosses can place something so that there are two ways of winning next turn, place a nought there
		{
			for (int i = 0; i < BOARD_SIZE; i++)
			{
				int ways = 0;

				for (int j = 0; j < BOARD_SIZE; j++)
				{
					if (b.GetSquare(i, j) == Blank)
					{
						Board testBoard = Board(b);

						testBoard.SetSquare(i, j, oppositeSymbol);

						ways = testBoard.WaysOfWinning(oppositeSymbol);

						if (ways >= 2)
						{
							b.SetSquare(i, j, symbol);
							symbolPlaced = true;
							break;
						}
					}
				}

				if (symbolPlaced)
					break;
			}
		}

		if (!symbolPlaced)
		{
			int x, y;

			do
			{
				x = rand() % BOARD_SIZE;
				y = rand() % BOARD_SIZE;


			} while (b.GetSquare(x, y) != Blank);

			b.SetSquare(x, y, symbol);
		}
	}
}

// OPERATOR OVERLOADS

void Player::operator= (const Player& p)
{
	level = p.level;
	symbol = p.symbol;
	oppositeSymbol = p.oppositeSymbol;
}