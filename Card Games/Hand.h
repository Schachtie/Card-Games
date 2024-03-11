/*
*	Class Header: Hand5
* 
*			Note: Any derived classes must add their own container for cards.
*/

#ifndef HAND_H
#define HAND_H

//Header Files
#include <array>
#include <vector>
#include <string>
#include "PlayingCard.h"


class Hand
{
	//Overloaded stream insertion operator
	friend std::ostream& operator<<(std::ostream& output, const Hand& hand);

public:
	//Constructors and Destructor
	Hand(); //default
	virtual ~Hand(); //destructor

	//Public Static Hand Rank array
	static const std::array<std::string, 10> s_HandRanks;

	//Public Get Functions
	unsigned short int getRankValue() const;
	std::string getRankString() const;

	//Public Virtual Set and Get Functions
	virtual const PlayingCard* getCPtrCardAt(size_t index) const = 0;
	virtual void setRank() = 0;
	virtual std::vector<const PlayingCard*> getTieBreakersAll() const = 0;
	virtual const PlayingCard* getTieBreakerAt(size_t index) const = 0;
	virtual size_t getNumOfTieBreakers() const = 0;

	//Public Virtual Services
	virtual void addCard(const PlayingCard& card) = 0;
	virtual void clearHand() = 0;
	virtual unsigned short int count() const = 0;
	virtual void printHandNumbered() const = 0;
	virtual void replaceCardAt(size_t index, const PlayingCard& newCard) = 0;
	virtual size_t size() const = 0;
	virtual void print(std::ostream& output) const = 0;

	//Operator Overloads
	virtual bool operator<(const Hand& secondHand) const = 0; //should be virtual in base class
	bool operator<=(const Hand& secondHand) const;
	bool operator>(const Hand& secondHand) const;
	bool operator>=(const Hand& secondHand) const;
	bool operator==(const Hand& secondHand) const;
	bool operator!=(const Hand& secondHand) const;

protected:
	//Protected Data Members
	unsigned short int m_iRank;
	std::vector<const PlayingCard*> m_ptrsTieBreakers;

private:
};

#endif