/*
*	Class Header: Player
*/

#ifndef PLAYER_H
#define PLAYER_H

//Header Files
#include <string>

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

	//Public Member Functions
	virtual void determineHandRank() = 0;
	virtual void givePayout(unsigned int payout);
	virtual unsigned int placeBet(unsigned int bet);
	virtual void printCards() const;
	virtual void takeTurn() = 0;

protected:
	//Protected Data Members
	std::string sName;
	unsigned int iCredits;
	//should also have some kind of hand (use a generic base class?)

private:
};

#endif