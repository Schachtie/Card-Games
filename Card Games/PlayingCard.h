/*
*	Class Header: PlayingCard
*/

#ifndef PLAYINGCARD_H
#define PLAYINGCARD_H


// Header Files
#include <iostream>
#include <string>
#include <array>


class PlayingCard
{
	// Stream insertion operator
	friend std::ostream& operator<<(std::ostream& output, const PlayingCard& card);

public:
	//Constructors and Destructor
	PlayingCard(unsigned short int faceValue = 0, size_t suitIndex = 0); //Default
	PlayingCard(const PlayingCard& oldCard); //Copy
	~PlayingCard() { }

	// Public Static Face and Suit arrays
	static const std::array<std::string, 14> s_CardFaces;
	static const std::array<std::string, 5> s_CardSuits;

	// Public Get Functions
	std::string getFaceString() const;
	unsigned short int getFaceValue() const;
	std::string getSuit() const;

	// Public Services
	bool isEmpty() const;
	std::string toString() const;

	// Operator Overloads
	bool operator<(const PlayingCard& card2) const;
	bool operator<=(const PlayingCard& card2) const;
	bool operator>(const PlayingCard& card2) const;
	bool operator>=(const PlayingCard& card2) const;
	bool operator==(const PlayingCard& card2) const;
	bool operator!=(const PlayingCard& card2) const;
	void operator=(const PlayingCard& card2);

private:
	// Private Data Members
	unsigned short int m_iFaceValue;
	std::string m_sFaceString;
	std::string m_sSuit;

	// Private Set Functions
	void setFaceString();
	void setFaceValue(unsigned short int newFaceValue);
	void setSuit(size_t suitIndex);
	void setSuit(const std::string& newSuit);
};

#endif