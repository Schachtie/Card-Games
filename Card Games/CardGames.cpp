/*
*	Author: Trenton Schacht
*
*	Simulates select Card Games on Console/Terminal
* 
* 
*	Working Notes: 
*		- Need to go through all code and "standardize" my variable names and {} use, as well as code documentation
*		- Need to add user interaction. Clean the game output before you do this. Everything seems to be functioning properly now.
*/

//Header Files
#include <iostream>
#include <string>
#include <array>
#include <fstream>
#include <sstream>

//Self-Made Classes Headers
#include "DeckOfCards.h"
#include "Hand5.h"
#include "Game_5CardDraw.h"
#include "Game_VideoPoker.h"

//Using Statements
using namespace std;


//Main Function
int main()
{
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
						Game_5CardDraw fiveCardDraw;
						fiveCardDraw.run();
						break;
					}
					case 2: { //VP
						Game_VideoPoker videoPoker;
						videoPoker.run();
						break;
					}
					case 0: { //Close
						cout << "\nThank you for playing!" << endl;
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