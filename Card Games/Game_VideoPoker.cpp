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

using namespace std;


//potentially put this in "Game" and just have code written once, it is essentially identical to fiveCardDraw, barring the title of the game and the rules that get pulled (can have a virtual function that pulls rules according to game)
void Game_VideoPoker::run() {
	while (true) {
		//Welcome message and menu
		cout << "\n-=-=-=-=-=-=-=- Welcome to Video Poker -=-=-=-=-=-=-=-" << endl;
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
					cout << "EXITS" << endl;
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

		
		//User buy in
		m_ptrsPlayers[0]->placeBuyIn(m_iBuyIn);

		//Deal 5 cards to user
		dealHand();

		//Draw/Replace (up to 5 cards)
		replaceRound();

		//Determine outcome


	} while (playAgain());
}


void Game_VideoPoker::dealHand() {
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