/*
*	Class Definitions: PlayingCard
*/

//Header Files
#include <iostream>
#include <stdexcept>
#include "PlayingCard.h"

using namespace std;

//Non Member Functions
ostream& operator<<(ostream& output, const PlayingCard& card) {
	output << card.getFaceString() << " of " << card.getSuit();
	return output;
} //end of "operator<<"




/* Constructor
*  faceValue range: [1, 13] (indicate 1 for Ace, 2 for 2, etc...)
*  suitIndex range: [1, 4]  (indicate 1 for Clubs, 2 for Diamonds, 3 for Hearts, 4 for Spades)
*  Note: using 0's will create a "blank" card
*/
PlayingCard::PlayingCard(int faceValue, int suitIndex)
{
	setFaceValue(faceValue);
	setFaceString();
	setSuit(suitIndex);
} //end of Default Constructor

//Copy Constructor
PlayingCard::PlayingCard(const PlayingCard& oldCard)
{
	//Call overloaded assignment operator
	*this = oldCard;
} //end of Copy Constructor

//Public Data Members

//Static Arrays for Faces & Suits
	//Note: both use an empty string at index 0. Mainly to align logical faceValue as an index for the array.
		//This allows "blank" cards to be initialized with no face/suit.
const array<string, 14> PlayingCard::s_CardFaces = { "", "Ace", "Duece", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" };
const array<string, 5> PlayingCard::s_CardSuits = { "", "Clubs", "Diamonds", "Hearts", "Spades" };


//Public Set and Get Functions
void PlayingCard::setFaceValue(int newFaceValue)
{
	if (newFaceValue >= 0 && newFaceValue <= s_CardFaces.size())
	{
		m_iFaceValue = newFaceValue;
	}
	else
	{
		throw invalid_argument("faceValue must be 0-14");
	}
} //end of "setFaceValue"

int PlayingCard::getFaceValue() const
{
	return m_iFaceValue;
} //end of "getFaceValue"

string PlayingCard::getFaceString() const
{
	return m_sFaceString;
} //end of "getFaceString"

string PlayingCard::getSuit() const
{
	return m_sSuit;
}  //end of "getSuit"

//Public Member Functions
string PlayingCard::toString() const 
{
	return getFaceString().append(" of ").append(getSuit()).append("\n\tFace value is: ").append(to_string(getFaceValue()));
}  //end of "toString"

bool PlayingCard::faceEqual(const PlayingCard& card2) const {
	if (this->getFaceValue() == card2.getFaceValue())
	{
		return true;
	}
	else
	{
		return false;
	}
}  //end of "faceEqual"

bool PlayingCard::isEmpty() const {
	if (m_sFaceString == s_CardFaces[0] || m_sSuit == s_CardSuits[0])
	{
		return true;
	}
	else
	{
		return false;
	}
} //end of "isEmpty"

//Operator Overloads
bool PlayingCard::operator<(const PlayingCard& card2) const {
	//Check if lhs is an Ace
	if (this->getFaceString() == PlayingCard::s_CardFaces[1])
	{
		return false;
	}
	//Check if rhs is an Ace
	else if (card2.getFaceString() == PlayingCard::s_CardFaces[1])
	{
		return true;
	}
	//Normal comparisons
	else if (this->getFaceValue() < card2.getFaceValue())
	{
		return true;
	}
	else
	{
		return false;
	}
} //end of "operator<"

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

void PlayingCard::operator=(const PlayingCard& card2) {
	//Check for self assignment
		//both same object or same data stored
	if (this == &card2)
	{
		return;
	}
	
	//Deep copy
	this->setFaceValue(card2.getFaceValue());
	this->setFaceString();
	this->setSuit(card2.getSuit());
} //end of "operator="




//Private Member Functions
void PlayingCard::setFaceString()
{
	//Set proper string for face
	if (m_iFaceValue >= 0 && m_iFaceValue < s_CardFaces.size())
	{
		m_sFaceString = s_CardFaces[getFaceValue()];
	}
	//This will handle "Ace High" situations
	else if (m_iFaceValue == s_CardFaces.size())
	{
		m_sFaceString = s_CardFaces[1];
	}
	else
	{
		throw invalid_argument("error setting faceString - invalid argument for faceValue passed");
	}
} //end of "setFaceString"

void PlayingCard::setSuit(int suitIndex)
{
	try
	{
		m_sSuit = s_CardSuits.at(suitIndex);
	}
	catch (const out_of_range& e)
	{
		cout << "Exception occurred: " << e.what();
	}
} //end of "setSuit(int)"

void PlayingCard::setSuit(const string& newSuit)
{
	//Loop through static array of suits, and check that the parameter "suit" is equal to one of the suits stored in array
	for (const auto& currentSuit : s_CardSuits)
	{
		if (newSuit == currentSuit)
		{
			m_sSuit = newSuit;
			return;
		}
	}

	//No match was found - invalid argument
	throw invalid_argument("newSuit parameter must be a valid suit");
} //end of "setSuit(const string&)"