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
	Hand5(const Hand5& oldHand); //copy
	//Destructor

	//Public Data Members
	static const std::array<std::string, 10> s_HandRanks;

	//Set and Get Functions
	Hand5 getHand() const;
	unsigned short int getRankValue() const;
	std::string getRankString() const;
	void setRank();

	//Public Member Functions
	void addCard(const PlayingCard& card);
	int count() const;
	void printHandStrings() const;
	void printHandArt() const;
	void replaceCardAt(size_t index, const PlayingCard& newCard);
	size_t size() const;


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