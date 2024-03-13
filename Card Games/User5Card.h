/*
*	Class Header: User5Card
*/

#ifndef USER5CARD_H
#define USER5CARD_H


// Header Files
#include "Player5Card.h"
#include "User.h"


class User5Card : public Player5Card
{
public:
	//Constructors and Destructor
	User5Card(); //Default
	User5Card(const User* const pOutsideUser); //Outside User
	virtual ~User5Card() { } //virtual destructor in case of dynamic memory

	// Public Virtual Services
	virtual unsigned int determineBet(unsigned int minBet) final;
	virtual std::vector<size_t> determineReplaceCardsIndexes() final;

protected:
	// Protected Virtual Member Functions
	virtual void raiseBehavior(unsigned int prevBet) final;

private:
};

#endif