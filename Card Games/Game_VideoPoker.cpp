/*
*	Class Definitions: Hand5
*/

/*
*	Working Notes:
*
*/

//Header Files
#include <iostream>
#include "Game_VideoPoker.h"
#include "User5Card.h"

using namespace std;


const array<unsigned int, 10> Game_VideoPoker::s_PayoutMultipliers = { 0, 1, 2, 3, 4, 6, 9, 25, 50, 800 };












//Constructor
Game_VideoPoker::Game_VideoPoker() {
	//Deck should be initialized implicitly using its default constructor (might need to use new)

	//Set buyIn,minBet, currentPot amounts
	m_iBuyIn = 5;
	m_iMinBet = 1;
	m_iCurrentPot = 0;

	//Set players to max and add all players (user + NPCs)
	m_NumPlayers = 1;
	m_ptrsPlayers.push_back(createUser());
} //end of default constructor




Player* Game_VideoPoker::createNPC(char npcName[10]) {
	//Create Player pointer
	Player* pNewPlayer = nullptr;
	return pNewPlayer;
}

Player* Game_VideoPoker::createUser() { //this may not be needed once player is created in main
	//Create Player pointer
	Player* pNewPlayer = nullptr;

	//Attempt to create new user
	try
	{
		pNewPlayer = new User5Card();
	}
	catch (bad_alloc& memoryAllocEx)
	{
		//PUT ERROR MESSAGE HERE OR SOMETHING
	}

	return pNewPlayer;
}

void Game_VideoPoker::resetGame() {
	;
}






//potentially put this in "Game" and just have code written once, it is essentially identical to fiveCardDraw, barring the title of the game and the rules that get pulled (can have a virtual function that pulls rules according to game)
void Game_VideoPoker::run() {
	while (true) {
		//Welcome message and menu
		cout << "\n-=-=-=-=-=-=-=-=-=-= Welcome to Video Poker =-=-=-=-=-=-=-=-=-=-" << endl;
		cout << "\t\t\t~~~~~ Menu ~~~~~" << endl;
		cout << "\t\t\t  (1) Play" << endl;
		cout << "\t\t\t  (2) Rules" << endl;
		cout << "\t\t\t  (0) Exit to Main Menu" << endl;

		//handle user input
		short int iInput = -1;
		while (iInput == -1) {
			cout << "\tPlease enter the number of your selection: ";
			cin >> iInput;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			if (cin.good()) {
				switch (iInput) {
				case 1: { //Play
					gameLoop();
					break;
				}
				case 2: { //Rules
					break;
				}
				case 0: { //Exit to main menu
					return;
				}
				default: { //Input error
					iInput = -1;
					cout << "\tPlease enter a valid option." << endl;
					break;
				}
				}
			}
			else {
				cout << "\tPlease enter a valid option." << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				iInput = -1;
			}
		}
	}
}


//Protected Member Functions

//Game Loop Function: Returns true to continue, false to end
void Game_VideoPoker::gameLoop() {
	do {
		//print payout table (Jacks or Better)
		printPayTable();
		
		//User buy in
		buyInRound();

		//Deal 5 cards to user
		dealCards();

		//Draw/Replace (up to 5 cards)
		replaceRound();

		//Determine outcome
		determinePayout();

	} while (playAgain());
}


