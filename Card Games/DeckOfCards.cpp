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
*				- Get functions: getCardAt
*				- Public services: initialize deck, peekNextCard, popNextCard, printing deck,
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



/*	Default Constructor
* 
*	@notes: Uses initDeck to create valid (and unique) cards to simulate a standard deck of playing cards.
*	
*	@params: void
* 
*	@return: Constructs an object of type DeckOfCards
*/
DeckOfCards::DeckOfCards() {
	initDeck();
} //end of "Default Constructor"


/*	Copy Constructor
* 
*	@notes: Copies each card from previous deck to new deck.
* 
*	@preconditions: Assumes all cards in old deck are valid.
* 
*	@params: Constant reference to another deck of cards.
* 
*	@return: Constructs an object of type DeckOfCards
*/
DeckOfCards::DeckOfCards(const DeckOfCards& oldDeck) {
	for (const PlayingCard& card : oldDeck.m_Cards) {
		this->addCard(card);
	}
} //end of "Copy Constructor"



// Public Get Functions

/*	getCardAt
* 
*	@notes: Uses bounds checking on supplied index.
* 
*	@params: index
* 
*	@returns: If index is valid returns card at indicated position. Otherwise returns empty card.
*/
PlayingCard DeckOfCards::getCardAt(size_t index) const {
	try {
		return m_Cards.at(index);
	}
	catch (const out_of_range& e) {
		cout << "Exception occurred: " << e.what();
		PlayingCard emptyCard;
		return emptyCard;
	}
} //end of "getCardAt"



//Public Services

/*	initDeck
* 
*	@notes: Initializes each unique card for a standard deck of playing cards and adds to m_Cards.
* 
*	@params: void
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


/*	peekNextCard
*
*	@notes: Card is not removed from deck.
*
*	@params: void
*
*	@return: Card at "top" of deck.
*/
PlayingCard DeckOfCards::peekNextCard() const {
	return m_Cards.back();
} //end of "peekNextCard"


/*	popNextCard
*
*	@notes: Removes card from deck completely. Return value should NOT be ignored!
*
*	@params: void
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
*	@notes: Primarily used for debugging.
* 
*	@params: void
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
*	@notes: Uses STL shuffle algorithm directly on cards container.
* 
*	@params: void
* 
*	@params: void
*/
void DeckOfCards::shuffle() {
	std::shuffle(m_Cards.begin(), m_Cards.end(), s_RandGen);
} //end of "shuffle"


/*	size
* 
*	@notes: NOT capacity.
* 
*	@params: void
* 
*	@return: Number of cards currently in deck.
*/
size_t DeckOfCards::size() const {
	return m_Cards.size();
} //end of "size"



//Private Member Functions

/*	addCard
* 
*	@params: Card to be added to deck.
* 
*	@return: void
*/
void DeckOfCards::addCard(PlayingCard newCard) {
	m_Cards.push_back(newCard);
} //end of "addCard"


/*	setCardAt
* 
*	@notes: Uses bounds checking on index. 
* 
*	@params: index, card to be added
* 
*	@return: void
*/
void DeckOfCards::setCardAt(size_t index, PlayingCard newCard) {
	try {
		m_Cards.at(index) = newCard;
	}
	catch (const out_of_range& e) {
		cout << "Exception occurred: " << e.what();
	}
} //end of "setCardAt"