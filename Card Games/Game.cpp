/*
*	Class Definitions: Game
* 
*	@author: Trenton Schacht
* 
*	@purpose:	Abstract base class for card games.
*				Written to allow extensibility for program to add more games.
* 
*			Provides the following functionalities:
*				- Virtual Public services: run
*/
 

// Header Files
#include <iostream>
#include <fstream>

#include "Game.h"

using namespace std;



// Constructors

/*
*/
Game::Game() {
	m_NumPlayers = 1;
	m_iBuyIn = 0;
	m_iCurrentPot = 0;
	m_iMinBet = 0;
	m_pOutsideUser = nullptr;
} //end of "Default Constructor"



// Protected Member Functions

/*	playAgain
* 
*	@note:	Treats function call like a question: "Play again?"
*			Handles user input and invalid input.
* 
*	@param: void
* 
*	@return: bool
*/
bool Game::playAgain() const {
	while (true) {
		cout << "Play again? (Yes/No): ";
		string input;
		getline(cin, input);

		if (input == "yes" || input == "Yes" || input == "YES") {
			return true;
		}
		else if (input == "no" || input == "No" || input == "NO") {
			return false;
		}

		cout << "Please enter a valid option. ";
		cin.clear();
	}
} //end of "playAgain"


/*	printRules
* 
*	@note: Opens file and prints rules to terminal.
* 
*	@param: File name in string format, must have extension.
* 
*	@return: void
*/
void Game::printRules(const std::string& fileName) {
	ifstream inRulesFile(fileName, ios::in);
	if (inRulesFile) {
		cout << endl;
		string sLine;
		while (getline(inRulesFile, sLine)) {
			cout << sLine << endl;
		}
		cout << endl;
	}
	else {
		cout << "\nError opening rules file.\n" << endl;
	}
} //end of "printRules"