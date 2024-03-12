/*
*	Class Definitions: Hand5
* 
*	@author: Trenton Schacht
* 
*	@purpose:	Simulates a hand of five playing cards.
*				Uses an array to store playing cards.
* 
*			Provides the following functionalities:
*				- Stream insertion via base class & print function.
*				- Get functions: rankString, rankValue, cardPtrAt, numOfTieBreakers, 
*									tieBreakerAt, tieBreakersAll
*				- Set functions: setRank
*				- Public services: addCard, clearHand, count, print, printHandNumbered, 
*									replaceCardAt, size
*/


// Header Files
#include <algorithm>
#include <stdexcept>
#include "Hand5.h"

using namespace std;



//Constructors
Hand5::Hand5() {
	m_iRank = 0;
} //dont use set function, the hand will be empty initially

//Copy Constructor
Hand5::Hand5(const Hand5& oldHand) {
	this->m_iRank = oldHand.m_iRank;
	this->m_Cards = oldHand.m_Cards;
	this->m_ptrsTieBreakers = oldHand.m_ptrsTieBreakers;
}

Hand5::~Hand5() {
	;
}



// Public Get and Set Functions

/*	Public Get Functions
*
*	@note:	All get functions have the following parameters and respective return types.
*			'getAt' functions do bounds checking and throw null pointers if index is invalid.
*
*	@param: 'getAt' functions have an index as parameter, otherwise void.
*
*	@return: Respective type of each private/protected data member.
*/

const PlayingCard* Hand5::getCPtrCardAt(size_t index) const {
	try {
		const PlayingCard* retPtr = &m_Cards.at(index);
		return retPtr;
	}
	catch (const out_of_range& e) {
		cout << "ERROR: " << e.what() << endl;
		return nullptr;
	}
} //end of "getCPtrCardAt"


size_t Hand5::getNumOfTieBreakers() const {
	return m_ptrsTieBreakers.size();
} //end of "getNumOfTieBreakers"


const PlayingCard* Hand5::getTieBreakerAt(size_t index) const {
	try {
		return m_ptrsTieBreakers.at(index);
	}
	catch (const out_of_range& e) {
		cout << "ERROR: " << e.what() << endl;
		return nullptr;
	}
} //end of "getTieBreakerAt"


vector<const PlayingCard*> Hand5::getTieBreakersAll() const {
	return m_ptrsTieBreakers;
} //end of "getTieBreakersAll"


/*	setRank
* 
*	@note:	Internally sets the rank based on cards in hand.
*			Uses private functions to check for matches, straights, and flushes.
*			After rank is determined, calls private storeTieBreakers function
*				for later hand comparisons.
*			Potential Hands (In probabilty order, greatest to least):
*				(0) High Card
*				(1) Pair
*				(2) Two Pair
*				(3) Three of a Kind
*				(4) Straight
*				(5) Flush
*				(6) Full House
*				(7) Four of a Kind
*				(8) Straight Flush
*				(9) Royal Flush
* 
*	@param: void
* 
*	@return: void
*/
void Hand5::setRank() {
	//Variables used for determining rank
	vector<pair<const PlayingCard*, unsigned short int>> matches = findMatches();
	bool bStraight = checkStraight();
	bool bFlush = checkFlush();

	//Logic to determine rank from previous checks
	if (!bStraight && !bFlush) {
		if (matches.size() == 0) {
			//High card
			m_iRank = 0;
		}
		else if (matches.size() == 1) {
			if (get<1>(matches[0]) == 2) {
				//Pair
				m_iRank = 1;
			}
			else if (get<1>(matches[0]) == 3) {
				//Three of a kind
				m_iRank = 3;
			}
			else if (get<1>(matches[0]) == 4) {
				//Four of a kind
				m_iRank = 7;
			}
		}
		else if (matches.size() == 2) {
			if (get<1>(matches[0]) == 2 && get<1>(matches[1]) == 2) {
				//Two pair
				m_iRank = 2;
			}
			else {
				//Full House
				m_iRank = 6;
			}
		}
	}
	else if (bStraight && !bFlush) {
		//Straight
		m_iRank = 4;
	}
	else if (bFlush && !bStraight) {
		//Flush
		m_iRank = 5;
	}
	else {
		//Check for Royal Flush (checks if there is an Ace and a King in hand)
		if (any_of(m_Cards.cbegin(), m_Cards.cend(), [](PlayingCard card) { return card.getFaceString() == PlayingCard::s_CardFaces[1]; })
			&& any_of(m_Cards.cbegin(), m_Cards.cend(), [](PlayingCard card) { return card.getFaceString() == PlayingCard::s_CardFaces[13]; }))
		{
			//Royal Flush
			m_iRank = 9;
		}
		else {
			//Straight Flush
			m_iRank = 8;
		}
	}
	storeTieBreakers(matches);
}



