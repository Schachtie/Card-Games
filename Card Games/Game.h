/*
*	Class Header: Game
*/

#ifndef GAME_H
#define GAME_H


// Header Files
#include <vector>
#include <string>

#include "Player.h"
#include "DeckOfCards.h"
#include "User.h"


class Game
{
public:
	//Constructors and Destructor
	Game(); //Default
	virtual ~Game() { } //virtual destructor in case of dynamic memory

	// Public Virtual Services
	virtual void run() = 0;

protected:
	// Protected Data Members
	User* m_pOutsideUser;
	size_t m_NumPlayers;
	std::vector<Player*> m_ptrsPlayers;
	unsigned int m_iBuyIn;
	unsigned int m_iMinBet;
	unsigned int m_iCurrentPot;
	DeckOfCards m_Deck;

	// Protected Member Functions
	bool playAgain() const;
	void printRules(const std::string& fileName);

	// Protected Virtual Member Functions
	virtual void buyInRound() = 0;
	virtual Player* createNPC(char npcName[10]) = 0;
	virtual Player* createUser() = 0;
	virtual void dealCards() = 0;
	virtual void gameLoop() = 0;
	virtual void replaceRound() = 0;
	virtual void resetGame() = 0;
	virtual void updateOutsideUser() = 0;

private:
};

#endif