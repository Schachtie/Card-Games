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

//Static Private Data Members
mt19937 NPC5Card::s_RandGen(chrono::steady_clock::now().time_since_epoch().count());

//Constructors and Destructors
NPC5Card::NPC5Card() {
	m_sName = "NPC";
}

//TESTING
NPC5Card::NPC5Card(char newName[10]) {
	/*m_bActiveStatus = true;
	m_iCredits = 2500;
	m_iCurrentBet = 0;
	m_iRaisesLeft = 2;
	*/
	m_sName = newName;
	m_sName += " (NPC)";
}

//Public Member Functions

//returns 0 if player folds or does not need to update their bet
unsigned int NPC5Card::determineBet(unsigned int minBet) {
	//Check if player has already placed the appropriate bet
	if (m_iCurrentBet == minBet) {
		return 0;
	}
	
	
	unsigned int iBet = 0;
	//Check if player has enough credits to bet
	if (m_iCredits >= minBet) {
		//If player has raises left, roll to raise (25%)
		if (m_iRaisesLeft > 0 && rollNumber(1, 4) == 1) {
			unsigned int lowBound = 0;
			unsigned int highBound = 0;
			//Roll for "high raise" (10%)
			if (rollNumber(1, 10) == 1) {
				lowBound = static_cast<unsigned int>(ceil(1.75 * (minBet + 1)));
				highBound = static_cast<unsigned int>(ceil(2.00 * (minBet + 1)));
			}
			else {
				lowBound = static_cast<unsigned int>(ceil(1.05 * (minBet + 1)));
				highBound = static_cast<unsigned int>(ceil(1.10 * (minBet + 1)));
			}
			//Determine raise amount, decrement player's remaining raises, and announce to terminal
			iBet = rollNumber(lowBound, highBound);
			--m_iRaisesLeft;
			m_iCurrentBet = iBet;
			cout << '\t' << m_sName << " raised the bet to " << iBet << " credit" << ((iBet == 1) ? "." : "s.") << endl;
		} //end of raise
		else {
			//If player has a no face card roll to fold (90%)
			if (m_pHand->getRankValue() == 0 && m_pHand->getTieBreakerAt(0)->getFaceValue() <= 9
				&& m_pHand->getTieBreakerAt(0)->getFaceValue() != 1 && rollNumber(1, 10) != 1) {
				m_bActiveStatus = false;
				cout << '\t' << m_sName << " folded." << endl;
			}
			else {
				iBet = minBet;
				m_iCurrentBet = iBet;
				cout << '\t' << m_sName << " called the previous bet (" << iBet << ")." << endl;
			}
		}
	}
	//Player doesn't have enough credits to bet
	else {
		m_bActiveStatus = false;
		cout << '\t' << m_sName << " was forced to fold. Not enough credits." << endl;
	}

	return iBet;
} //end of "determineBet()"

void NPC5Card::printCards() {

}

// add appropriate header comments
vector<size_t> NPC5Card::determineReplaceCardsIndexes() {
	vector<size_t> replaceIndexes;
	
	switch (m_pHand->getRankValue()) {
		//Check all tiebreakers for potential replacement
		case 0: //High Card
		{
			storeReplaceCardIndexes(0, &replaceIndexes);
			break;
		}
		//Check all tiebreakers that do not affect current rank (grouped by identical starting TB indexes)
		case 1: //Pair
		case 3: //Three of a kind
		case 7: //Four of a kind
		{
			storeReplaceCardIndexes(1, &replaceIndexes);
			break;
		}
		case 2: //Two Pair
		{
			storeReplaceCardIndexes(2, &replaceIndexes);
			break;
		}
	
		//No replacements
		case 4: //Straight
		case 5: //Flush
		case 6: //Full House
		case 8: //Straight Flush
		case 9:	//Royal Flush
		{
			break;
		}
	}

	return replaceIndexes;
}



//Private Member Functions
unsigned int NPC5Card::rollNumber(unsigned int low, unsigned int high) {
	return uniform_int_distribution<unsigned int> {low, high}(s_RandGen);
}

void NPC5Card::storeReplaceCardIndexes(size_t startingTBIndex, vector<size_t>* pStoredIndexes) {
	//Loop through each TB that is not associated with the player's rank
	for (size_t tieBreakerIndex = startingTBIndex; tieBreakerIndex < m_pHand->getNumOfTieBreakers(); ++tieBreakerIndex) {
		//Only replace cards that are not face cards (10, J, Q, K, A)
		if (m_pHand->getTieBreakerAt(tieBreakerIndex)->getFaceValue() < 10
			&& m_pHand->getTieBreakerAt(tieBreakerIndex)->getFaceValue() != 1) {
			//Loop through the hand and find the tiebreaker card
			for (size_t counter = 0; counter < m_pHand->size(); ++counter) {
				if (m_pHand->getTieBreakerAt(tieBreakerIndex) == m_pHand->getCPtrCardAt(counter)) {
					pStoredIndexes->push_back(counter);
					break;
				}
			}
		}
	}
}