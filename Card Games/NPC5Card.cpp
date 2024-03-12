/*
*	Class Definitions: NPC5Card
* 
*	@author: Trenton Schacht
* 
*	@purpose:	Derived class of "Player and Player5Card".
*				Allows NPC creation and use for games that require a Hand5 Hand type.
* 
*			Provides the following functionalities:
*				- Virtual final Public services: determineBet, determineReplaceCardsIndexes
*/


// Header Files
#include "NPC5Card.h"

using namespace std;



// Static Private Data Members
mt19937 NPC5Card::s_RandGen(chrono::steady_clock::now().time_since_epoch().count());



// Constructors and Destructors

/*
*/
NPC5Card::NPC5Card() {
	m_sName = "NPC";
} //end of "Default Constructor"


/*
*/
NPC5Card::NPC5Card(char newName[10]) {
	m_sName = newName;
	m_sName += " (NPC)";
} //end of "Name Provided Constructor"



// Public Virtual Services

/*	determineBet
* 
*	@note: Randomly determines NPC bet behavior by rolling for each behavior (call, raise, fold).
* 
*	@param: Minimum bet, can be either game's minimum or previous bet that needs to be matched.
* 
*	@return: Player's new bet. Returns 0 if player folds.
*/
unsigned int NPC5Card::determineBet(unsigned int minBet) {
	unsigned int iBet = 0;
	//Check if player has enough credits to bet
	if (m_iCredits >= minBet) {
		//If player has raises left, roll to raise (25%)
		if (m_iRaisesLeft > 0 && rollNumber(1, 4) == 1) {
			raiseBehavior(minBet);
			return m_iCurrentBet;
		}
		else {
			//If player has a no face card roll to fold (90%)
			if (m_pHand->getRankValue() == 0 && m_pHand->getTieBreakerAt(0)->getFaceValue() <= 9
				&& m_pHand->getTieBreakerAt(0)->getFaceValue() != 1 && rollNumber(1, 10) != 1) 
			{
				foldBehavior();
				return 0;
			}
			else {
				callBehavior(minBet);
				return minBet;
			}
		}
	}
	//Player doesn't have enough credits to bet
	else {
		forcedFold();
		return 0;
	}
} //end of "determineBet"


/*	determineReplaceCardsIndexes
* 
*	@note:	Uses "storeReplaceCardIndexes" to store actual indexes.
*			Will not store any indexes of cards that are included in player's current rank,
*				unless player's rank is High Card.
* 
*	@param: void
* 
*	@return: Vector containing indexes of cards to replace [0, 4].
*/
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
} //end of "determineReplaceCardsIndexes"



// Protected Virtual Functions

/*	raiseBehavior
* 
*	@note:	Has 2 different raise types. Rolls to select type.
*			(1) Normal raise - (+ 5-10% of previous bet)
*			(2) High raise - (+ 75-100% of previous bet)
* 
*	@param: Previous player's bet, could also be minimum bet of game if player's turn is first.
* 
*	@return: void
*/
void NPC5Card::raiseBehavior(unsigned int prevBet) {
	unsigned int lowBound = 0;
	unsigned int highBound = 0;
	//Roll for "high raise" (10%)
	if (rollNumber(1, 10) == 1) {
		lowBound = static_cast<unsigned int>(ceil(1.75 * (prevBet + 1)));
		highBound = static_cast<unsigned int>(ceil(2.00 * (prevBet + 1)));
	}
	else {
		lowBound = static_cast<unsigned int>(ceil(1.05 * (prevBet + 1)));
		highBound = static_cast<unsigned int>(ceil(1.10 * (prevBet + 1)));
	}
	//Determine raise amount, decrement player's remaining raises, and announce to terminal
	m_iCurrentBet = rollNumber(lowBound, highBound);
	--m_iRaisesLeft;
	cout << '\t' << m_sName << " raised the bet to " << m_iCurrentBet << " credit" << ((m_iCurrentBet == 1) ? "." : "s.") << endl;
} //end of "raiseBehavior"



// Private Member Functions

/*	rollNumber
*
*	@note:	Specifically for unsigned int.
*
*	@param: Lower and upper bounds.
*
*	@return: Randomly generated number within provided range.
*/
unsigned int NPC5Card::rollNumber(unsigned int low, unsigned int high) {
	return uniform_int_distribution<unsigned int> {low, high}(s_RandGen);
} //end of "rollNumber"


/*	storeReplaceCardIndexes
* 
*	@note:	Only checks cards from supplied index onwards.
*			Only replaces cards that are not face cards (10, J, Q, K, A)
* 
*	@param:	Tiebreaker index to start check with, and vector to store indexes to replace.
* 
*	@return: void
*/
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
} //end of "storeReplaceCardIndexes"