/*
*	Class Definitions: Hand5
*/

/*
*	Working Notes:
*		
*/

//Header Files
#include <iostream>
#include "Game.h"

using namespace std;



Game::Game() {
	m_NumPlayers = 1;
	m_iBuyIn = 0;
	m_iCurrentPot = 0;
	m_iMinBet = 0;
	m_pOutsideUser = nullptr;
} //end of "Default Constructor"





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
}