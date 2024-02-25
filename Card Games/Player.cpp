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

//Public Member Functions
void Player::givePayout(unsigned int payout) {

}

//Generic "placeBet" function
unsigned int Player::placeBet(unsigned int bet) {
	m_iCredits -= bet;
	return bet;
}

void Player::printCards() const {

}

//Testing Functions
Hand5 Player::getHand() const {
	return *m_pHand;
}