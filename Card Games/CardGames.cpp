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

//Self-Made Classes Headers
#include "DeckOfCards.h"
#include "Hand5.h"
#include "Game_5CardDraw.h"



//Using Statements
using namespace std;

//Generators
static mt19937 randGen(chrono::steady_clock::now().time_since_epoch().count());

//Function Prototypes
void dealFullHand(DeckOfCards& deck, Hand5& hand);
unsigned int rollNumber(unsigned int low, unsigned int high);

//Main Function
int main()
{
	string sInput;
	vector<string> numbers;
	//going to bed, but try getting full line (no delimiters / default), then tokenizing the string using ' ' as a delimiter. Would still need vector which gets parsed to ints. Think about incorrect user input.
	while (getline(cin, sInput, ' ') && (sInput != "done" || sInput != "Done" || sInput != "DONE") && numbers.size() < 5) {
		numbers.push_back(sInput);
	}
	cout << sInput << endl;
	for (const auto& i : numbers) {
		cout << i << ' ';
	}
	cout << endl;
	
	
	
	
	/*cout << "Now testing game object..." << endl << endl;

	Game_5CardDraw fiveCardDraw;
	fiveCardDraw.run();*/
}

//Function Bodies

	//This works great! Should put this inside a game class like VideoPoker,  tweak for other games
void dealFullHand(DeckOfCards& deck, Hand5& hand) {
	while (hand.count() < hand.size())
	{
		hand.addCard(deck.popNextCard());
	}
}

unsigned int rollNumber(unsigned int low, unsigned int high) {
	return uniform_int_distribution<unsigned int> {low, high} (randGen);
}