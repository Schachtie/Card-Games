/*
*	Class Definitions: Player5Card
*/

//Header Files
#include "Player5Card.h"

using namespace std;

//Default Constructor
Player5Card::Player5Card() {
	m_sName = "Player 5 Card"; //can get rid of this potentially
	m_pHand = new Hand5();
}

//Copy Constructor

//Destructor
Player5Card::~Player5Card() {
	delete m_pHand;
}

//Public Member Functions (virtual)
void Player5Card::addCard(const PlayingCard& card) {
	m_pHand->addCard(card);
}

void Player5Card::determineHandRank() {
	m_pHand->setRank();
}

void Player5Card::givePayout(unsigned int payout) {
	//should have validation of maximum / overflow

	m_iCredits += payout;
}

void Player5Card::printCards() const {

}

//Public Member Functions
unsigned short int Player5Card::getHandCount() const {
	return m_pHand->count();
}

size_t Player5Card::getHandSize() const {
	return m_pHand->size();
}