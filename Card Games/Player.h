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
	//Constructors & Deconstructor
	Player(); //default
	Player(const Player& oldPlayer); //copy
	virtual ~Player() { } //virtual deconstructor in case of dynamic memory

	//Public Static Data Members
	static const unsigned int s_iSTARTINGCREDITS = 2500;

	//Set and Get Functions
	void setName(std::string newName);
	std::string getName() const;
	unsigned int getCredits() const;
	unsigned int getCurrentBet() const;
	void setActiveStatus(bool newStatus);
	bool getActiveStatus() const;
	virtual unsigned short int getHandCount() const = 0;
	virtual size_t getHandSize() const = 0;
	std::string getHandRankString() const;
	unsigned short int getHandRankValue() const;
	void setRaisesLeft(unsigned short int maxRaises);

	//Public Member Functions
	unsigned int placeBuyIn(unsigned int iBuyIn);
	unsigned int placeCurrentBet();
	void replaceCardAt(size_t index, const PlayingCard& newCard);


	virtual void addCard(const PlayingCard& card) = 0;
	void clearHand(); //might want to make this virtual
	virtual unsigned int determineBet(unsigned int minBet) = 0;
	virtual void determineHandRank() = 0;
	virtual void givePayout(unsigned int payout);
	virtual void printCards() const;
	virtual std::vector<size_t> determineReplaceCardsIndexes() = 0;


	Hand5 getHand() const;

protected:
	//Protected Data Members
	std::string m_sName;
	bool m_bActiveStatus;
	unsigned int m_iCredits;
	unsigned int m_iCurrentBet;
	unsigned short int m_iRaisesLeft;
	//should also have some kind of hand (use a generic base class?)
	Hand5* m_pHand;


	void callBehavior(unsigned int prevBet);

	void foldBehavior();
	void forcedFold();

	virtual void raiseBehavior(unsigned int prevBet) = 0;

private:
};

#endif