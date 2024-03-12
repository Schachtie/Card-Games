/*
*	Class Definitions: Player
* 
*	@author: Trenton Schacht
* 
*	@purpose:	Abstract base class of player hierarchy. 
*				Written to be extensible to different types of players
*					such as user/npc or different hand sizes.
* 
*			Provides the following functionalities
*				- Get functions: activeStatus, credits, currentBet, handPtr,
*									handRankString, handRankValue, name
*				- Virtual Get functions: handCount, handSize
*				- Set functions: activeStatus, raisesLeft
*				- Public Services: clearHand, givePayout, placeBuyIn, 
*									placeCurrentBet, replaceCardAt
*				- Virtual Public services: addCard, determineBet, determineHandRank
*											determineReplaceCardsIndexes
*/


// Header Files
#include "Player.h"

using namespace std;



// Constructors
Player::Player() {
	m_bActiveStatus = true;
	m_iCredits = s_iSTARTINGCREDITS;
	m_iCurrentBet = 0;
	m_iRaisesLeft = 0;
	m_pHand = nullptr;
} //end of "Default Constructor"



// Public Get and Set Functions

/*	Public Get Functions
*
*	@notes: All get functions have the following parameters and respective return types.
*
*	@params: void
*
*	@return: Respective type of each private data member.
*/

bool Player::getActiveStatus() const {
	return m_bActiveStatus;
} //end of "getActiveStatus"


unsigned int Player::getCredits() const {
	return m_iCredits;
} //end of "getCredits"


unsigned int Player::getCurrentBet() const {
	return m_iCurrentBet;
} //end of "getCurrentBet"


const Hand* Player::getHandPtr() const {
	return m_pHand;
} //end of "getHandPtr"


string Player::getHandRankString() const {
	return m_pHand->getRankString();
} //end of "getHandRankString"


unsigned short int Player::getHandRankValue() const {
	return m_pHand->getRankValue();
} //end of "getHandRankValue"


string Player::getName() const {
	return m_sName;
} //end of "getName"


/*	Public Set Functions
*
*	@note:	All set functions have the following parameters and respective return types.
*
*	@param: Respective type of each private/protected data member.
*
*	@return: void
*/

void Player::setActiveStatus(bool newStatus) {
	if (m_bActiveStatus != newStatus) {
		m_bActiveStatus = newStatus;
	}
} //end of "setActiveStatus"


void Player::setRaisesLeft(unsigned short int maxRaises) {
	m_iRaisesLeft = maxRaises;
} //end of "setRaisesLeft"



// Public Services

/*	clearHand
* 
*	@note: Calls polymorphic clearHand function to reset hand based on type.
* 
*	@param: void
* 
*	@return: void
*/
void Player::clearHand() {
	m_pHand->clearHand();
} //end of "clearHand"


/*	givePayout
* 
*	@note: Adds payout to private credit data member.
* 
*	@param: Amount of payout.
* 
*	@return: void
*/
void Player::givePayout(unsigned int payout) {
	m_iCredits += payout;
} //end of "givePayout"


/*	placeBuyIn
* 
*	@note:	Validates that player can buy in to game.
*			Otherwise will disable player.
*			Return should be added to pot.
* 
*	@param: Buy in amount.
* 
*	@return: Credits to be added to pot.
*/
unsigned int Player::placeBuyIn(unsigned int iBuyIn) {
	if (m_iCredits >= iBuyIn) {
		m_iCredits -= iBuyIn;
	}
	else {
		iBuyIn = 0;
		m_bActiveStatus = false;
	}
	return iBuyIn;
} //end of "placeBuyIn"


/*	placeCurrentBet
*
*	@note: Saves stored bet, resets private member variable m_iCurrentBet, applies bet to player's credits.
*
*	@param: void
*
*	@return: Credits to add to pot.
*/
unsigned int Player::placeCurrentBet() {
	unsigned int finalBet = m_iCurrentBet;
	m_iCurrentBet = 0;
	m_iCredits -= finalBet;
	return finalBet;
} //end of "placeCurrentBet"


/*	replaceCardAt
* 
*	@note:	Attempts to replace card at given index.
*			Will rethrow exception if encountered.
* 
*	@param: Card index to replace, card to replace with.
* 
*	@return: void
* 
*	@throw: out_of_range
*/
void Player::replaceCardAt(size_t index, const PlayingCard& card) {
	try {
		m_pHand->replaceCardAt(index, card);
	}
	catch (const out_of_range& e) {
		cout << "Exception occurred: " << e.what();
		throw e;
	}
} //end of "replaceCardAt"



// Protected Member Functions

/*	callBehavior
* 
*	@note:	Call is for agreeing to previous bet without raising it.
*			Announces player's behavior.
* 
*	@param: Previous bet amount.
* 
*	@return: void
*/
void Player::callBehavior(unsigned int prevBet) {
	m_iCurrentBet = prevBet;
	cout << '\t' << m_sName << " called the previous bet (" << prevBet << ")." << endl;
} //end of "callBehavior"


/*	foldBehavior
* 
*	@note: Disables player and announces behavior.
* 
*	@param: void
* 
*	@return: void
*/
void Player::foldBehavior() {
	m_bActiveStatus = false;
	cout << '\t' << m_sName << " folded." << endl;
} //end of "foldBehavior"


/*	forcedFold
*
*	@note: Intended to be called when player must fold due to lack of credits.
* 
*	@param: void
* 
*	@return: void
*/
void Player::forcedFold() {
	cout << '\t' << m_sName << " doesn't have enough credits and folded." << endl;
	m_bActiveStatus = false;
} //end of "forcedFold"