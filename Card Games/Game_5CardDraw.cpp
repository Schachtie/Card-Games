/*
*	Class Definitions: Game_5CardDraw
*
*	@author: Trenton Schacht
*
*	@purpose:	Simulates a game of Five Card Draw Poker with 4 non-player characters and the user.
*
*			Provides the following functionalities:
*				- Virtual Public services: run (runs game once object is created)
*/


// Header Files
#include <fstream>
#include <conio.h>
#include "Game_5CardDraw.h"
#include "User5Card.h"
#include "NPC5Card.h"

using namespace std;



// Constructors and Destructor

/*
*/
Game_5CardDraw::Game_5CardDraw() {
	//Set buyIn,minBet, currentPot amounts
	m_iBuyIn = 5;
	m_iMinBet = 1;

	//Set players to max and add all players (user + NPCs)
	m_NumPlayers = s_iMAXPLAYERS;
	m_ptrsPlayers.push_back(createUser());

	//Open NPC Names file and generate 4 names
	ifstream inNames("NPC_Names.txt", ios::in | ios::binary);
	if (inNames) {
		char genName[10];
		while (m_ptrsPlayers.size() < m_NumPlayers) {
			inNames.seekg(rollNumber(0, 99) * sizeof(genName));
			inNames.read(genName, sizeof(genName));
			m_ptrsPlayers.push_back(createNPC(genName));
		}
		inNames.close();
	}
} //end of "Default Constructor"


/*
*/
Game_5CardDraw::Game_5CardDraw(User* pOutsideUser) {
	//Set buyIn,minBet, currentPot amounts
	m_iBuyIn = 5;
	m_iMinBet = 1;

	//Set players to max and add all players (user + NPCs)
	m_NumPlayers = s_iMAXPLAYERS;
	m_pOutsideUser = pOutsideUser;
	m_ptrsPlayers.push_back(createUser());

	//Open NPC Names file and generate 4 names
	ifstream inNames("NPC_Names.txt", ios::in | ios::binary);
	if (inNames) {
		char genName[10];
		while (m_ptrsPlayers.size() < m_NumPlayers) {
			inNames.seekg(rollNumber(0, 99) * sizeof(genName));
			inNames.read(genName, sizeof(genName));
			m_ptrsPlayers.push_back(createNPC(genName));
		}
		inNames.close();
	}
} //end of "Outside User Constructor"


/*
*/
Game_5CardDraw::~Game_5CardDraw() {
	//Deallocate memory for each player
	while (!m_ptrsPlayers.empty()) {
		delete m_ptrsPlayers.back();
		m_ptrsPlayers.pop_back();
	}
} //end of "Virtual Destructor"



/*	Private Static Random Generator
*
*	@note: Uses a Mersenne Twister Engine seeded with the current time.
*/
mt19937 Game_5CardDraw::s_RandGen(chrono::steady_clock::now().time_since_epoch().count());



// Public Virtual Services

