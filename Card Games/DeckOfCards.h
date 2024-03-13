/*
*	Class Header: DeckOfCards
*/

#ifndef DECKOFCARDS_H
#define DECKOFCARDS_H


// Header Files
#include <deque>
#include <random>
#include <chrono>
#include <iostream>

#include "PlayingCard.h"


class DeckOfCards
{
	// Stream insertion operator
	friend std::ostream& operator<<(std::ostream& output, const DeckOfCards& deck);

public:
	//Constructors and Destructor
	DeckOfCards(); //Default
	DeckOfCards(const DeckOfCards& oldDeck); //Copy
	~DeckOfCards() { }

	// Public Services
	void initDeck();
	PlayingCard popNextCard();
	void printDeck() const;
	void shuffle();
	size_t size() const;

private:
	// Private Data Members
	std::deque<PlayingCard> m_Cards;
	static std::mt19937 s_RandGen;
	
	// Private Member Functions
	void addCard(PlayingCard newCard);
};

#endif