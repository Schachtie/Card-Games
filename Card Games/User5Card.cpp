/*
*	Class Definitions: User5Card
* 
*	@author: Trenton Schacht
* 
*	@purpose:	Derived class of "Player and Player5Card"
*				Allows use to interact with games that require a Hand5 Hand type.
* 
*			Provides the following functionalities:
*				- Virtual final Public Services: determineBet, determineReplaceCardsIndexes
*/


// Header Files
#include "User5Card.h"
#include <sstream>

using namespace std;



// Constructors

//Default Constructor
User5Card::User5Card() {
	m_sName = "USER";
} //end of "Default Constructor"


User5Card::User5Card(const User* const pOutsideUser) {
	m_sName = pOutsideUser->getUserName();
	m_iCredits = pOutsideUser->getCredits();
} //end of "Outside User Constructor"



// Public Virtual Services

/*	determineBet
* 
*	@note:	Allows user to specify bet.
*			Verifies user has enough credits to even to even bet.
*			Handles incorrect user input.
* 
*	@param: Minimum bet, can be either game's minimum or previous bet that needs to be matched.
* 
*	@return: Player's new bet. Returns 0 if player folds.
*/
unsigned int User5Card::determineBet(unsigned int minBet) {
	//print user data
	cout << '\n' << m_sName << endl;
	cout << "Credits: " << m_iCredits - m_iCurrentBet << endl;
	cout << (*m_pHand) << endl;

	//check if user has enough credits to call or bet
	if (m_iCredits >= minBet) {
		while (true) {
			cout << "\tCurrent bet is: " << minBet << ". What would you like to do? (Call" << ((m_iRaisesLeft > 0) ? "/Raise" : "") << "/Fold): ";
			string input;
			getline(cin, input);

			if (input == "call" || input == "Call" || input == "CALL") {
				//call behavior
				callBehavior(minBet);
				return minBet;
			}
			else if (input == "raise" || input == "Raise" || input == "RAISE") { //add max raises here
				if (m_iRaisesLeft == 0) {
					cout << "\tYou can only raise twice per game." << endl;
					continue;
				}
				//raise behavior
				raiseBehavior(minBet);
				return m_iCurrentBet;
			}
			else if (input == "fold" || input == "Fold" || input == "FOLD") {
				//fold behavior
				foldBehavior();
				return 0;
			}

			cout << "\tPlease enter a valid option. " << endl;
			cin.clear();
		}
	}
	else { //not enough credits, user must fold
		forcedFold();
		return 0;
	}
} //end of "determineBet"


/*	determineReplaceCardsIndexes
* 
*	@note:
*
*	@param: void
* 
*	@return: Vector containing indexes of cards to replace [0, 4].
*/
vector<size_t> User5Card::determineReplaceCardsIndexes() {
	vector<size_t> replaceIndexes;
	
	//Handle user input
	while (true) {
		//Print hand for user
		cout << '\n' << m_sName << "'s cards: " << endl;
		m_pHand->printHandNumbered();
		cout << "\n\tYou may replace up to five cards. Enter \"All\", \"None\", or the numbers of\n\tthe cards you'd like to replace with spaces in between.\n\tHit \"Enter\" when you are finished: ";
		string input;
		getline(cin, input);
		if (input == "all" || input == "All" || input == "ALL") {
			for (size_t i = 0; i < 5; ++i) {
				replaceIndexes.push_back(i);
			}
		}
		else if (input == "none" || input == "None" || input == "NONE") {
		}
		else {
			stringstream sStream(input);
			while (!sStream.eof()) {
				string token;
				sStream >> token;
				size_t sz = 0;
				try {
					int i = stoi(token, &sz);
					if (i >= 1 && i <= 5 && sz == token.size()) {
						replaceIndexes.push_back(i - 1);
					}
				}
				catch (const exception& e) {}
			}

		}
		//Verify with user that input was correct
		while (true) {
			cout << "\tCard numbers to replace: ";
			if (replaceIndexes.empty()) {
				cout << "NONE";
			}
			else {
				for (const auto& i : replaceIndexes) {
					cout << i + 1 << " ";
				}
			}
			cout << "\n\tAre these correct? (Yes/No): ";
			string input;
			getline(cin, input);
			if (input == "yes" || input == "Yes" || input == "YES") {
				return replaceIndexes;
			}
			else if (input == "no" || input == "No" || input == "NO") {
				replaceIndexes.clear();
				break;
			}
			cout << "\tInvalid input. Try again." << endl;
		}
	}
} //end of "determineReplaceCardIndexes"



// Protected Virtual Member Functions

/*	raiseBehavior
* 
*	@note:	Called when player chooses to raise.
*			Handles user input and invalid input.
*
*	@param: Previous player's bet, could also be minimum bet of game if player's turn is first.
* 
*	@return: void
*/
void User5Card::raiseBehavior(unsigned int prevBet) {
	while (true) {
		cout << "\tWhat would you like to raise the bet to?" << endl;
		cout << "\t(Must be between " << (prevBet + 1) << " and " << m_iCredits << "): ";
		unsigned int userBet = 0;
		cin >> userBet;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		if (cin.good() && userBet > prevBet && userBet <= m_iCredits) {
			m_iCurrentBet = userBet;
			--m_iRaisesLeft;
			cout << '\t' << m_sName << " raised the bet to " << userBet << " credit" << ((userBet == 1) ? "." : "s.") << endl;
			return;
		}
		cout << "\tPlease enter a valid option. ";
		if (!cin.good()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
} //end of "raiseBehavior"