/*
*	@author: Trenton Schacht
*
*	@note:	Simulates Five Card Draw and Video Poker on Console/Terminal.
*			Classes written to be extensible so new card games could be added.
*/

// Header Files
#include <iostream>

#include "User.h"
#include "Game_5CardDraw.h"
#include "Game_VideoPoker.h"

using namespace std;



// Function Prototypes
void mainMenu(User* pMainUser);
void welcomeUser(User* pMainUser);



// Main Function
int main()
{
	User mainUser;
	welcomeUser(&mainUser);
	mainMenu(&mainUser);
} //end of "main"



// Function Definitions

/*	mainMenu
* 
*	@note:	Displays main menu of games (and exit) for user to choose from.
*			Can add new games by adjusting the menu and adding a switch case.
* 
*	@param: Pointer to user created in main.
* 
*	@return: void
*/
void mainMenu(User* pMainUser) {
	while (true) {
		//Main Menu
		cout << "\n-=-=-=-=-=-=-=-=-=-=-=-=-= Card Games =-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
		cout << "\t\t     ~~~~~ Main Menu ~~~~~" << endl;
		cout << "\t\t       (1) Five Card Draw Poker" << endl;
		cout << "\t\t       (2) Video Poker" << endl;
		cout << "\t\t       (0) Close Program" << endl;

		//Handle user input
		short int iInput = -1;
		while (iInput == -1) {
			cout << "\tPlease enter the number of your selection: ";
			cin >> iInput;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			if (cin.good()) {
				switch (iInput) {
				case 1: { //FCD
					Game_5CardDraw fiveCardDraw(pMainUser);
					fiveCardDraw.run();
					break;
				}
				case 2: { //VP
					Game_VideoPoker videoPoker(pMainUser);
					videoPoker.run();
					break;
				}
				case 0: { //Close
					cout << "\nThank you for playing!" << endl;
					cout << "\n\n" << pMainUser->getUserName() << " ended with " << pMainUser->getCredits() << " credits." << endl;
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
} //end of "mainMenu"


/*	welcomeUser
* 
*	@note:	Welcomes user to program and allows them to enter a username.
*			Handles user input.
* 
*	@param: Pointer to user created in main.
* 
*	@return: void
*/
void welcomeUser(User* pMainUser) {
	cout << "\\____________________ Welcome to Card Games! ____________________/\n" << endl;
	
	while (true) {
		cout << "Please enter a Username: ";
		string userName;
		getline(cin, userName);

		while (true) {
			cout << "Welcome, " << userName << endl;
			cout << "Is this Username correct? (Yes/No): ";
			string input;
			getline(cin, input);

			if (input == "yes" || input == "Yes" || input == "YES") {
				pMainUser->setUserName(userName);
				cout << '\n' << pMainUser->getUserName() << " is given " << pMainUser->getCredits() << " credits to start." << endl;
				cout << "Have fun!\n" << endl;
				return;
			}
			else if (input == "no" || input == "No" || input == "NO") {
				break;
			}

			cout << "Please enter a valid option. ";
			cin.clear();
		}
	}
} //end of "welcomeUser"