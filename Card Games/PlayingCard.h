/*
*	Class Header: PlayingCard
*/

#ifndef PLAYINGCARD_H
#define PLAYINGCARD_H

//Header Files
#include <iostream>
#include <string>
#include <array>

class PlayingCard
{
	//Overloaded steam insertion operator
	friend std::ostream& operator<<(std::ostream& output, const PlayingCard& card);

public:
	//Constructors
	PlayingCard(int faceValue = 0, int suitIndex = 0); //Default Constructor
	PlayingCard(const PlayingCard& oldCard); //Copy Constructor
	//Destructor (no dynamic memory - not currently needed)

	//Public Data Members
		//Face and Suit arrays
	static const std::array<std::string, 14> s_CardFaces;
	static const std::array<std::string, 5> s_CardSuits;

	//Set and Get Functions
	void setFaceValue(int newFaceValue);
	int getFaceValue() const;
	
	std::string getFaceString() const;
		//"set" function is private - only constructors should call

	std::string getSuit() const;
		//"set" function is private - only constructors should call


	//Public Member Functions
	std::string toString() const;
	bool isEmpty() const;

	//Operator Overloads
	bool operator<(const PlayingCard& card2) const;
	bool operator<=(const PlayingCard& card2) const;
	bool operator>(const PlayingCard& card2) const;
	bool operator>=(const PlayingCard& card2) const;
	bool operator==(const PlayingCard& card2) const;
	bool operator!=(const PlayingCard& card2) const;
	void operator=(const PlayingCard& card2);

private:
	//Private Data Members
	int m_iFaceValue;
	std::string m_sFaceString;
	std::string m_sSuit;

	//Private Member Functions
	void setFaceString(); //Only constructors should call this
	void setSuit(int suitIndex); //Only constructors should call this
	void setSuit(const std::string& newSuit); //Only assignment operator should call this (along with copy constructor)
};

#endif