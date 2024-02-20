/*
*	Class Header: Hand5
*/

#ifndef HAND5_H
#define HAND5_H

//Header Files
#include <iostream>
#include <array>
#include <vector>
#include "PlayingCard.h"

class Hand5
{
	//Overloaded stream insertion operator
	friend std::ostream& operator<<(std::ostream& output, const Hand5& hand);

public:
	//Constructors
	Hand5(); //default
	Hand5(const Hand5& oldHand); //copy - not written
	//Destructor

	//Public Data Members
	static const std::array<std::string, 10> s_HandRanks;

	//Set and Get Functions
	void setRank(); //currently writing and testing
	unsigned short int getRankValue() const; //not written
		//setRank is private - only should be used within class itself
	std::string getRankString() const;

	//Public Member Functions
	size_t size() const;
	int count() const;
	void addCard(const PlayingCard& card);


	//Operator Overloads - these will need testing once determineRank has been written. currently all hands are equal as each hand's rank is 0 and all ptrsTieBreakers point to NULL
	bool operator<(const Hand5& secondHand) const;
	bool operator<=(const Hand5& secondHand) const;
	bool operator>(const Hand5& secondHand) const;
	bool operator>=(const Hand5& secondHand) const;
	bool operator==(const Hand5& secondHand) const;
	bool operator!=(const Hand5& secondHand) const;

	

private:
	//Private Data Members
	unsigned short int m_iRank;
	std::array<PlayingCard, 5> m_Cards;
	std::vector<const PlayingCard*> m_ptrsTieBreakers;

	//Private Member Functions
	const Hand5* breakTie(const Hand5* hand1, const Hand5* hand2) const;
	std::vector<std::pair<const PlayingCard*, unsigned short int>> findMatches() const;
	bool checkStraight() const;
	bool checkFlush() const;
	void storeTieBreakers(const std::vector<std::pair<const PlayingCard*, unsigned short int>>& matches);
};

#endif