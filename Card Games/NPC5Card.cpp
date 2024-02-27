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

//Public Member Functions

unsigned int NPC5Card::determineBet(unsigned int minBet) {
	unsigned int iBet = 0;
	//Check if player has enough credits to bet
	if (m_iCredits >= minBet) {
		//Use randomly generated number to determine betting behavior
		unsigned int randomRoll = rollNumber(1, 10);
		//Call/Fold roll (40%)
		if (randomRoll >= 1 && randomRoll <= 4) {
			//Checks if player has "High Card" as their rank, and a card that is a 9 or lower (excluding aces) and rolls for fold (90%)
			if (m_pHand->getRankValue() == 0 && m_pHand->getTieBreakerAt(0)->getFaceValue() <= 9 && m_pHand->getTieBreakerAt(0)->getFaceValue() != 1) {
				randomRoll = rollNumber(1, 10);
				if (randomRoll >= 1 && randomRoll <= 9) {
					m_bActiveStatus = false;
				}
				//No fold
				else {
					iBet = minBet;
				}
			}
			//Otherwise, have player call the previous bet
			else {
				iBet = minBet;
			}
		}
		//Raise (normal) (50%)
		else if (randomRoll >= 5 && randomRoll <= 9) {
			unsigned int lowBet = (unsigned int)ceil(1.0 * (minBet + 1) * 0.05);
			unsigned int highBet = (unsigned int)ceil(1.0 * (minBet + 1) * 0.10);
			iBet = minBet + rollNumber(lowBet, highBet);
		}
		//Raise (high, potential bluff) (10%)
		else if (randomRoll == 10) {
			unsigned int lowBet = (unsigned int)ceil(1.0 * (minBet + 1) * 0.75);
			unsigned int highBet = (unsigned int)ceil(1.0 * (minBet + 1) * 1.25);
			iBet = minBet + rollNumber(lowBet, highBet);
		}
		//Catch for any randomRoll incorrect generation
		else {
			//PUT ERROR MESSAGE
		}
	}
	//Player doesn't have enough credits to bet
	else {
		m_bActiveStatus = false;
	}

	//apply bet to private data member
	m_iCurrentBet = iBet;
	return iBet;
} //end of "determineBet()"

void NPC5Card::printCards() {

}

//look into rewritting this to avoid repeated code
vector<size_t> NPC5Card::determineReplaceCardsIndexes() {
	vector<size_t> replaceIndexes;
	
	switch (m_pHand->getRankValue()) {
		case 0: //High Card
		{
			//only replace cards that are worth less than a 10
			for (size_t tieBreakerIndex = 0; tieBreakerIndex < m_pHand->getNumOfTieBreakers(); ++tieBreakerIndex) {
				if (m_pHand->getTieBreakerAt(tieBreakerIndex)->getFaceValue() < 10
					&& m_pHand->getTieBreakerAt(tieBreakerIndex)->getFaceValue() != 1) {
					for (size_t counter = 0; counter < m_pHand->size(); ++counter) {
						if (m_pHand->getTieBreakerAt(tieBreakerIndex) == m_pHand->getCPtrCardAt(counter)) {
							replaceIndexes.push_back(counter);
							break;
						}
					}
				}
				
				
			}
			break;
		}
		case 1: //Pair
		{
			//Store replacement indexes
			for (size_t tieBreakerIndex = 1; tieBreakerIndex < m_pHand->getNumOfTieBreakers(); ++tieBreakerIndex) {
				for (size_t counter = 0; counter < m_pHand->size(); ++counter) {
					if (m_pHand->getTieBreakerAt(tieBreakerIndex) == m_pHand->getCPtrCardAt(counter)) {
						replaceIndexes.push_back(counter);
						break;
					}
				}
			}
			break;
		}
		case 2: //Two Pair
		{
			//Store replacement indexes
			for (size_t tieBreakerIndex = 2; tieBreakerIndex < m_pHand->getNumOfTieBreakers(); ++tieBreakerIndex) {
				for (size_t counter = 0; counter < m_pHand->size(); ++counter) {
					if (m_pHand->getTieBreakerAt(tieBreakerIndex) == m_pHand->getCPtrCardAt(counter)) {
						replaceIndexes.push_back(counter);
						break;
					}
				}
			}
			break;
		}
		case 3: //Three of a kind
		{
			for (size_t tieBreakerIndex = 1; tieBreakerIndex < m_pHand->getNumOfTieBreakers(); ++tieBreakerIndex) {
				for (size_t counter = 0; counter < m_pHand->size(); ++counter) {
					if (m_pHand->getTieBreakerAt(tieBreakerIndex) == m_pHand->getCPtrCardAt(counter)) {
						replaceIndexes.push_back(counter);
						break;
					}
				}
			}
			break;
		}
		case 7: //Four of a kind
		{
			//Store replacement indexes
			for (size_t tieBreakerIndex = 1; tieBreakerIndex < m_pHand->getNumOfTieBreakers(); ++tieBreakerIndex) {
				for (size_t counter = 0; counter < m_pHand->size(); ++counter) {
					if (m_pHand->getTieBreakerAt(tieBreakerIndex) == m_pHand->getCPtrCardAt(counter)) {
						replaceIndexes.push_back(counter);
						break;
					}
				}
			}
			break;
		}
	
		//No replacements
		case 4:
		case 5:
		case 6:
		case 8:
		case 9:
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