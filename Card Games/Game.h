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
	size_t m_NumPlayers;
	std::vector<Player*> m_ptrsPlayers;
	unsigned int m_iBuyIn;
	unsigned int m_iMinBet;
	unsigned int m_iCurrentPot;
	DeckOfCards m_Deck;

	//Protected Member Functions
	virtual Player* createNPC(char npcName[10]) = 0;
	virtual Player* createUser() = 0;
	virtual void gameLoop() = 0;
		

	virtual void replaceRound() = 0;
	virtual void resetGame() = 0;
	bool playAgain() const;

private:
};

#endif