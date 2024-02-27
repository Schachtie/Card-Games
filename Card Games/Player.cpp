/*
*	Class Definitions: Hand5
*/

/*
*	Working Notes:
*
*/

//Header Files
#include "Player.h"

using namespace std;

//Constructors
Player::Player() {
	m_sName = "Player"; //can get rid of this potentially
	m_iCredits = 2500;
	m_iCurrentBet = 0;
	m_bActiveStatus = true;
}

Player::Player(const Player& oldPlayer) {

}

//Set and Get Functions
void Player::setName(string newName) {

}

string Player::getName() const {
	return m_sName;
}

unsigned int Player::getCurrentBet() const {
	return m_iCurrentBet;
}

unsigned int Player::getCredits() const {
	return m_iCredits;
}

void Player::setActiveStatus(bool newStatus) {
	if (m_bActiveStatus != newStatus) {
		m_bActiveStatus = newStatus;
	}
}

bool Player::getActiveStatus() const {
	return m_bActiveStatus;
}

string Player::getHandRankString() const {
	return m_pHand->getRankString();
}

unsigned short int Player::getHandRankValue() const {
	return m_pHand->getRankValue();
}

//Public Member Functions

/*	placeCurrentBet()
*	
*	Saves stored bet, resets private member variable m_iCurrentBet, applies bet to player's credits
*	
*	@params: none
* 
*	@return: unsigned int - credits bet (to add to pot)
*/
unsigned int Player::placeCurrentBet() {
	unsigned int finalBet = m_iCurrentBet;
	m_iCurrentBet = 0;
	m_iCredits -= finalBet;
	return finalBet;
}

void Player::replaceCardAt(size_t index, const PlayingCard& card) {
	try {
		m_pHand->replaceCardAt(index, card);
	}
	catch (const out_of_range& e) {
		cout << "Exception occurred: " << e.what();
		throw e;
	}
}

void Player::clearHand() {
	m_pHand->clearHand();
}

void Player::givePayout(unsigned int payout) {

}

//needs to validate buyIn (player must have twice the buyIn so they can bet)
unsigned int Player::placeBuyIn(unsigned int iBuyIn) {
	if (m_iCredits >= 2 * iBuyIn) {
		m_iCredits -= iBuyIn;
	}
	else {
		iBuyIn = 0;
		m_bActiveStatus = false;
	}
	return iBuyIn;
}

void Player::printCards() const {

}


Hand5 Player::getHand() const {
	return *m_pHand;
}