#ifndef PLAYER5CARD_H
#define PLAYER5CARD_H

//Header Files
#include "Player.h"
#include "Hand5.h"

class Player5Card : public Player
{
public:
	//Constructors & Deconstructor
	Player5Card(); //default
	Player5Card(const Player5Card& oldPlayer); //copy
	virtual ~Player5Card() { } //virtual deconstructor in case of dynamic memory

	//Public Member Functions
	virtual void determineHandRank() final;
	virtual void givePayout(unsigned int payout) final;
	virtual unsigned int placeBet() = 0;
	virtual void printCards() const;
	virtual void takeTurn() = 0;

protected:
	//Protected Data Members
	Hand5 hand;

private:
};

#endif