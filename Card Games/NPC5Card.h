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
	NPC5Card(); //default
	NPC5Card(const NPC5Card& oldPlayer); //copy
	NPC5Card(char npcName[10], unsigned short int raisesPerGame); //USED FOR TESTING
	virtual ~NPC5Card() { } //virtual destructor in case of dynamic memory

	//Public Member Functions
	virtual unsigned int determineBet(unsigned int minBet);
	virtual void printCards();
	virtual std::vector<size_t> determineReplaceCardsIndexes();

protected:
	virtual void raiseBehavior(unsigned int prevBet) final;

private:
	static std::mt19937 s_RandGen;

	unsigned int rollNumber(unsigned int low, unsigned int high);
	void storeReplaceCardIndexes(size_t startingTBIndex, std::vector<size_t>* pStoredIndexes);
	//add "compare card pointers" function for "determineReplaceCards"
};

#endif