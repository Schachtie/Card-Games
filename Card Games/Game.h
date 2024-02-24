#ifndef GAME_H
#define GAME_H

//Header Files
#include <vector>
#include "Player.h"

class Game
{
public:
	//Constructors & Deconstructor

	//Public Member Functions
	virtual void run() = 0;

protected:
	//Protected Data Members
	std::vector<Player*> m_ptrsPlayers;

	//Protected Member Functions
	virtual bool gameLoop() = 0;
private:
};

#endif