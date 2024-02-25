/*
*	Class Definitions: Hand5
*/

/*
*	Working Notes:
*
*/

//Header Files
#include "NPC5Card.h"

using namespace std;

//Constructors and Destructors
NPC5Card::NPC5Card() {
	m_sName = "NPC";
}

//Public Member Functions

//Currently has NPCs place the minimum possible bet (add some dynamic betting)
unsigned int NPC5Card::placeBet(unsigned int minBet) {
	unsigned int bet = 0;
	if (m_iCredits >= minBet) {
		bet = minBet;
		m_iCredits -= bet;
	}
	else {
		cout << "Error calling NPC's placeBet function." << endl;
	}
	return bet;
}

void NPC5Card::printCards() {

}

void NPC5Card::takeTurn() {

}