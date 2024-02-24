/*
*	Class Definitions: Player5Card
*/

//Header Files
#include "Player5Card.h"

using namespace std;

//Default Constructor
Player5Card::Player5Card() {
	
}

//Copy Constructor


//Public Member Functions
void Player5Card::determineHandRank() {
	hand.setRank();
}

void Player5Card::givePayout(unsigned int payout) {
	//should have validation of maximum / overflow

	sName += payout;
}

void Player5Card::printCards() const {

}