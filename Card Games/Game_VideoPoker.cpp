/*
*	Class Definitions: Game_VideoPoker
*
*	@author: Trenton Schacht
*
*	@purpose:	Simulates a game of Video Poker with user interaction.
*
*			Provides the following functionalities:
*				- Virtual Public services: run (runs game once object is created)
*/


// Header Files
#include <iostream>

#include "Game_VideoPoker.h"
#include "User5Card.h"

using namespace std;



// Constructors and Destructor

//Default Constructor
Game_VideoPoker::Game_VideoPoker() {
	m_iMinBet = 1;
	m_ptrsPlayers.push_back(createUser());
} //end of "Default Constructor"


//Outside User Constructor
Game_VideoPoker::Game_VideoPoker(User* pOutsideUser) {
	m_iMinBet = 1;
	m_pOutsideUser = pOutsideUser;
	m_ptrsPlayers.push_back(createUser());
} //end of "Outside User Constructor"


//Destructor
Game_VideoPoker::~Game_VideoPoker() {
	//Deallocate memory for each player
	while (!m_ptrsPlayers.empty()) {
		delete m_ptrsPlayers.back();
		m_ptrsPlayers.pop_back();
	}
} //end of "Destructor"



/*	Public Static Array for Payout Multipliers
* 
*	@notes: Multipliers were taken from wikipedia on Video Poker.
*			https://en.wikipedia.org/wiki/Video_poker
*/
const array<unsigned int, 10> Game_VideoPoker::s_PayoutMultipliers = { 0, 1, 2, 3, 4, 6, 9, 25, 50, 800 };



// Public Virtual Services

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
					printRules("Rules_VideoPoker.txt");
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



// Protected Virtual Member Functions

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
*	@note:	Creates either a default user or outside user of type User5Card.
*			Returns a null pointer if allocation fails.
*
*	@param:	void
*
*	@return: Player pointer to created user.
*/
Player* Game_VideoPoker::createUser() {
	//Create Player pointer
	Player* pNewPlayer = nullptr;

	//Attempt to create new user
	try {
		if (m_pOutsideUser == nullptr) {
			pNewPlayer = new User5Card();
		}
		else {
			pNewPlayer = new User5Card(m_pOutsideUser);
		}
	}
	catch (bad_alloc& memoryAllocEx) {
		cout << "Error allocating memory for USER: " << endl;
		cout << "ERROR: " << memoryAllocEx.what() << endl;
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
*			Updates outside player's credits once user stops playing.
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
	updateOutsideUser();
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
*	@note:  Player's hand is cleared and pot is reset to 0.
*			Also has to reset deck.
*
*	@param: void
*
*	@return: void
*/
void Game_VideoPoker::resetGame() {
	m_ptrsPlayers[0]->clearHand();
	m_iCurrentPot = 0;
} //end of "resetGame"


/*	updateOutsideUser
* 
*	@note:	User's Player pointer was put in index 0 in this game.
*			Updates outside user's credits.
* 
*	@param: void
* 
*	@return: void
*/
void Game_VideoPoker::updateOutsideUser() {
	if (m_pOutsideUser != nullptr) {
		m_pOutsideUser->setCredits(m_ptrsPlayers[0]->getCredits());
	}
} //end of "updateOutsideUser"



// Private Member Functions

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
	if (m_ptrsPlayers[0]->getHandRankString() == "Pair" && *((*m_ptrsPlayers[0]->getHandPtr()).getTieBreakerAt(0)) < jack) {
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
	cout << *m_ptrsPlayers[0]->getHandPtr() << endl;
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