void Game_VideoPoker::buyInRound() {
	while (true) {
		cout << "\tHow much would you like to bet?" << endl;
		cout << "\t(Must be between " << (m_iMinBet) << " and " << m_ptrsPlayers[0]->getCredits() << "): ";
		unsigned int userBet = 0;
		cin >> userBet;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		if (cin.good() && userBet >= m_iMinBet && userBet <= m_ptrsPlayers[0]->getCredits()) {
			m_iCurrentPot = m_ptrsPlayers[0]->placeBuyIn(userBet);
			cout << '\t' << m_ptrsPlayers[0]->getName() << " bet " << userBet << " credit" << ((userBet == 1) ? "." : "s.") << endl;
			return;
		}
		cout << "\tPlease enter a valid option. ";
		if (!cin.good()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
}


void Game_VideoPoker::dealCards() {
	//Shuffle deck
	cout << "Shuffling deck... ";
	m_Deck.shuffle();
	cout << "Deck shuffled." << endl;

	//Deal 5 cards to player
	cout << "Dealing cards to " << m_ptrsPlayers[0]->getName() << "... ";
	while (m_ptrsPlayers[0]->getHandCount() < m_ptrsPlayers[0]->getHandSize()) {
		m_ptrsPlayers[0]->addCard(m_Deck.popNextCard());
	}
	cout << "All cards have been dealt." << endl;

	//set player's hand rank
	m_ptrsPlayers[0]->determineHandRank();
}


void Game_VideoPoker::replaceRound() {
	cout << "\n== Draw and Replace Round ==" << endl;

	//determine card indexes to replace
	vector<size_t> replaceCardsIndexes = m_ptrsPlayers[0]->determineReplaceCardsIndexes();

	if (replaceCardsIndexes.size() > 0) {
		for (auto it = replaceCardsIndexes.cbegin(); it != replaceCardsIndexes.cend(); ++it) {
			m_ptrsPlayers[0]->replaceCardAt(*it, m_Deck.popNextCard());
		}
	}

	//announce number of cards replaced
	cout << '\t' << m_ptrsPlayers[0]->getName();
	if (replaceCardsIndexes.size() == 0) {
		cout << " kept all their cards." << endl;
	}
	else {
		cout << " replaced " << replaceCardsIndexes.size() << " card" << ((replaceCardsIndexes.size() == 1) ? "." : "s.") << endl;
	}

	//update hand rank
	m_ptrsPlayers[0]->determineHandRank();
}


void Game_VideoPoker::determinePayout() {
	//apply multiplier
	PlayingCard jack(11);
	if (m_ptrsPlayers[0]->getHandRankString() == "Pair" && *(m_ptrsPlayers[0]->getHand().getTieBreakerAt(0)) < jack) {
		m_iCurrentPot = 0;
	}
	else {
		m_iCurrentPot *= s_PayoutMultipliers.at(m_ptrsPlayers[0]->getHandRankValue());
	}

	//announce result
	cout << "\n\t" << "You ";
	if (m_iCurrentPot == 0) {
		cout << "lost. Try again!" << endl;
	}
	else {
		cout << "won " << m_iCurrentPot << " credits!" << endl;
		m_ptrsPlayers[0]->givePayout(m_iCurrentPot);
	}

	//print user data
	cout << '\n' << m_ptrsPlayers[0]->getName() << endl;
	cout << "Credits: " << m_ptrsPlayers[0]->getCredits() << endl;
	cout << m_ptrsPlayers[0]->getHand() << endl;
}


void Game_VideoPoker::printPayTable() const {
	cout << endl;
	cout << "\t\t********************************" << endl;
	cout << "\t\t*       Bet Multipliers        *" << endl;
	cout << "\t\t*------------------------------*" << endl;
	cout << "\t\t* Pair of Jacks or Higher...x" << s_PayoutMultipliers[1] << " *" << endl;
	cout << "\t\t* Two Pair..................x" << s_PayoutMultipliers[2] << " *" << endl;
	cout << "\t\t* Three of a Kind...........x" << s_PayoutMultipliers[3] << " *" << endl;
	cout << "\t\t* Straight..................x" << s_PayoutMultipliers[4] << " *" << endl;
	cout << "\t\t* Flush.....................x" << s_PayoutMultipliers[5] << " *" << endl;
	cout << "\t\t* Full House................x" << s_PayoutMultipliers[6] << " *" << endl;
	cout << "\t\t* Four of a Kind...........x" << s_PayoutMultipliers[7] << " *" << endl; //2 digits
	cout << "\t\t* Straight Flush...........x" << s_PayoutMultipliers[8] << " *" << endl; //2 digits
	cout << "\t\t* Royal Flush.............x" << s_PayoutMultipliers[9] << " *" << endl; //3 digits
	cout << "\t\t* Anything Else...........LOSS *" << endl;
	cout << "\t\t********************************" << endl;
	cout << endl;
}