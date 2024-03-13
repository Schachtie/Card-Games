/*
*	Author: Trenton Schacht
*
*	Simulates select Five Card Draw and Video Poker on Console/Terminal
* 
* 
*	Working Notes: 
*		- Need to go through all code and "standardize" my variable names and {} use, as well as code documentation
*/

//Header Files
#include <iostream>

#include "User.h"
#include "Game_5CardDraw.h"
#include "Game_VideoPoker.h"

//Using Statements
using namespace std;


//Main Function
int main()
{
	User defaultUser;
	User trentUser("Trent");

	cout << defaultUser.getUserName() << " has " << defaultUser.getCredits() << " credits." << endl;
	cout << trentUser.getUserName() << " has " << trentUser.getCredits() << " credits." << endl;



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
						Game_5CardDraw fiveCardDraw(&trentUser);
						fiveCardDraw.run();
						break;
					}
					case 2: { //VP
						Game_VideoPoker videoPoker(&trentUser);
						videoPoker.run();
						break;
					}
					case 0: { //Close
						cout << "\nThank you for playing!" << endl;
						cout << "\n\n" << trentUser.getUserName() << " has " << trentUser.getCredits() << " credits." << endl;
						return 0;
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