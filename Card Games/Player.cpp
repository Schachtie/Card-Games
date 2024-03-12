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
	m_bActiveStatus = true;
	m_iCredits = s_iSTARTINGCREDITS;
	m_iCurrentBet = 0;
	m_iRaisesLeft = 0;
	m_pHand = nullptr;
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

void Player::setRaisesLeft(unsigned short int maxRaises) {
	m_iRaisesLeft = maxRaises;
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

//needs to validate buyIn 
unsigned int Player::placeBuyIn(unsigned int iBuyIn) {
	if (m_iCredits >= iBuyIn) {
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


const Hand* Player::getHandPtr() const {
	return m_pHand;
}


void Player::callBehavior(unsigned int prevBet) {
	m_iCurrentBet = prevBet;
	cout << '\t' << m_sName << " called the previous bet (" << prevBet << ")." << endl;
}

void Player::foldBehavior() {
	m_bActiveStatus = false;
	cout << '\t' << m_sName << " folded." << endl;
}

void Player::forcedFold() {
	cout << '\t' << m_sName << " doesn't have enough credits and folded." << endl;
	m_bActiveStatus = false;
}