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
	oppositeSymbol = OppositeSymbol(s);
}

// GETTERS

// SETTERS

void Player::SetSymbol(const Square s)
{
	symbol = s;
	oppositeSymbol = OppositeSymbol(s);
}

// METHODS

void Player::MakeMove(Board& b) const
{
	if (level == Joe) // If not a pro, pick a square at random
	{
		std::vector<Position> potentialMoves = b.FindBlankSquares();

		int x = rand() % potentialMoves.size();

		b.SetSquare(potentialMoves[x].x, potentialMoves[x].y, symbol);
	}

	else if (level == Pro)
	{
		std::vector<Position> potentialMoves = b.FindBlankSquares();

		bool symbolPlaced = false;

		if (b.GetSquare(BOARD_SIZE / 2, BOARD_SIZE / 2) == Blank) // If the centre square is empty, place a nought there
		{
			b.SetSquare(BOARD_SIZE / 2, BOARD_SIZE / 2, symbol);
			symbolPlaced = true;
		}

		for (int i = 1; i <= BOARD_SIZE; i++)
		{
			if (!symbolPlaced)
			{
				for (Position v : potentialMoves)
				{
					WinType willWin = RecursiveCheck(v.x, v.y, symbol, b, i);

					if ((willWin == NoughtsWin && symbol == Nought) || (willWin == CrossesWin && symbol == Cross))
					{
						b.SetSquare(v.x, v.y, symbol);
						symbolPlaced = true;
						break;
					}
				}

				if (!symbolPlaced)
				{
					for (Position v : potentialMoves)
					{
						WinType willWin = RecursiveCheck(v.x, v.y, oppositeSymbol, b, i);

						if ((willWin == NoughtsWin && symbol == Cross) || (willWin == CrossesWin && symbol == Nought))
						{
							b.SetSquare(v.x, v.y, symbol);
							symbolPlaced = true;
							break;
						}
					}
				}
			}
		}

		if (!symbolPlaced)
		{
			std::vector<Position> potentialMoves = b.FindBlankSquares();

			int x = rand() % potentialMoves.size();

			b.SetSquare(potentialMoves[x].x, potentialMoves[x].y, symbol);
		}
	}
}

// Checks 'depth' moves ahead to see if a win exists

WinType Player::RecursiveCheck(const int x, const int y, const Square s, const Board& b, const int depth) const
{
	Square o = OppositeSymbol(s);

	if (depth == 1)
	{
		Board testBoard = Board(b);

		testBoard.SetSquare(x, y, s);

		WinType result = testBoard.CheckWin();

		// std::cout << "RecursiveCheck " << x << " " << y << " " << s << " " << depth << " returns " << result << "\n";

		return result;
	}

	else
	{
		Board testBoard = Board(b);

		testBoard.SetSquare(x, y, s);

		std::vector<Position> potentialMoves = testBoard.FindBlankSquares();

		bool alwaysWin = true;

		for (Position v : potentialMoves)
		{
			bool winsAgainstThisMove = false;

			Board nextTestBoard = Board(testBoard);

			nextTestBoard.SetSquare(v.x, v.y, o);

			std::vector<Position> potentialSecondMoves = nextTestBoard.FindBlankSquares();

			for (Position v2 : potentialSecondMoves)
			{
				WinType winCheck = RecursiveCheck(v2.x, v2.y, s, nextTestBoard, depth - 1);

				if ((winCheck == NoughtsWin && s == Nought) || (winCheck == CrossesWin && s == Cross))
				{
					winsAgainstThisMove = true;
					break;
				}
			}

			if (!winsAgainstThisMove)
			{
				alwaysWin = false;
				break;
			}
		}
		
		if (alwaysWin && s == Nought)
		{
			// std::cout << "RecursiveCheck " << x << " " << y << " " << s << " " << depth << " returns NoughtsWin\n";
			return NoughtsWin;
		}

		else if (alwaysWin && s == Cross)
		{
			// std::cout << "RecursiveCheck " << x << " " << y << " " << s << " " << depth << " returns CrossesWin\n";
			return CrossesWin;
		}
	}

	return Draw;
}

// OPERATOR OVERLOADS

void Player::operator= (const Player& p)
{
	level = p.level;
	symbol = p.symbol;
	oppositeSymbol = p.oppositeSymbol;
}