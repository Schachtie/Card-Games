/*
*	Class Definitions: Hand
*
*	@author: Trenton Schacht
*
*	@purpose:	asdf
*
*			Provides the following functionalities:
*				- 
*/


// Header Files
#include "Hand.h"

using namespace std;



// Non Member Functions
ostream& operator<<(ostream& output, const Hand& hand) {
	hand.print(output);
	return output;
}

// Constructors and Destructors
Hand::Hand() {
	;
}

Hand::~Hand() {
	;
}


/*	Public Static Array for Hand Ranks
*
*	@notes: Hands were taken from wikipedia, ignoring Five of a Kind.
*			https://en.wikipedia.org/wiki/List_of_poker_hands
*/
const array<string, 10> Hand::s_HandRanks = { "High Card", "Pair", "Two Pair", "Three of a Kind", "Straight", "Flush", "Full House", "Four of a Kind", "Straight Flush", "Royal Flush" };



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