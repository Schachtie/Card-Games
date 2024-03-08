#ifndef VIDEOPOKER_H
#define VIDEOPOKER_H

//Header Files
#include "Game.h"

class Game_VideoPoker : public Game
{
public:
	//Constructors & Deconstructor
	Game_VideoPoker();


	//Public Member Functions
	static const std::array<unsigned int, 10> s_PayoutMultipliers;

	virtual void run();

protected:
	//Protected Member Functions
	virtual Player* createNPC(char npcName[10]);
	virtual Player* createUser();
	virtual void gameLoop();


	virtual void resetGame();
private:
	void buyInRound();
	void dealHand();
	void replaceRound();
	void determinePayout();
};

#endif