#ifndef FIVECARDDRAW_H
#define FIVECARDDRAW_H

//Header Files
#include "Game.h"

class Game_5CardDraw : public Game
{
public:
	//Constructors & Destructor
	Game_5CardDraw(); //default
	//copy
	virtual ~Game_5CardDraw(); //virtual destructor

	//Public Static Data Members
	static const unsigned short int s_iMAXPLAYERS = 5;

	//Public Member Functions
	virtual void run();

	//Testing Area

	void printHands() const;

protected:
	//Protected Member Functions
	virtual Player* createNPC(char npcName[10]);
	virtual Player* createUser();
	virtual bool gameLoop();
private:
	void buyInRound(); //tested and working
	void dealHands(); //tested and working
	void bettingRound(); //needs dynamic betting
	void replaceRound();
	void resetGame();
	void showdown(); //tested and working


	static std::mt19937 s_RandGen;
	unsigned int rollNumber(unsigned int low, unsigned int high);
};

#endif