/*	Public Service - run
* 
*	@note: Has a menu that allows user to choose interaction, switch statement controls whether 
*			gameLoop is entered, rules are displayed, or exit back to main menu.
* 
*	@param: void
* 
*	@return: void
*/
void Game_5CardDraw::run() {
	while (true) {
		//Welcome message and menu
		cout << "\n-=-=-=-=-=-=-=- Welcome to Five Card Draw Poker -=-=-=-=-=-=-=-" << endl;
		cout << "\t\t\t~~~~~ Menu ~~~~~" << endl;
		cout << "\t\t\t  (1) Play" << endl;
		cout << "\t\t\t  (2) Rules" << endl;
		cout << "\t\t\t  (0) Exit to Main Menu" << endl;

		//Handle user input
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



// Protected Virtual Member Functions

/*	buyInRound
* 
*	@note: Announces buy in amount as well as updated pot.
* 
*	@param: void
*
*	@return: void
*/
void Game_5CardDraw::buyInRound() {
	cout << "Buy-in for this game is " << m_iBuyIn << " credits." << endl;

	//Iterate through all players backwards, have them place bets of the buyIn amounts, add to pot
	for (auto revItPlayer = m_ptrsPlayers.rbegin(); revItPlayer != m_ptrsPlayers.rend(); ++revItPlayer) {
		unsigned int iBuyInRet = (*revItPlayer)->placeBuyIn(m_iBuyIn);
		cout << '\t' << (*revItPlayer)->getName() << ((iBuyInRet != 0) ? " has bought in!" : " doesn't have enough credits to play.") << endl;
		m_iCurrentPot += iBuyInRet;
	}

	cout << "The starting pot for this game is " << m_iCurrentPot << " credits." << endl;
} //end of "buyInRound"


/*	createNPC
* 
*	@note:	If allocation fails, returns null pointer.
* 
*	@param: NPC's name as a C-style string.
* 
*	@return: pointer to dynamically allocated NPC.
*/
Player* Game_5CardDraw::createNPC(char npcName[10]) {
	//Create Player pointer
	Player* pNewPlayer = nullptr;

	//Attempt to create new NPC
	try {
		pNewPlayer = new NPC5Card(npcName);
		pNewPlayer->setRaisesLeft(s_iMAXRAISES);
	}
	catch (bad_alloc& memoryAllocEx) {
		cout << "Error allocating memory for NPC: " << npcName << endl;
		cout << "ERROR: " << memoryAllocEx.what() << endl;
	}

	return pNewPlayer;
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
Player* Game_5CardDraw::createUser() { //this may not be needed once player is created in main
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
		pNewPlayer->setRaisesLeft(s_iMAXRAISES);
	}
	catch (bad_alloc& memoryAllocEx) {
		cout << "Error allocating memory for USER: " << endl;
		cout << "ERROR: " << memoryAllocEx.what() << endl;
	}

	return pNewPlayer;
} //end of "createUser"


/*	dealCards
* 
*	@note:	Simulates real dealing where players get one card at a time. 
*			Also takes care of shuffling the initialized deck, and
*			setting each player's initial hand rank.
* 
*	@param: void
* 
*	@return: void
*/
void Game_5CardDraw::dealCards() {
	cout << "Shuffling deck... ";
	m_Deck.shuffle();
	cout << "Deck shuffled." << endl;

	//Deal up to 5 cards per player (uses number of cards dealt to User to check)
	cout << "Dealing cards to each player... ";
	while (m_ptrsPlayers[0]->getHandCount() < m_ptrsPlayers[0]->getHandSize()) {
		//Iterate through all players backwards, deal 1 card to each active player
		for (auto revItPlayer = m_ptrsPlayers.rbegin(); revItPlayer != m_ptrsPlayers.rend(); ++revItPlayer) {
			if ((*revItPlayer)->getActiveStatus()) {
				(*revItPlayer)->addCard(m_Deck.popNextCard());
			}
		}
	}
	cout << "All cards have been dealt." << endl;

	//Set each active player's hand rank
	for (auto itPlayer = m_ptrsPlayers.begin(); itPlayer != m_ptrsPlayers.end(); ++itPlayer) {
		if ((*itPlayer)->getActiveStatus()) {
			(*itPlayer)->determineHandRank();
		}
	}
} //end of "dealCards"


/*	gameLoop
* 
*	@note:	Relies on "playAgain" function to terminate loop.
*			Updates outside player's credits once user stops playing.
* 
*	@param: void
* 
*	@return: void
*/
void Game_5CardDraw::gameLoop() {
	do {
		cout << "\n\n\t===== Game Start =====" << endl;
		
		buyInRound();
		dealCards();

		bettingRound();

		replaceRound();

		bettingRound();

		showdown();

		pauseForUser("Hit \"Enter\" to show every player's cards.");
		cout << "\n\n ~~~~~~~~~~~~~~~ PRINTING EVERYONE'S HAND BELOW ~~~~~~~~~~~~~~~" << endl;
		printAllHands();

		//Prep for new game
		resetGame();
	} while (playAgain());
	updateOutsideUser();
} //end of "gameLoop"


/*	replaceRound
* 
*	@note: Takes care of updating hand rank once cards have been replaced.
* 
*	@param: void
* 
*	@return: void
*/
void Game_5CardDraw::replaceRound() {
	cout << "\n== Draw and Replace Round ==" << endl;

	//Iterate through all players backwards, if they're active have them take their replace card round turn.
	for (auto revItPlayer = m_ptrsPlayers.rbegin(); revItPlayer != m_ptrsPlayers.rend(); ++revItPlayer) {
		if ((*revItPlayer)->getActiveStatus()) {
			vector<size_t> replaceCardsIndexes = (*revItPlayer)->determineReplaceCardsIndexes();

			//Replace cards
			if (replaceCardsIndexes.size() > 0) {
				for (auto it = replaceCardsIndexes.cbegin(); it != replaceCardsIndexes.cend(); ++it) {
					(*revItPlayer)->replaceCardAt(*it, m_Deck.popNextCard());
				}
				(*revItPlayer)->determineHandRank();
			}

			//Announce number of cards replaced
			cout << '\t' << (*revItPlayer)->getName();
			if (replaceCardsIndexes.size() == 0) {
				cout << " kept all their cards." << endl;
			}
			else {
				cout << " replaced " << replaceCardsIndexes.size() << " card" << ((replaceCardsIndexes.size() == 1) ? "." : "s.") << endl;
			}
		}
	}
} //end of "replaceRound"


/*	resetGame
* 
*	@note:	Each player's hand is cleared, active status reset to true, and raises reset.
*			Also has to reset deck.
* 
*	@param: void
* 
*	@return: void
*/
void Game_5CardDraw::resetGame() {
	for (auto itPlayer = m_ptrsPlayers.begin(); itPlayer != m_ptrsPlayers.end(); ++itPlayer) {
		(*itPlayer)->clearHand();
		(*itPlayer)->setActiveStatus(true);
		(*itPlayer)->setRaisesLeft(s_iMAXRAISES);
	}

	m_Deck.initDeck();
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
void Game_5CardDraw::updateOutsideUser() {
	if (m_pOutsideUser != nullptr) {
		m_pOutsideUser->setCredits(m_ptrsPlayers[0]->getCredits());
	}
} //end of "updateOutsideUser"



// Private Member Functions

/*	bettingRound
* 
*	@note: Mimics betting structure of a real poker match. Allows players to raise and
*			other players must either match the bet or raise again. Players actually "commit"
*			to bets they make. Even if they fold, the highest bet they've agreed to gets applied.
* 
*	@param: void
* 
*	@return: void
*/
void Game_5CardDraw::bettingRound() {
	cout << "\n== Betting Round == Starting bet: " << m_iMinBet << endl;
	unsigned int iMinimumBet = m_iMinBet;

	//Iterate through all players backwards, if they're active have them determine bets until all bets are equalized
	auto revItPlayer = m_ptrsPlayers.rbegin();
	while (revItPlayer != m_ptrsPlayers.rend()) {
		//Cycle through players that don't have an updated bet
		for (revItPlayer = m_ptrsPlayers.rbegin(); revItPlayer != m_ptrsPlayers.rend(); ++revItPlayer) {
			if ((*revItPlayer)->getActiveStatus() && (*revItPlayer)->getCurrentBet() != iMinimumBet) {
				unsigned int iCurrentBet = (*revItPlayer)->determineBet(iMinimumBet);
				if (iCurrentBet != 0 && iCurrentBet != iMinimumBet) {
					iMinimumBet = iCurrentBet;
				}
			}
		}

		//search for an active player who does not have an updated bet
		revItPlayer = find_if_not(m_ptrsPlayers.rbegin(), m_ptrsPlayers.rend(), [&iMinimumBet](Player* player) 
			{ return (player->getActiveStatus() && player->getCurrentBet() == iMinimumBet) || !player->getActiveStatus(); });
	}

	//Apply everyone's stored bet to the pot
	for (revItPlayer = m_ptrsPlayers.rbegin(); revItPlayer != m_ptrsPlayers.rend(); ++revItPlayer) {
		m_iCurrentPot += (*revItPlayer)->placeCurrentBet();
	}

	//Announce the updated pot
	cout << "The pot is now " << m_iCurrentPot << " credits." << endl;
} //end of "bettingRound"


/*	pauseForUser
*
*	@note: Used to prompt user to enter a key to continue output printing.
* 
*	@param: Prompt for user.
* 
*	@return: void
*/
void Game_5CardDraw::pauseForUser(const string& prompt) const {
	cout << '\n' << prompt << ' ';
	string str;
	getline(cin, str);
} //end of "pauseForUser"


/*	printAllHands
* 
*	@note: Prints player's name, credits, and their hand. Hand rank is printed alongside hand.
*
*	@param: void
* 
*	@return: void
*/
void Game_5CardDraw::printAllHands() const {
	for (auto itPlayer = m_ptrsPlayers.cbegin(); itPlayer != m_ptrsPlayers.cend(); ++itPlayer) {
		cout << endl;
		cout << (*itPlayer)->getName() << endl;
		cout << "Credits: " << (*itPlayer)->getCredits() << endl;
		cout << *(*itPlayer)->getHandPtr() << endl;
	}
} //end of "printAllHands"


/*	rollNumber
* 
*	@note:	Specifically for unsigned int. 
* 
*	@param: Lower and upper bounds.
* 
*	@return: Randomly generated number within provided range.
*/
unsigned int Game_5CardDraw::rollNumber(unsigned int low, unsigned int high) {
	return uniform_int_distribution<unsigned int> {low, high}(s_RandGen);
} //end of "rollNumber"


/*	showDown
* 
*	@note:	Showdown will determine the winner(s) of the game and distribute pot accordingly.
			Any leftover credits in pot from integer rounding will be rolled over into next pot.
* 
*	@param: void
* 
*	@return: void
*/
void Game_5CardDraw::showdown() {
	cout << "\n== Showdown ==" << endl;

	//Put active players into a vector to later find winner
	vector<Player*> activePlayers;
	for (auto itPlayer = m_ptrsPlayers.begin(); itPlayer != m_ptrsPlayers.end(); ++itPlayer) {
		if ((*itPlayer)->getActiveStatus()) {
			activePlayers.push_back(*itPlayer);
		}
	}

	//Find winner based on largest hand
	auto itWinner = max_element(activePlayers.begin(), activePlayers.end(), [](Player* pLHS, Player* pRHS)
		{ return *(pLHS->getHandPtr()) < *(pRHS->getHandPtr()); });

	//Check if there are multiple winners
	int iWinners = count_if(activePlayers.begin(), activePlayers.end(), [&itWinner](Player* pOtherPlayer)
		{ return *((*itWinner)->getHandPtr()) == *(pOtherPlayer->getHandPtr()); });
	
	//Add all winners to vector of Player*
	vector<Player*> ptrsWinners;
	auto itCurrentPlayer = activePlayers.begin();
	for (int i = 0; i < iWinners; ++i) {
		itCurrentPlayer = find_if(itCurrentPlayer, activePlayers.end(), [&itWinner](Player* pOtherPlayer)
			{ return *((*itWinner)->getHandPtr()) == *(pOtherPlayer->getHandPtr()); });
		if (itCurrentPlayer != activePlayers.end()) {
			ptrsWinners.push_back(&(**itCurrentPlayer));
		}
	}

	//Distribute pot to winners
	for (itWinner = ptrsWinners.begin(); itWinner != ptrsWinners.end(); ++itWinner) {
		//Determine split for each person
		unsigned int payout = m_iCurrentPot / iWinners;
		m_iCurrentPot -= payout;
		
		//Announce winner and payout
		cout << (*itWinner)->getName() << " was awarded " << payout << " credits for winning with a " << (*itWinner)->getHandRankString() << "." << endl;

		//Give payout
		(*itWinner)->givePayout(payout);
	} 
} //end of "showdown"