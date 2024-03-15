/*
*	Class Definitions: Hand
*
*	@author: Trenton Schacht
*
*	@purpose:	Abstract class used to allow potential expansion of program.
*				New hand types can be defined and inherit this class for new games.
*
*			Provides the following functionalities:
*				- Stream insertion via polymorphic behavior in derived classes.
*				- Get functions: rankString, rankValue, 
*				- Virtual Get functions: cardPtrAt, numOfTieBreakers, 
*											tieBreakerAt, tieBreakersAll
*				- Virtual Set functions: setRank
*				- Virtual Public services: addCard, clearHand, count, print, printHandNumbered, 
*											replaceCardAt, size
*/


// Header Files
#include "Hand.h"

using namespace std;



// Non Member Functions
ostream& operator<<(ostream& output, const Hand& hand) {
	hand.print(output);
	return output;
}



// Constructors

//Default Constructor
Hand::Hand() {
	m_iRank = 0;
} //end of "Default Constructor"



/*	Public Static Array for Hand Ranks
*
*	@notes: Hands were taken from wikipedia, ignoring Five of a Kind.
*			https://en.wikipedia.org/wiki/List_of_poker_hands
*/
const array<string, 10> Hand::s_HandRanks = { "High Card", "Pair", "Two Pair", "Three of a Kind", "Straight", "Flush", "Full House", "Four of a Kind", "Straight Flush", "Royal Flush" };



// Public Get Functions

/*	Public Get Functions
*
*	@notes: All get functions have the following parameters and respective return types.
*
*	@params: void
*
*	@return: Respective type of each private data member.
*/

unsigned short int Hand::getRankValue() const {
	return m_iRank;
} //end of "getRankValue"


string Hand::getRankString() const {
	return s_HandRanks[m_iRank];
} //end of "getRankString"



// Operator Overloads

/*	Relational Operators (<=, >, >=, ==, !=)
*
*	@notes: < is pure virtual and must be defined in each derived class. 
			All are defined in terms of <. See logic in respective function.
*/

bool Hand::operator<=(const Hand& secondHand) const {
	return !(secondHand < *this);
}


bool Hand::operator>(const Hand& secondHand) const {
	return secondHand < *this;
}


bool Hand::operator>=(const Hand& secondHand) const {
	return !(*this < secondHand);
}


bool Hand::operator==(const Hand& secondHand) const {
	return !(*this < secondHand) && !(secondHand < *this);
}


bool Hand::operator!=(const Hand& secondHand) const {
	return (*this < secondHand) || (secondHand < *this);
}