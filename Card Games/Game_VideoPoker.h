#ifndef VIDEOPOKER_H
#define VIDEOPOKER_H

//Header Files
#include "Game.h"

class Game_VideoPoker : public Game
{
public:
	//Constructors & Deconstructor

	//Public Member Functions
	virtual void run();

protected:
	//Protected Member Functions
	virtual void gameLoop();
private:
};

#endif