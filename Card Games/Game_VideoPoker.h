#ifndef VIDEOPOKER_H
#define VIDEOPOKER_H

//Header Files
#include "Game.h"

class Game_VideoPoker : public Game
{
public:
	//Constructors and Destructor
	Game_VideoPoker(); //Default
	virtual ~Game_VideoPoker(); //Virtual Destructor


	//Public Static Payout array
	static const std::array<unsigned int, 10> s_PayoutMultipliers;

	//Public Services
	virtual void run();

protected:
	//Protected Virtual Member Functions
	virtual void buyInRound();
	virtual Player* createNPC(char npcName[10]);
	virtual Player* createUser();
	virtual void dealCards();
	virtual void gameLoop();
	virtual void replaceRound();
	virtual void resetGame();

private:
	//Private Member Functions
	void determinePayout();
	void printPayTable() const;
};

#endif