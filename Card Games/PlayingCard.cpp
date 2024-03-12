/*
*	Class Definitions: PlayingCard
* 
*	@author: Trenton Schacht
* 
*	@purpose:	Stores data for standard playing cards. 
*				Face is stored as both a number (for comparisons; [0, 13], 0 is for empty card) and a string (for display).
*				Suit is stored as a string.
*
*			Provides the following functionalities:
*				- Static Public Arrays: cardFaces, cardSuits
*				- Stream insertion
*				- Get functions: faceValue, faceString, suit
*				- Public services: toString, isEmpty
*				- Relational operators (<, <=, >, >=, ==, !=)
*				- Assignment operator
*/


// Header Files
#include <iostream>
#include <stdexcept>
#include "PlayingCard.h"

using namespace std;



// Non Member Function
ostream& operator<<(ostream& output, const PlayingCard& card) {
	output << card.getFaceString() << " of " << card.getSuit();
	return output;
} //end of "operator<<"



/*	Default Constructor
*	
*	@note: Uses private set functions which verify valid data.
* 
*	@preconditions: faceValue range: [1, 13] (indicate 1 for Ace, 2 for 2, etc...)
*					suitIndex range: [1, 4]  (indicate 1 for Clubs, 2 for Diamonds, 3 for Hearts, 4 for Spades)
*					Note: using 0's will create a "blank" card
* 
*	@param: Integers for face and suit. See preconditions.
*
*	@return: Constructs an object of type PlayingCard
*/
PlayingCard::PlayingCard(unsigned short int faceValue, size_t suitIndex) {
	setFaceValue(faceValue);
	setFaceString();
	setSuit(suitIndex);
} //end of "Default Constructor"


/*	Copy Constructor
* 
*	@note: Uses assignment operator which calls private set functions which verify valid data.
* 
*	@param: Constant reference to another playing card. 
* 
*	@return: Constructs an object of type PlayingCard with attributes of parameter.
*/
PlayingCard::PlayingCard(const PlayingCard& oldCard) {
	*this = oldCard;
} //end of "Copy Constructor"



/*	Public Static Arrays for Faces & Suits
*	
*	@note: Both use an empty string at index 0. Aligns logical faceValue as an index for its array.
*			This allows "blank" cards to be initialized with no face/suit.
*/
const array<string, 14> PlayingCard::s_CardFaces = { "", "Ace", "Duece", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" };
const array<string, 5> PlayingCard::s_CardSuits = { "", "Clubs", "Diamonds", "Hearts", "Spades" };



/*	Public Get Functions
* 
*	@note: All get functions have the following parameters and respective return types.
* 
*	@param: void
* 
*	@return: Respective type of each private data member.
*/

string PlayingCard::getFaceString() const {
	return m_sFaceString;
} //end of "getFaceString"


unsigned short int PlayingCard::getFaceValue() const {
	return m_iFaceValue;
} //end of "getFaceValue"


string PlayingCard::getSuit() const {
	return m_sSuit;
}  //end of "getSuit"



// Public Services

/*	isEmpty
*
*	@note: If either face or suit is a "blank" string the card is considered empty.
*
*	@param: void
*
*	@return: bool
*/
bool PlayingCard::isEmpty() const {
	if (m_sFaceString == s_CardFaces[0] || m_sSuit == s_CardSuits[0]) {
		return true;
	}
	else {
		return false;
	}
} //end of "isEmpty"


/*	toString
*	
*	@note: Primarly used for debugging.
* 
*	@param: void
* 
*	@return: string of all private data members.
*/
string PlayingCard::toString() const {
	return getFaceString().append(" of ").append(getSuit()).append("\n\tFace value is: ").append(to_string(getFaceValue()));
}  //end of "toString"



// Operator Overloads

/*	Relational Operator: <
*	
*	@note: Accounts for Aces as highest card.
* 
*	@param: Constant reference to another card. 
* 
*	@return: bool
*/
bool PlayingCard::operator<(const PlayingCard& card2) const {
	//Check if lhs is an Ace
	if (this->getFaceString() == s_CardFaces[1]) {
		return false;
	}
	//Check if rhs is an Ace
	else if (card2.getFaceString() == s_CardFaces[1]) {
		return true;
	}
	//Normal comparisons
	else if (this->getFaceValue() < card2.getFaceValue()) {
		return true;
	}
	else {
		return false;
	}
} //end of "operator<"


/*	Relational Operators (<=, >, >=, ==, !=)
*	
*	@note: All are defined in terms of <. See logic in respective function.
*/

bool PlayingCard::operator<=(const PlayingCard& card2) const {
	return !(card2 < *this);
} //end of "operator<="


bool PlayingCard::operator>(const PlayingCard& card2) const {
	return card2 < *this;
} //end of "operator>"


bool PlayingCard::operator>=(const PlayingCard& card2) const {
	return !(*this < card2);
} //end of "operator>="


bool PlayingCard::operator==(const PlayingCard& card2) const {
	return !(*this < card2) && !(card2 < *this);
} //end of "operator=="


bool PlayingCard::operator!=(const PlayingCard& card2) const {
	return (*this < card2) || (card2 < *this);
} //end of "operator!="


/*	Assignment Operator
* 
*	@note: Checks for self assignment. Calls private set functions that validate data.
* 
*	@param: Constant reference to another card.
* 
*	@return: void
*/
void PlayingCard::operator=(const PlayingCard& card2) {
	if (this == &card2) {
		return;
	}
	
	this->setFaceValue(card2.getFaceValue());
	this->setFaceString();
	this->setSuit(card2.getSuit());
} //end of "operator="




// Private Set Functions (Used for constructors and assignment operator)

/*	Set: m_sFaceString
* 
*	@note: Verifies valid data.
* 
*	@param: void (uses stored faceValue)
* 
*	@return: void
*/
void PlayingCard::setFaceString() {
	try {
		m_sFaceString = s_CardFaces.at(getFaceValue());
	}
	catch (const out_of_range& e) {
		cout << "Exception occurred: " << e.what();
	}
} //end of "setFaceString"


/*	Set: m_iFaceValue
*
*	@note: Verifies valid data.
*
*	@param: New integer for faceValue.
*
*	@return: void
*
*	@throw: invalid_argument
*/
void PlayingCard::setFaceValue(unsigned short int newFaceValue) {
	if (newFaceValue >= 0 && newFaceValue <= s_CardFaces.size()) {
		m_iFaceValue = newFaceValue;
	}
	else {
		throw invalid_argument("faceValue must be 0-14");
	}
} //end of "setFaceValue"


/*	Set: m_sSuit
* 
*	@note: Verifies valid data. Overloaded.
* 
*	@param: Index of s_CardSuits.
* 
*	@return: void
*/
void PlayingCard::setSuit(size_t suitIndex) {
	try {
		m_sSuit = s_CardSuits.at(suitIndex);
	}
	catch (const out_of_range& e) {
		cout << "Exception occurred: " << e.what();
	}
} //end of "setSuit(int)"


/*	Set: m_sSuit
* 
*	@note: Verifies valid data. Overloaded.
* 
*	@param: string for suit. 
* 
*	@return: void
*/
void PlayingCard::setSuit(const string& newSuit) {
	//Loop through static array of suits, and check that the parameter "suit" is equal to one of the suits stored in array
	for (const auto& currentSuit : s_CardSuits) {
		if (newSuit == currentSuit) {
			m_sSuit = newSuit;
			return;
		}
	}

	//No match was found - invalid argument
	throw invalid_argument("newSuit parameter must be a valid suit");
} //end of "setSuit(const string&)"