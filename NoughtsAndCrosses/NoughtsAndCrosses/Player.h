#ifndef PLAYER_H
#define PLAYER_H

#include "Board.h"

enum Standard
{
	Pro,
	Joe
};

class Player
{
private :

	Standard level;
	Square symbol;
	Square oppositeSymbol;

public :

	// CONSTRUCTORS

	Player();
	Player(const Player&);
	Player(const Standard, const Square);

	// GETTERS

	// SETTERS

	void SetSymbol(const Square);

	// METHODS

	void MakeMove(Board&) const;

	// OPERATOR OVERLOADS

	void operator= (const Player&);
};

#endif