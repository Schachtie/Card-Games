/*
*	Class Definitions: Player5Card
* 
*	@author: Trenton Schacht
* 
*	@purpose:	Abstract derived class of "Player".
*				Written for players that have a hand that contains 5 card objects.
*				Defines common services between NPC and User players.
* 
*			Provides the following functionalities:
*				- Virtual final Get functions: handCount, handSize
*				- Virtual final Public services: addCard, determineHandRank
*/


// Header Files
#include "Player5Card.h"

using namespace std;



// Constructor and Destructor

//Default Constructor
Player5Card::Player5Card() {
	m_pHand = new Hand5();
} //end of "Default Constructor"


//Destructor
Player5Card::~Player5Card() {
	delete m_pHand;
} //end of "Destructor"



// Public Virtual Get Functions

/*	Public Get Functions
*
*	@note:	All get functions have the following parameters and respective return types.
*			'getAt' functions do bounds checking and throw null pointers if index is invalid.
*
*	@param: 'getAt' functions have an index as parameter, otherwise void.
*
*	@return: Respective type of each private/protected data member.
*/

unsigned short int Player5Card::getHandCount() const {
	return m_pHand->count();
} //end of "getHandCount"


size_t Player5Card::getHandSize() const {
	return m_pHand->size();
} //end of "getHandSize"



// Public Virtual Services

/*	addCard
* 
*	@note: Calls polymorphic Hand function to attempt to add card appropriately.
* 
*	@param: Card to be added.
* 
*	@return: void
*/
void Player5Card::addCard(const PlayingCard& card) {
	m_pHand->addCard(card);
} //end of "addCard"


/*	determineHandRank
* 
*	@note: Calls polymorphic Hand function to internally set the hand's rank.
* 
*	@param: void
* 
*	@return: void
*/
void Player5Card::determineHandRank() {
	m_pHand->setRank();
} //end of "determineHandRank"