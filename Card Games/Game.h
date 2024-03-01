#ifndef GAME_H
#define GAME_H

//Header Files
#include <vector>
#include "Player.h"
#include "DeckOfCards.h"

class Game
{
public:
	//Constructors & Deconstructor

	//Public Member Functions
	virtual void run() = 0;

protected:
	//Protected Data Members
	size_t numPlayers;
	std::vector<Player*> m_ptrsPlayers;
	unsigned int m_iBuyIn;
	unsigned int m_iMinBet;
	unsigned int m_iCurrentPot;
	DeckOfCards m_Deck;

	//Protected Member Functions
	virtual Player* createNPC(int i) = 0;
	virtual Player* createUser() = 0;
	virtual bool gameLoop() = 0;
private:
};

#endif