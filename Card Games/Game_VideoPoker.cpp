/*
*	Class Definitions: Game_VideoPoker
*
*	@author: Trenton Schacht
*
*	@purpose:	Simulates a game of Video Poker with user interaction.
*
*			Provides the following functionalities:
*				- run (runs game once object is created)
*/


//Header Files
#include <iostream>
#include "Game_VideoPoker.h"
#include "User5Card.h"

using namespace std;


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



/*	Public Static Array for Payout Multipliers
* 
*	@notes: Multipliers were taken from wikipedia on Video Poker.
*			https://en.wikipedia.org/wiki/Video_poker
*/
const array<unsigned int, 10> Game_VideoPoker::s_PayoutMultipliers = { 0, 1, 2, 3, 4, 6, 9, 25, 50, 800 };



/*	Public Service - run
*
*	@notes: Has a menu that allows user to choose interaction, switch statement controls whether
*			gameLoop is entered, rules are displayed, or exit back to main menu.
*
*	@params: void
*
*	@return: void
*/
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
} //end of "run"



//Protected Virtual Member Functions

/*	buyInRound
* 
*	@notes:	Handles user input, allows user to bet anywhere between
*			minimum bet and all their credits.
*
*	@params: void
* 
*	@return: void
*/
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
} //end of "buyInRound"


/*	createNPC
*
*	@notes: Not intended to be used for Video Poker.
* 
*	@params: Name of NPC in a C-style string.
* 
*	@return: Returns a null pointer.
*/
Player* Game_VideoPoker::createNPC(char npcName[10]) {
	return nullptr;
} //end of "createNPC"


/*	createUser
* 
*	@notes:
* 
*	@params:
* 
*	@return:
*/
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
} //end of "createUser"


/*	dealCards
* 
*	@notes:	Shuffles deck, deals 5 cards to player and also sets their hand rank.
*
*	@params: void
* 
*	@return: void
*/
void Game_VideoPoker::dealCards() {
	cout << "Shuffling deck... ";
	m_Deck.shuffle();
	cout << "Deck shuffled." << endl;

	cout << "Dealing cards to " << m_ptrsPlayers[0]->getName() << "... ";
	while (m_ptrsPlayers[0]->getHandCount() < m_ptrsPlayers[0]->getHandSize()) {
		m_ptrsPlayers[0]->addCard(m_Deck.popNextCard());
	}
	cout << "All cards have been dealt." << endl;

	m_ptrsPlayers[0]->determineHandRank();
} //end of "dealCards"


/*	gameLoop
*
*	@notes:	Relies on "playAgain" function to terminate loop.
*
*	@params: void
*
*	@return: void
*/
void Game_VideoPoker::gameLoop() {
	do {
		printPayTable();
		buyInRound();

		dealCards();

		replaceRound();

		determinePayout();

		//Reset for new game
		resetGame();
	} while (playAgain());
} //end of "gameLoop"


/*	replaceRound
*
*	@notes: Updates player's hand rank after cards have been replaced.
* 
*	@params: void
* 
*	@return: void
*/
void Game_VideoPoker::replaceRound() {
	cout << "\n== Draw and Replace Round ==" << endl;

	//Determine card indexes to replace
	vector<size_t> replaceCardsIndexes = m_ptrsPlayers[0]->determineReplaceCardsIndexes();

	if (replaceCardsIndexes.size() > 0) {
		for (auto it = replaceCardsIndexes.cbegin(); it != replaceCardsIndexes.cend(); ++it) {
			m_ptrsPlayers[0]->replaceCardAt(*it, m_Deck.popNextCard());
		}
		m_ptrsPlayers[0]->determineHandRank();
	}

	//Announce number of cards replaced
	cout << '\t' << m_ptrsPlayers[0]->getName();
	if (replaceCardsIndexes.size() == 0) {
		cout << " kept all their cards." << endl;
	}
	else {
		cout << " replaced " << replaceCardsIndexes.size() << " card" << ((replaceCardsIndexes.size() == 1) ? "." : "s.") << endl;
	}
} //end of "replaceRound"


/*	resetGame
* 
*	@notes:
* 
*	@params:
* 
*	@return:
*/
void Game_VideoPoker::resetGame() {
	;
} //end of "resetGame"



//Private Member Functions

/*	determinePayout
* 
*	@notes:	"Jacks or Better" for pair payout. 
*			All others are normal rank based.
* 
*	@params: void
* 
*	@return: void
*/
void Game_VideoPoker::determinePayout() {
	//Apply multiplier
	PlayingCard jack(11);
	if (m_ptrsPlayers[0]->getHandRankString() == "Pair" && *(m_ptrsPlayers[0]->getHand().getTieBreakerAt(0)) < jack) {
		m_iCurrentPot = 0;
	}
	else {
		m_iCurrentPot *= s_PayoutMultipliers.at(m_ptrsPlayers[0]->getHandRankValue());
	}

	//Announce result
	cout << "\n\t" << "You ";
	if (m_iCurrentPot == 0) {
		cout << "lost. Try again!" << endl;
	}
	else {
		cout << "won " << m_iCurrentPot << " credits!" << endl;
		m_ptrsPlayers[0]->givePayout(m_iCurrentPot);
	}

	//Print user data
	cout << '\n' << m_ptrsPlayers[0]->getName() << endl;
	cout << "Credits: " << m_ptrsPlayers[0]->getCredits() << endl;
	cout << m_ptrsPlayers[0]->getHand() << endl;
} //end of "determinePayout"


/*	printPayTable
* 
*	@notes: "Jacks or Better" payout structure
*			Accounts for payout multipliers having different digits in some cases.
* 
*	@params: void
* 
*	@return: void
*/
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
	cout << "\t\t* Royal Flush.............x" << s_PayoutMultipliers[9] << " *" << endl;
	cout << "\t\t* Anything Else...........LOSS *" << endl;
	cout << "\t\t********************************" << endl;
	cout << endl;
} //end of "printPayTable"