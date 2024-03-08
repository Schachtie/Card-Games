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