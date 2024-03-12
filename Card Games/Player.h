/*
*	Class Header: Player
*/

#ifndef PLAYER_H
#define PLAYER_H

//Header Files
#include <string>
#include "Hand5.h"

class Player
{
public:
	//Constructors and Destructor
	Player(); //Default
	virtual ~Player() { } //virtual destructor in case of dynamic memory

	// Public Static Data Members
	static const unsigned int s_iSTARTINGCREDITS = 2500;

	// Public Get and Set Functions
	bool getActiveStatus() const;
	unsigned int getCredits() const;
	unsigned int getCurrentBet() const;
	const Hand* getHandPtr() const;
	std::string getHandRankString() const;
	unsigned short int getHandRankValue() const;
	std::string getName() const;
	void setActiveStatus(bool newStatus);
	void setRaisesLeft(unsigned short int maxRaises);

	// Public Virtual Get Functions
	virtual unsigned short int getHandCount() const = 0;
	virtual size_t getHandSize() const = 0;

	// Public Services
	void clearHand();
	void givePayout(unsigned int payout);
	unsigned int placeBuyIn(unsigned int iBuyIn);
	unsigned int placeCurrentBet();
	void replaceCardAt(size_t index, const PlayingCard& newCard);

	// Public Pure Virtual Services
	virtual void addCard(const PlayingCard& card) = 0;
	virtual unsigned int determineBet(unsigned int minBet) = 0;
	virtual void determineHandRank() = 0;
	virtual std::vector<size_t> determineReplaceCardsIndexes() = 0;

protected:
	// Protected Data Members
	std::string m_sName;
	bool m_bActiveStatus;
	unsigned int m_iCredits;
	unsigned int m_iCurrentBet;
	unsigned short int m_iRaisesLeft;
	Hand* m_pHand;

	// Protected Member Functions
	void callBehavior(unsigned int prevBet);
	void foldBehavior();
	void forcedFold();

	// Protected Pure Virtual Member Functions
	virtual void raiseBehavior(unsigned int prevBet) = 0;

private:
};

#endif