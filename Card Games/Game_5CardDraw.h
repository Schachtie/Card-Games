#ifndef FIVECARDDRAW_H
#define FIVECARDDRAW_H

//Header Files
#include "Game.h"

class Game_5CardDraw : public Game
{
public:
	//Constructors and Destructor
	Game_5CardDraw(); //Default
	Game_5CardDraw(User* pOutsideUser); //Outside User
	virtual ~Game_5CardDraw(); //Virtual Destructor

	//Public Static Data Members
	static const unsigned short int s_iMAXPLAYERS = 5;
	static const unsigned short int s_iMAXRAISES = 2;

	//Public Virtual Services
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
	virtual void updateOutsideUser();

private:
	//Private Member Functions
	void bettingRound();
	void pauseForUser(const std::string& prompt) const;
	void printAllHands() const;
	unsigned int rollNumber(unsigned int low, unsigned int high);
	void showdown();

	//Private Data Members
	static std::mt19937 s_RandGen;
};

#endif