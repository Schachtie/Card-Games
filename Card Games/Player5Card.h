#ifndef PLAYER5CARD_H
#define PLAYER5CARD_H

//Header Files
#include "Player.h"
#include "Hand5.h"

class Player5Card : public Player
{
public:
	//Constructors and Destructor
	Player5Card(); //Default
	virtual ~Player5Card(); //virtual destructor in case of dynamic memory

	//Public Virtual Get Services
	virtual unsigned short int getHandCount() const final;
	virtual size_t getHandSize() const final;

	//Public Virtual Services
	virtual void addCard(const PlayingCard& card) final;
	virtual void determineHandRank() final;

	//Public Pure Virtual Services
	virtual unsigned int determineBet(unsigned int minBet) = 0;
	virtual std::vector<size_t> determineReplaceCardsIndexes() = 0;

protected:
	//Protected Pure Virtual Functions
	virtual void raiseBehavior(unsigned int prevBet) = 0;

private:
};

#endif