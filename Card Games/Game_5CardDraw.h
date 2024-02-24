#ifndef FIVECARDDRAW_H
#define FIVECARDDRAW_H

//Header Files
#include "Game.h"

class Game_5CardDraw : public Game
{
public:
	//Constructors & Deconstructor
	Game_5CardDraw(); //defaul

	//Public Member Functions
	virtual void run();

protected:
	//Protected Member Functions
	virtual bool gameLoop();
private:
};

#endif