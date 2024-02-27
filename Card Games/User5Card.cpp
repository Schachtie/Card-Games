/*
*	Class Definitions: User5Card
*/

//Header Files
#include "User5Card.h"

using namespace std;

//Default Constructor
User5Card::User5Card() {
	m_sName = "USER";
}

//Copy Constructor


//Public Member Functions

//Allows user to specify bet (need to actually code this)

unsigned int User5Card::determineBet(unsigned int minBet) {
	unsigned int bet = 0;

	//ask user for bet
	bet = minBet;

	//apply bet
	m_iCurrentBet = bet;

	//return bet
	return bet;
}

unsigned int User5Card::placeBet(unsigned int minBet) {
	unsigned int bet = 0;

	//ask user for bet
	bet = minBet;

	//apply bet
	m_iCredits -= bet;

	//return bet
	return bet;
}

void User5Card::printCards() const {

}

vector<size_t> User5Card::determineReplaceCardsIndexes() {
	vector<size_t> replaceIndexes;
	return replaceIndexes;
}
