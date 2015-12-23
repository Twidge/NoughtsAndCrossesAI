#ifndef GAME_H
#define GAME_H

#include "Player.h"

class Game
{
private :

	Board gameBoard;
	Player noughts;
	Player crosses;

public :

	// CONSTRUCTORS

	Game();
	Game(const Game&);
	Game(const Board&, Player&, Player&);

	// METHODS

	WinType RunGame();
};

#endif