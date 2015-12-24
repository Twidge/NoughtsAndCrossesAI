#include "Game.h"

// CONSTRUCTORS

Game::Game()
{

}

Game::Game(const Game& g)
{
	gameBoard = g.gameBoard;
	noughts = g.noughts;
	crosses = g.crosses;
}

Game::Game(const Board& b, Player& p1, Player& p2)
{
	gameBoard = b;
	noughts = p1;
	crosses = p2;

	p1.SetSymbol(Nought);
	p2.SetSymbol(Cross);
}

// METHODS

WinType Game::RunGame()
{
	WinType gameState = NoResult;

	while (true)
	{
		// std::cout << gameBoard;

		noughts.MakeMove(gameBoard);

		gameState = gameBoard.CheckWin();

		if (gameState != NoResult)
		{
			gameBoard.ResetBoard();
			return gameState;
		}

		// std::cout << gameBoard;

		crosses.MakeMove(gameBoard);

		gameState = gameBoard.CheckWin();

		if (gameState != NoResult)
		{
			gameBoard.ResetBoard();
			return gameState;
		}
	}
}