/*
*	Class Header: Player
*/

#ifndef PLAYER_H
#define PLAYER_H

//Header Files
#include <string>
#include "Hand5.h"

class Player
{
public:
	//Constructors & Deconstructor
	Player(); //default
	Player(const Player& oldPlayer); //copy
	virtual ~Player() { } //virtual deconstructor in case of dynamic memory

	//Set and Get Functions
	void setName(std::string newName);
	std::string getName() const;
	unsigned int getCredits() const;
	void setActiveStatus(bool newStatus);
	bool getActiveStatus() const;
	virtual unsigned short int getHandCount() const = 0;
	virtual size_t getHandSize() const = 0;
	std::string getHandRankString() const;

	//Public Member Functions
	virtual void addCard(const PlayingCard& card) = 0;
	virtual void determineHandRank() = 0;
	virtual void givePayout(unsigned int payout);
	virtual unsigned int placeBet(unsigned int bet);
	virtual void printCards() const;
	virtual void takeTurn() = 0;

	//Testing Functions
	Hand5 getHand() const;

protected:
	//Protected Data Members
	std::string m_sName;
	unsigned int m_iCredits;
	bool m_bActiveStatus;
	//should also have some kind of hand (use a generic base class?)
	Hand5* m_pHand;

private:
};

#endif