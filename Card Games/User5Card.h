#ifndef USER5CARD_H
#define USER5CARD_H

//Header Files
#include "Player5Card.h"

class User5Card : public Player5Card
{
public:
	//Constructors & Deconstructor
	User5Card(); //default
	User5Card(const User5Card& oldUser); //copy
	virtual ~User5Card() { } //virtual deconstructor in case of dynamic memory

	//Public Member Functions
	virtual unsigned int determineBet(unsigned int minBet);
	virtual unsigned int placeBet(unsigned int minBet) final; //incomplete: need to ask user for bet & validate
	virtual void printCards() const;
	virtual std::vector<size_t> determineReplaceCardsIndexes();

protected:

private:

	void raiseBehavior(unsigned int prevBet);
};

#endif