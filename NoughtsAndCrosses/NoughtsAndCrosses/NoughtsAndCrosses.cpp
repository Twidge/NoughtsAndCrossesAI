// NoughtsAndCrosses.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Game.h"
#include <time.h>

const int GAME_LOOPS = 100000;

int _tmain(int argc, _TCHAR* argv[])
{
	srand(time(NULL));

	int wins[3] { 0, 0, 0 };

	Board b = Board();
	Player p1 = Player(Pro, Nought);
	Player p2 = Player(Joe, Cross);
	
	WinType result;

	for (int i = 0; i < GAME_LOOPS; i++)
	{
		// std::cout << "--\n";

		Game newGame = Game(b, p1, p2);

		result = newGame.RunGame();

		if (result == NoughtsWin)
		{
			wins[(int)NoughtsWin]++;
		}

		else if (result == CrossesWin)
		{
			wins[(int)CrossesWin]++;
		}

		else
		{
			wins[(int)Draw]++;
		}

		if (i % (GAME_LOOPS / 100) == 0)
			std::cout << "Game " << i + 1 << " done.\n";
	}

	std::cout << "\n" << "Noughts Wins: " << wins[(int)NoughtsWin] << "\n";
	std::cout << "Crosses Wins: " << wins[(int)CrossesWin] << "\n";
	std::cout << "Draws: " << wins[(int)Draw] << "\n";

	std::cin.get();
}

