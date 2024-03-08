/*
*	Class Definitions: User5Card
*/

//Header Files
#include "User5Card.h"
#include <sstream>

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
	

	//handle user input
	while (true) {
		//print hand for user
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