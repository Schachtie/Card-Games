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
#include "Hand.h"

class Hand5 : public Hand
{
public:
	//Constructors
	Hand5(); //default
	Hand5(const Hand5& oldHand); //copy
	virtual ~Hand5(); //Destructor

	//Public Virtual Set and Get Functions
	virtual const PlayingCard* getCPtrCardAt(size_t index) const;
	virtual void setRank();
	virtual std::vector<const PlayingCard*> getTieBreakersAll() const;
	virtual const PlayingCard* getTieBreakerAt(size_t index) const;
	virtual size_t getNumOfTieBreakers() const;

	//Public Virtual Services
	virtual void addCard(const PlayingCard& card);
	virtual void clearHand();
	virtual unsigned short int count() const;
	virtual void printHandNumbered() const;
	virtual void replaceCardAt(size_t index, const PlayingCard& newCard);
	virtual size_t size() const;
	virtual void print(std::ostream& output) const;

	//Operator Overloads
	virtual bool operator<(const Hand& secondHand) const;

private:
	//Private Data Members
	std::array<PlayingCard, 5> m_Cards;

	//Private Member Functions
	int breakTie(const Hand5* hand1, const Hand5* hand2) const; //change return type to int
	std::vector<std::pair<const PlayingCard*, unsigned short int>> findMatches() const;
	bool checkStraight() const;
	bool checkFlush() const;
	void storeTieBreakers(const std::vector<std::pair<const PlayingCard*, unsigned short int>>& matches);
};

#endif