/*
*	Class Definitions: DeckOfCards
* 
*	@author: Trenton Schacht
* 
*	@purpose:	Simulates a standard deck of playing cards.
*				Uses a deque to store playing cards.
* 
*			Provides the following functionalities:
*				- Stream insertion
*				- Public services: initialize deck, popNextCard, printing deck,
*									shuffle, determine size
*/


// Header Files
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include "DeckOfCards.h"

using namespace std;



// Private Static Random Generator
mt19937 DeckOfCards::s_RandGen(chrono::steady_clock::now().time_since_epoch().count());



// Non Member Function
ostream& operator<<(ostream& output, const DeckOfCards& deck) {
	for (PlayingCard card : deck.m_Cards) {
		output << card << endl;
	}
	return output;
} //end of "operator<<"



// Constructors

/*	Default Constructor
* 
*	@note: Uses initDeck to create valid (and unique) cards to simulate a standard deck of playing cards.
*	
*	@param: void
* 
*	@return: Constructs an object of type DeckOfCards
*/
DeckOfCards::DeckOfCards() {
	initDeck();
} //end of "Default Constructor"


/*	Copy Constructor
* 
*	@note: Copies each card from previous deck to new deck.
* 
*	@preconditions: Assumes all cards in old deck are valid.
* 
*	@param: Constant reference to another deck of cards.
* 
*	@return: Constructs an object of type DeckOfCards
*/
DeckOfCards::DeckOfCards(const DeckOfCards& oldDeck) {
	for (const PlayingCard& card : oldDeck.m_Cards) {
		this->addCard(card);
	}
} //end of "Copy Constructor"



// Public Services

/*	initDeck
* 
*	@note: Initializes each unique card for a standard deck of playing cards and adds to m_Cards.
* 
*	@param: void
* 
*	@return: void (adds cards directly to private m_Cards data member)
*/
void DeckOfCards::initDeck() {
	//Empty deck just in case
	m_Cards.clear();

	for (size_t suitIndex = 1; suitIndex < PlayingCard::s_CardSuits.size(); ++suitIndex) {
		for (unsigned short int faceIndex = 1; faceIndex < PlayingCard::s_CardFaces.size(); ++faceIndex) {
			PlayingCard newCard(faceIndex, suitIndex);
			this->addCard(newCard);
		}
	}
} //end of "initDeck"


/*	popNextCard
*
*	@note: Removes card from deck completely. Return value should NOT be ignored!
*
*	@param: void
*
*	@return: Card that was removed from deck.
*/
PlayingCard DeckOfCards::popNextCard() {
	PlayingCard nextCard = m_Cards.back();
	m_Cards.pop_back();
	return nextCard;
} //end of "popNextCard"


/*	printDeck
* 
*	@note: Primarily used for debugging.
* 
*	@param: void
* 
*	@return: void (Prints deck directly)
*/
void DeckOfCards::printDeck() const {
	cout << "Number of cards in deck: " << size() << endl;
	for (PlayingCard card : m_Cards) {
		cout << card.toString() << endl;
	}
} //end of "printDeck"


/*	shuffle
* 
*	@note: Uses STL shuffle algorithm directly on cards container.
* 
*	@param: void
* 
*	@return: void
*/
void DeckOfCards::shuffle() {
	std::shuffle(m_Cards.begin(), m_Cards.end(), s_RandGen);
} //end of "shuffle"


/*	size
* 
*	@note: NOT capacity.
* 
*	@param: void
* 
*	@return: Number of cards currently in deck.
*/
size_t DeckOfCards::size() const {
	return m_Cards.size();
} //end of "size"



// Private Member Functions

/*	addCard
* 
*	@param: Card to be added to deck.
* 
*	@return: void
*/
void DeckOfCards::addCard(PlayingCard newCard) {
	m_Cards.push_back(newCard);
} //end of "addCard"