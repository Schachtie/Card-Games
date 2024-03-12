#ifndef NPC5CARD_H
#define NPC5CARD_H

//Header Files
#include <random>
#include <chrono>
#include "Player5Card.h"

class NPC5Card : public Player5Card
{
public:
	//Constructors and Destructors
	NPC5Card(); //Default
	NPC5Card(char npcName[10]); //Name Provided
	virtual ~NPC5Card() { } //virtual destructor in case of dynamic memory

	//Public Virtual Services
	virtual unsigned int determineBet(unsigned int minBet) final;
	virtual std::vector<size_t> determineReplaceCardsIndexes() final;

protected:
	//Protected Virtual Functions
	virtual void raiseBehavior(unsigned int prevBet) final;

private:
	//Private Data Members
	static std::mt19937 s_RandGen;

	//Private Member Functions
	unsigned int rollNumber(unsigned int low, unsigned int high);
	void storeReplaceCardIndexes(size_t startingTBIndex, std::vector<size_t>* pStoredIndexes);
};

#endif