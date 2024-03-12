#ifndef USER5CARD_H
#define USER5CARD_H

//Header Files
#include "Player5Card.h"
#include "User.h"

class User5Card : public Player5Card
{
public:
	//Constructors & Deconstructor
	User5Card(); //default
	User5Card(const User* const pOutsideUser); //Outside User
	virtual ~User5Card() { } //virtual deconstructor in case of dynamic memory

	//Public Member Functions
	virtual unsigned int determineBet(unsigned int minBet);
	virtual void printCards() const;
	virtual std::vector<size_t> determineReplaceCardsIndexes();

protected:
	virtual void raiseBehavior(unsigned int prevBet) final;
private:
};

#endif