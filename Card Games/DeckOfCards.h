/*
*	Class Header: DeckOfCards
*/

#ifndef DECKOFCARDS_H
#define DECKOFCARDS_H


//Header Files
#include <deque>
#include <random>
#include <chrono>
#include <iostream>
#include "PlayingCard.h"

class DeckOfCards
{
	//Overloaded steam insertion operator
	friend std::ostream& operator<<(std::ostream& output, const DeckOfCards& deck);

public:
	//Constructors and Deconstructors
	DeckOfCards(); //Default Constructor
	DeckOfCards(const DeckOfCards& oldDeck); //Copy Constructor
	//TODO: deconstructor

	//Set and Get Functions
	PlayingCard getCardAt(int index) const;
		//setCardAt is private
	size_t size() const;

	//Public Member Functions
	void initDeck();
	void printDeck() const;
	void shuffle();
	//unshuffle?
	PlayingCard popNextCard();
	PlayingCard peekNextCard() const;

	//Operator Overloads??
		//+, +=, (maybe - and -=, will need unshuffle), MIGHT WANT TO JUST GET RID OF THESE, NOT SURE WHEN I WOULD CALL ANYWAY

private:
	//Private Data Members
	std::deque< PlayingCard > m_Cards;
	static std::mt19937 s_RandGen;
	

	//Private Member Functions
	void setCardAt(int index, PlayingCard newCard); //untested - not sure if even being used, may delete
	void addCard(PlayingCard newCard);
};

#endif