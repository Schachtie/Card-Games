/*
*	Class Definitions: User5Card
*/

//Header Files
#include "User5Card.h"

using namespace std;

//Default Constructor
User5Card::User5Card() {
	m_sName = "USER";
}

//Copy Constructor


//Public Member Functions

//Allows user to specify bet (need to actually code this)

unsigned int User5Card::determineBet(unsigned int minBet) {
	//print user data
	cout << '\n' << m_sName << endl;
	cout << "Credits: " << m_iCredits << endl;
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
}



void User5Card::printCards() const {

}

vector<size_t> User5Card::determineReplaceCardsIndexes() {
	vector<size_t> replaceIndexes;
	
	//print hand for user
	cout << '\n' << m_sName << "'s cards: " << endl;
	m_pHand->printHandNumbered();
	cout << '\t';

	//handle user input
	while (true) {
		cout << "\tYou may replace up to five cards. Enter \"All\", or the numbers of the cards you'd like to replace with spaces in between.\nEnter \"Done\" when you are finished or want to keep all your cards: ";
		string input;
		getline(cin, input);
		if (input == "all" || input == "All" || input == "ALL") {
			for (size_t i = 0; i < m_pHand->count(); ++i) {
				replaceIndexes.push_back(i);
			}
		}
		else if (input == "done" || input == "Done" || input == "DONE") {

		}


		cout << "\tPlease enter a valid option. " << endl;
		cin.clear();
	}

	


	return replaceIndexes;
}





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
}