// Public Services

/*	addCard
* 
*	@note:	Only adds cards if there are "blank" cards in hand.
*			Replaces the blank cards, will catch exception if hand is full.
* 
*	@param: Constant reference to the card being added.
* 
*	@return: void
*/
void Hand5::addCard(const PlayingCard& card) {
	try {
		m_Cards.at(count()) = card;
	}
	catch (const out_of_range& e) {
		cout << "Exception occurred: " << e.what();
	}
} //end of "addCard"


/*	clearHand
* 
*	@note: Resets hand to an "empty hand" as if it was just created.
* 
*	@param: void
* 
*	@return: void
*/
void Hand5::clearHand() {
	m_ptrsTieBreakers.clear();
	m_Cards.fill(PlayingCard());
	m_iRank = 0;
} //end of "clearHand"


/*	count
* 
*	@note: Not capacity.
* 
*	@param: void
* 
*	@return: Number of non-"blank" cards in hand.
*/
unsigned short int Hand5::count() const {
	return (unsigned short int)count_if(m_Cards.cbegin(), m_Cards.cend(), [](PlayingCard c) { return !c.isEmpty(); });
} //end of "count"


/*	print
* 
*	@note:	Called from base class "Hand", used to achieve
*			polymorphic behavior with "<<" operator.
* 
*	@param: Output stream.
*
*	@return: void
*/
void Hand5::print(ostream& output) const {
	for (PlayingCard card : m_Cards) {
		output << card << endl;
	}

	output << "Hand rank is: " << Hand::s_HandRanks[m_iRank] << endl;
} //end of "print"


/*	printNumberedHand
* 
*	@note:	Not to be confused with "print", 
*				directly uses cout to print hand.
*			Numbers each card that could be used to
*				distinguish cards and take user input.
* 
*	@param: void
* 
*	@return: void
*/
void Hand5::printHandNumbered() const {
	for (size_t i = 0; i < m_Cards.size(); ++i) {
		cout << '(' << i + 1 << ") " << m_Cards.at(i) << endl;
	}
	cout << "Hand rank is: " << s_HandRanks.at(m_iRank) << endl;
} //end of "printHandNumbered"


/*	replaceCardAt
* 
*	@note:	Performs bounds checking on index and rethrows exceptions.
* 
*	@param: Index to replace [0, 4] and new card.
* 
*	@return: void
* 
*	@throw: out_of_range
*/
void Hand5::replaceCardAt(size_t index, const PlayingCard& card) {
	try {
		m_Cards.at(index) = card;
	}
	catch (const out_of_range& e) {
		cout << "Exception occurred: " << e.what();
		throw e;
	}
} //end of "replaceCardAt"


/*	size
* 
*	@param: void
* 
*	@return: Capacity of hand container.
*/
size_t Hand5::size() const {
	return m_Cards.size();
} //end of "size"



// Operator Overloads

