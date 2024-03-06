/*
*	Class Definitions: Hand5
*/

/*
*	Working Notes:
*		(1) Might want to add validation of cards for setRank()
*/

//Header Files
#include "Hand5.h"
#include <algorithm>
#include <stdexcept>

using namespace std;

//Non Member Functions
ostream& operator<<(ostream& output, const Hand5& hand) {
	for (PlayingCard card : hand.m_Cards)
	{
		output << card << endl;
	}

	cout << "Hand rank is: " << Hand5::s_HandRanks[hand.m_iRank] << endl;

	return output;
}

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

//Public Data Members
const array<string, 10> Hand5::s_HandRanks = { "High Card", "Pair", "Two Pair", "Three of a Kind", "Straight", "Flush", "Full House", "Four of a Kind", "Straight Flush", "Royal Flush" };

//Public Set and Get Functions
const PlayingCard* Hand5::getCPtrCardAt(size_t index) const {
	try {
		const PlayingCard* retPtr = &m_Cards.at(index);
		return retPtr;
	}
	catch (const out_of_range& e) {
		return nullptr;
	}
}

unsigned short int Hand5::getRankValue() const {
	return m_iRank;
}

string Hand5::getRankString() const {
	return s_HandRanks[m_iRank];
}

void Hand5::setRank() {
	//Variables used for determining rank
	vector<pair<const PlayingCard*, unsigned short int>> matches = findMatches();
	bool bStraight = checkStraight();
	bool bFlush = checkFlush();

	//Probability (most to least)
		// High Card - (cmp)
		// Pair - stored
		// Two Pair - stored
		// Three of a kind - stored
		// Straight
		// Flush - stored
		// Full House (cmp)
		// Four of a kind - stored
		// Straight Flush (cmp)
		// Royal Flush (cmp)

	//Logic to determine rank from previous checks
	if (!bStraight && !bFlush)
	{
		if (matches.size() == 0)
		{
			//High card
			m_iRank = 0;
		}
		else if (matches.size() == 1)
		{
			if (get<1>(matches[0]) == 2)
			{
				//Pair
				m_iRank = 1;
			}
			else if (get<1>(matches[0]) == 3)
			{
				//Three of a kind
				m_iRank = 3;
			}
			else if (get<1>(matches[0]) == 4)
			{
				//Four of a kind
				m_iRank = 7;
			}
		}
		else if (matches.size() == 2)
		{
			if (get<1>(matches[0]) == 2 && get<1>(matches[1]) == 2)
			{
				//Two pair
				m_iRank = 2;
			}
			else
			{
				//Full House
				m_iRank = 6;
			}
		}
	}
	else if (bStraight && !bFlush)
	{
		//Straight
		m_iRank = 4;
	}
	else if (bFlush && !bStraight)
	{
		//Flush
		m_iRank = 5;
	}
	else
	{
		//Check for Royal Flush (checks if there is an Ace and a King in hand)
			//Royal Flush
		if (any_of(m_Cards.cbegin(), m_Cards.cend(), [](PlayingCard card) { return card.getFaceString() == PlayingCard::s_CardFaces[1]; })
			&& any_of(m_Cards.cbegin(), m_Cards.cend(), [](PlayingCard card) { return card.getFaceString() == PlayingCard::s_CardFaces[13]; }))
		{
			m_iRank = 9;
		}
		else
		{
			//Straight Flush
			m_iRank = 8;
		}
	}
	storeTieBreakers(matches);
}

vector<const PlayingCard*> Hand5::getTieBreakersAll() const {
	return m_ptrsTieBreakers;
}

const PlayingCard* Hand5::getTieBreakerAt(size_t index) const {
	try {
		return m_ptrsTieBreakers.at(index);
	}
	catch (const out_of_range& e) {
		return nullptr;
	}
}

size_t Hand5::getNumOfTieBreakers() const {
	return m_ptrsTieBreakers.size();
}

//Public Member Functions
size_t Hand5::size() const {
	return m_Cards.size();
}

unsigned short int Hand5::count() const {
	return (unsigned short int)count_if(m_Cards.cbegin(), m_Cards.cend(), [](PlayingCard c) { return !c.isEmpty(); });
}

void Hand5::addCard(const PlayingCard& card) {
	try
	{
		m_Cards.at(count()) = card;
	}
	catch (const out_of_range& e)
	{
		cout << "Exception occurred: " << e.what();
	}
}

void Hand5::clearHand() {
	m_ptrsTieBreakers.clear();
	m_Cards.fill(PlayingCard());
	m_iRank = 0;
}

void Hand5::replaceCardAt(size_t index, const PlayingCard& card) {
	try {
		m_Cards.at(index) = card;
	}
	catch (const out_of_range& e) {
		cout << "Exception occurred: " << e.what();
		throw e;
	}
}

void Hand5::printHandNumbered() const {
	for (size_t i = 0; i < m_Cards.size(); ++i) {
		cout << '(' << i << ") " << m_Cards.at(i) << endl;
	}
	cout << "Hand rank is: " << s_HandRanks.at(m_iRank) << endl;
}

