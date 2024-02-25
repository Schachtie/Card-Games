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
	virtual ~Player5Card(); //virtual destructor in case of dynamic memory

	//Public Member Functions (virtual)
	virtual void addCard(const PlayingCard& card) final;
	virtual void determineHandRank() final;
	virtual unsigned short int getHandCount() const final;
	virtual size_t getHandSize() const final;
	virtual void givePayout(unsigned int payout) final;
	virtual unsigned int placeBet(unsigned int minBet) = 0;
	virtual void printCards() const;
	virtual void takeTurn() = 0;

	//Public Member Functions
	

protected:
	//Protected Data Members
	

private:
};

#endif