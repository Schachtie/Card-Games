/*
*	Class Definitions: DeckOfCards
*/

//Header Files
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include "DeckOfCards.h"

using namespace std;

//Static Private Data Members
mt19937 DeckOfCards::m_RandGen(chrono::steady_clock::now().time_since_epoch().count());

//Non Member Functions
ostream& operator<<(ostream& output, const DeckOfCards& deck) {
	for (PlayingCard card : deck.m_Cards) {
		output << card << endl;
	}
	return output;
}

//Public Modifier

//Constructors and Deconstructors
DeckOfCards::DeckOfCards() {
	for (int suitIndex = 1; suitIndex < PlayingCard::s_CardSuits.size(); ++suitIndex)
	{
		for (int faceIndex = 1; faceIndex < PlayingCard::s_CardFaces.size(); ++faceIndex)
		{
			PlayingCard newCard(faceIndex, suitIndex);
			this->addCard(newCard);
		}
	}
}

DeckOfCards::DeckOfCards(const DeckOfCards& oldDeck) {
	for (PlayingCard card : oldDeck.m_Cards)
	{
		this->addCard(card);
	}
}

//Set and Get Functions
PlayingCard DeckOfCards::getCardAt(int index) const {
	try
	{
		return m_Cards.at(index);
	}
	catch (const out_of_range& e)
	{
		cout << "Exception occurred: " << e.what();
		PlayingCard emptyCard;
		return emptyCard;
	}
}

size_t DeckOfCards::size() const {
	return m_Cards.size();
}


//Public Member Functions
void DeckOfCards::printDeck() {
	cout << "Number of cards in deck: " << size() << endl;
	for (PlayingCard card : m_Cards)
	{
		cout << card.toString() << endl;
	}
}

void DeckOfCards::shuffle() {
	std::shuffle(m_Cards.begin(), m_Cards.end(), m_RandGen);
}

PlayingCard DeckOfCards::popNextCard() {
	PlayingCard nextCard = m_Cards.back();
	m_Cards.pop_back();
	return nextCard;
}

PlayingCard DeckOfCards::peekNextCard() const {
	return m_Cards.back();
}


//Operator Overloads



//Private Member Functions
void DeckOfCards::setCardAt(int index, PlayingCard newCard) {
	try
	{
		m_Cards.at(index) = newCard;
	}
	catch (const out_of_range& e)
	{
		cout << "Exception occurred: " << e.what();
	}
}

void DeckOfCards::addCard(PlayingCard newCard) {
	m_Cards.push_back(newCard);
}