//Operator Overloads
bool Hand5::operator<(const Hand5& secondHand) const {
	if (this->m_iRank < secondHand.m_iRank)
	{
		return true;
	}
	else if (this->m_iRank == secondHand.m_iRank)
	{
		//Tie needs to be broken
		const Hand5* breakResult = breakTie(this, &secondHand);
		
		if (breakResult == &secondHand)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

bool Hand5::operator<=(const Hand5& secondHand) const {
	return !(secondHand < *this);
}

bool Hand5::operator>(const Hand5& secondHand) const {
	return secondHand < *this;
}

bool Hand5::operator>=(const Hand5& secondHand) const {
	return !(*this < secondHand);
}

bool Hand5::operator==(const Hand5& secondHand) const {
	return !(*this < secondHand) && !(secondHand < *this);
}

bool Hand5::operator!=(const Hand5& secondHand) const {
	return (*this < secondHand) || (secondHand < *this);
}

//Private Member Functions

//Returns a pointer to the "greater" hand, NULL if hands tieBreakers are equal
//UNTESTED
const Hand5* Hand5::breakTie(const Hand5* hand1, const Hand5* hand2) const {
	//Check for empty tieBreakers vector (Royal Flush Tie)
	if (hand1->m_ptrsTieBreakers.size() == 0)
	{
		return nullptr;
	}
	
	//Check for all other ties
	pair<vector<const PlayingCard*>::const_iterator, 
		vector<const PlayingCard*>::const_iterator> mmRet 
			= mismatch(hand1->m_ptrsTieBreakers.cbegin(), hand1->m_ptrsTieBreakers.cend(), 
						hand2->m_ptrsTieBreakers.cbegin(), hand2->m_ptrsTieBreakers.cend(), 
						[](auto lhs, auto rhs) { return *lhs == *rhs; });
	
	if (get<0>(mmRet) == hand1->m_ptrsTieBreakers.cend())
	{
		return nullptr;
	}
	else if (*get<0>(mmRet) < *get<1>(mmRet))
	{
		return hand2;
	}
	else
	{
		return hand1;
	}
}

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
}

//Should rewrite to avoid retyping same code - come back to this!
bool Hand5::checkStraight() const {
	int straightCounter = 1;
	bool bStraight = true;
	auto itCurrentCard = max_element(m_Cards.cbegin(), m_Cards.cend());

	//Check if minimum card is an Ace
	if (itCurrentCard->getFaceString() == PlayingCard::s_CardFaces[1])
	{
		//Check for an Ace Low Straight (searches for a Duece as well)
		auto itMinCard = min_element(m_Cards.cbegin(), m_Cards.cend());
		if (itMinCard->getFaceString() == PlayingCard::s_CardFaces[2])
		{
			//Update counter to reflect Ace & Duece
			++straightCounter;
			
			while (bStraight)
			{
				if (straightCounter == m_Cards.size())
				{
					return true;
				}

				try
				{
					if ((itMinCard = find_if(m_Cards.cbegin(), m_Cards.cend(),
						[&itMinCard](PlayingCard otherCard) { return otherCard.getFaceString() == PlayingCard::s_CardFaces.at(itMinCard->getFaceValue() + 1); }))
						!= m_Cards.cend())
					{
						++straightCounter;
					}
					else
					{
						bStraight = false;
					}
				}
				catch (out_of_range& e)
				{
					//this is if there is an error with the "at()" function
					cout << "ERROR1" << endl;
				}
			}
		}
	} //end of Ace High Straight Check

	//reset variables for normal straight check
	bStraight = true;
	straightCounter = 1;
	itCurrentCard = min_element(m_Cards.cbegin(), m_Cards.cend());
	
	while (bStraight)
	{
		if (straightCounter == m_Cards.size())
		{
			return true;
		}
		
		try
		{
			if (itCurrentCard->getFaceString() == PlayingCard::s_CardFaces[13])
			{
				if (straightCounter == m_Cards.size() - 1)
				{
					if (find_if(m_Cards.cbegin(), m_Cards.cend(), [](PlayingCard card) { return card.getFaceString() == PlayingCard::s_CardFaces[1]; }) != m_Cards.cend())
					{
						return true;
					}
				}
				bStraight = false;
			}
			else if ((itCurrentCard = find_if(m_Cards.cbegin(), m_Cards.cend(),
				[&itCurrentCard](PlayingCard otherCard) { return otherCard.getFaceString() == PlayingCard::s_CardFaces.at(itCurrentCard->getFaceValue() + 1); }))
				!= m_Cards.cend())
			{
				++straightCounter;
			}
			else
			{
				bStraight = false;
			}
		}
		catch (const out_of_range& e)
		{
			//this is if there is an error with the "at()" function
			cout << "ERROR2" << endl;
		}
	}

	return bStraight;
} //end of "checkStraight"

bool Hand5::checkFlush() const {
	return search_n(m_Cards.cbegin(), m_Cards.cend(), m_Cards.size(), m_Cards[0].getSuit(),
		[](PlayingCard card, string firstCardSuit) { return card.getSuit() == firstCardSuit; })
		!= m_Cards.cend();
}

//storeTieBreakers() - come back to this to reduce code replication
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
		if (*get<0>(matches[0]) < *get<0>(matches[1]))
		{
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
		if (get<1>(matches[0]) < get<1>(matches[1]))
		{
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
}