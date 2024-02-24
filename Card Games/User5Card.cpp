/*
*	Class Definitions: User5Card
*/

//Header Files
#include "User5Card.h"

using namespace std;

//Default Constructor
User5Card::User5Card() {
	;
}

//Copy Constructor


//Public Member Functions
unsigned int User5Card::placeBet() {
	unsigned int bet = 0;

	//ask user for bet


	//apply bet
	iCredits -= bet;

	//return bet
	return bet;
}

void User5Card::printCards() const {

}

void User5Card::takeTurn() {
	;
}