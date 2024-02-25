#ifndef NPC5CARD_H
#define NPC5CARD_H

//Header Files
#include "Player5Card.h"

class NPC5Card : public Player5Card
{
public:
	//Constructors and Destructors
	NPC5Card(); //default
	NPC5Card(const NPC5Card& oldPlayer); //copy
	virtual ~NPC5Card() { } //virtual destructor in case of dynamic memory

	//Public Member Functions
	virtual unsigned int placeBet(unsigned int minBet) final;
	virtual void printCards();
	virtual void takeTurn();
};

#endif