/*	operator<
* 
*	@note:	Enables polymorphic behavior for relational operators.
*			All other operators are defined in base class.
*			Compares the stored hand rank, and breaks any
*				ties that may arise.
* 
*	@param: Right hand side of comparison.(ex. B in A < B)
* 
*	@return: bool
*/
bool Hand5::operator<(const Hand& secondHand) const {
	if (this->m_iRank < secondHand.getRankValue()) {
		return true;
	}
	else if (this->m_iRank == secondHand.getRankValue()) {
		//Tie needs to be broken
		const Hand5& secondHandCast = dynamic_cast<const Hand5&>(secondHand);
		if (breakTie(this, &secondHandCast) == 1) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
} //end of "operator<"



// Private Member Functions

/*	breakTie
* 
*	@note: Return is based on which hand is considered "greater".
* 
*	@param: Two pointers to hands being compared.
* 
*	@return: -1 for hand1, 1 for hand2, and 0 if hands are completely tied.
*/
int Hand5::breakTie(const Hand5* hand1, const Hand5* hand2) const {
	//Check for empty tieBreakers vector (Royal Flush Tie)
	if (hand1->m_ptrsTieBreakers.size() == 0) {
		return 0;
	}
	
	//Check for all other ties
	pair<vector<const PlayingCard*>::const_iterator, 
		vector<const PlayingCard*>::const_iterator> mmRet 
			= mismatch(hand1->m_ptrsTieBreakers.cbegin(), hand1->m_ptrsTieBreakers.cend(), 
						hand2->m_ptrsTieBreakers.cbegin(), hand2->m_ptrsTieBreakers.cend(), 
						[](const PlayingCard* lhs, const PlayingCard* rhs) { return *lhs == *rhs; });
	
	//Use returned pair of mismatched tieBreakers to determine the outcome of the tie break
	if (get<0>(mmRet) == hand1->m_ptrsTieBreakers.cend() || get<1>(mmRet) == hand2->m_ptrsTieBreakers.cend()) {
		return 0;
	}
	else if (**get<0>(mmRet) < **get<1>(mmRet)) {
		return 1;
	}
	else {
		return -1;
	}
} //end of "breakTie"


/*	checkFlush
* 
*	@note: Searches for consecutive cards that have the same suit.
* 
*	@param: void
* 
*	@return: bool
*/
bool Hand5::checkFlush() const {
	return search_n(m_Cards.cbegin(), m_Cards.cend(), m_Cards.size(), m_Cards[0].getSuit(),
		[](PlayingCard card, string firstCardSuit) { return card.getSuit() == firstCardSuit; })
		!= m_Cards.cend();
} //end of "checkFlush"


/*	checkStraight
* 
*	@note:	Checks for both Ace high (10, J, Q, K , A)
*				and Ace low (A, 2, 3, 4, 5) straights.
* 
*	@param: void
* 
*	@return: bool
*/
bool Hand5::checkStraight() const {
	int straightCounter = 1;
	bool bStraight = true;
	auto itCurrentCard = max_element(m_Cards.cbegin(), m_Cards.cend());

	//Check if maximum card is an Ace
	if (itCurrentCard->getFaceString() == PlayingCard::s_CardFaces[1]) {
		//Check for an Ace Low Straight (searches for a Duece as well)
		auto itMinCard = min_element(m_Cards.cbegin(), m_Cards.cend());
		if (itMinCard->getFaceString() == PlayingCard::s_CardFaces[2]) {
			//Update counter to reflect Ace & Duece
			++straightCounter;

			//Loop to iterate through the remaining cards to check for next card in straight
			while (bStraight) {
				if (straightCounter == m_Cards.size()) {
					return true;
				}

				try {
					if ((itMinCard = find_if(m_Cards.cbegin(), m_Cards.cend(),
						[&itMinCard](PlayingCard otherCard) { return otherCard.getFaceString() == PlayingCard::s_CardFaces.at(itMinCard->getFaceValue() + 1); }))
						!= m_Cards.cend())
					{
						++straightCounter;
					}
					else {
						bStraight = false;
					}
				}
				catch (out_of_range& e) {
					//this is if there is an error with the "at()" function
					cout << "ERROR: " << e.what() << endl;
				}
			}
		}
	} //end of Ace Low Straight Check

	//Reset variables for normal straight check, finds minimum card now
	bStraight = true;
	straightCounter = 1;
	itCurrentCard = min_element(m_Cards.cbegin(), m_Cards.cend());

	//Loop to iterate through remaining cards to check for next card in straight
	while (bStraight) {
		if (straightCounter == m_Cards.size()) {
			return true;
		}

		try {
			//Special check if current card is a king, as below logic does not work since "Ace" is stored at beginning of card faces array.
			if (itCurrentCard->getFaceString() == PlayingCard::s_CardFaces[13]) {
				if (straightCounter == m_Cards.size() - 1) {
					if (find_if(m_Cards.cbegin(), m_Cards.cend(), [](PlayingCard card) { return card.getFaceString() == PlayingCard::s_CardFaces[1]; }) != m_Cards.cend()) {
						return true;
					}
				}
				bStraight = false;
			}
			//Search if next card in straight is in hand
			else if ((itCurrentCard = find_if(m_Cards.cbegin(), m_Cards.cend(),
										[&itCurrentCard](PlayingCard otherCard) { return otherCard.getFaceString() == PlayingCard::s_CardFaces.at(itCurrentCard->getFaceValue() + 1); }))
						!= m_Cards.cend())
			{
				++straightCounter;
			}
			else {
				bStraight = false;
			}
		}
		catch (const out_of_range& e) {
			//this is if there is an error with the "at()" function
			cout << "ERROR: " << e.what() << endl;
		}
	}

	return bStraight;
} //end of "checkStraight"


/*	findMatches
* 
*	@note: If no matches are found a default vector of the respective type is returned.
* 
*	@param: void
* 
*	@return: Vector storing any matches found. 
*			 A pair is used to store both the size of the match
*				and a pointer to one of the cards in the match.
*/
vector<pair<const PlayingCard*, unsigned short int>> Hand5::findMatches() const {
	//Vector to store whether a pair/three/four or multi match was found and with what cards
	vector <pair<const PlayingCard*, unsigned short int>> matchesVec;

	//Loops through all but last card (no need to check final card, all comparisons have been completed)
	for (array<PlayingCard, 5>::const_iterator cardIt = m_Cards.cbegin(); cardIt != m_Cards.cend() - 1; ++cardIt)
	{
		//Checks that the current card faceValue is not already stored inside matchesVec
		if (all_of(matchesVec.cbegin(), matchesVec.cend(),
			[&cardIt](pair<const PlayingCard*, unsigned short int> match) { return (*get<0>(match)) != *cardIt; }))
		{
			//This counts the number of equal cards for each "pass" through the array
			int equalCardCount = (int)std::count(cardIt + 1, m_Cards.cend(), *cardIt);

			if (equalCardCount > 0)
			{
				//Increment equalCardCount to account for card being used as comparison
				++equalCardCount;

				//Store into vector to pull for tieBreakers later
				pair<const PlayingCard*, unsigned short int> match(&(*cardIt), equalCardCount);
				matchesVec.push_back(match);
			}
		}
	}

	return matchesVec;
} //end of "findMatches"


/*	storeTieBreakers
* 
*	@note:	Stores appropriate number of pointers in protected data member m_ptrsTieBreakers
*				based on hand's rank.
* 
*	@param:	Vector of matches found within hand.
* 
*	@return: void
*/
void Hand5::storeTieBreakers(const vector<pair<const PlayingCard*, unsigned short int>>& matches) {
	switch (m_iRank)
	{
		case 0: // High Card - done and working
		{
			//needs to store all 5 cards (order of faceValue)
			for (auto itCard = m_Cards.cbegin(); itCard != m_Cards.cend(); ++itCard) {
				m_ptrsTieBreakers.push_back(&(*itCard));
			}
			sort(m_ptrsTieBreakers.begin(), m_ptrsTieBreakers.end(),
				[](const PlayingCard* lhs, const PlayingCard* rhs) { return *lhs > *rhs; });
			break;
		}
		case 1: // Pair  - done and working
		{
			//needs pair + 3 cards (order of faceValue)
			m_ptrsTieBreakers.push_back(get<0>(matches[0]));
			for (auto itCard = m_Cards.cbegin(); itCard != m_Cards.cend(); ++itCard) {
				if (*itCard != *m_ptrsTieBreakers[0]) {
					m_ptrsTieBreakers.push_back(&(*itCard));
				}
			}
			sort(m_ptrsTieBreakers.begin() + 1, m_ptrsTieBreakers.end(),
				[](const PlayingCard* lhs, const PlayingCard* rhs) { return *lhs > *rhs; });
			break;
		}
		case 2: // Two Pair - done and working
		{
			//needs pair + pair + 1 card (order of faceValue)
			m_ptrsTieBreakers.push_back(get<0>(matches[0]));
			m_ptrsTieBreakers.push_back(get<0>(matches[1]));
			//If tieBreakers were put into vector in incorrect order, swap them
			if (*get<0>(matches[0]) < *get<0>(matches[1])) {
				swap(m_ptrsTieBreakers[0], m_ptrsTieBreakers[1]);
			}
			//find and add final tiebreaker card
			for (auto itCard = m_Cards.cbegin(); itCard != m_Cards.cend(); ++itCard) {
				if (*itCard != *m_ptrsTieBreakers[0] && *itCard != *m_ptrsTieBreakers[1]) {
					m_ptrsTieBreakers.push_back(&(*itCard));
				}
			}
			break;
		}
		case 3: // Three of a Kind - done and working
		{
			//needs 3k + 2 cards (order of faceValue)
			m_ptrsTieBreakers.push_back(get<0>(matches[0]));
			for (auto itCard = m_Cards.cbegin(); itCard != m_Cards.cend(); ++itCard) {
				if (*itCard != *m_ptrsTieBreakers[0]) {
					m_ptrsTieBreakers.push_back(&(*itCard));
				}
			}
			sort(m_ptrsTieBreakers.begin() + 1, m_ptrsTieBreakers.end(),
				[](const PlayingCard* lhs, const PlayingCard* rhs) { return *lhs > *rhs; });
			break;
		}
		case 4: // Straight - done and working
		{
			//needs 1 card (high card)
			m_ptrsTieBreakers.push_back(&(*max_element(m_Cards.cbegin(), m_Cards.cend())));
			break;
		}
		case 5: // Flush - done and working
		{
			//needs all 5 cards (order of faceValue)
			for (auto itCard = m_Cards.cbegin(); itCard != m_Cards.cend(); ++itCard) {
				m_ptrsTieBreakers.push_back(&(*itCard));
			}
			sort(m_ptrsTieBreakers.begin(), m_ptrsTieBreakers.end(),
				[](const PlayingCard* lhs, const PlayingCard* rhs) { return *lhs > *rhs; });
			break;
		}
		case 6: // Full House - done and working
		{
			//needs 3k + pair
			m_ptrsTieBreakers.push_back(get<0>(matches[0]));
			m_ptrsTieBreakers.push_back(get<0>(matches[1]));
			//If tieBreakers were put into vector in incorrect order, swap them
			if (get<1>(matches[0]) < get<1>(matches[1])) {
				swap(m_ptrsTieBreakers[0], m_ptrsTieBreakers[1]);
			}
			break;
		}
		case 7: // Four of a Kind - done and working
		{
			//needs 4k + 1 card 
			m_ptrsTieBreakers.push_back(get<0>(matches[0]));
			for (auto itCard = m_Cards.cbegin(); itCard != m_Cards.cend(); ++itCard) {
				if (*itCard != *m_ptrsTieBreakers[0]) {
					m_ptrsTieBreakers.push_back(&(*itCard));
				}
			}
			sort(m_ptrsTieBreakers.begin() + 1, m_ptrsTieBreakers.end(),
				[](const PlayingCard* lhs, const PlayingCard* rhs) { return *lhs > *rhs; });
			break;
		}
		case 8: // Straight Flush - done and working
		{
			//needs 1 card (high card)
			m_ptrsTieBreakers.push_back(&(*max_element(m_Cards.cbegin(), m_Cards.cend())));
			break;
		}
		case 9: // Royal Flush - DONE
		{
			//no need to store any tieBreakers, all Royal Flushes are of equal value
			break;
		}
		default: // Errors
		{
			cout << "Error with \"m_iRank\" member's stored value: " << m_iRank << endl;
			break;
		}
	}
} //end of "storeTieBreakers"