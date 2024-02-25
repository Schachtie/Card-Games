/*
*	Author: Trenton Schacht
*
*	Simulates select Card Games on Console/Terminal
* 
* 
*	Working Notes: 
*		- Need to go through all code and "standardize" my variable names and {} use
*		- Need to name NPCs to make it easier to debug
*		- Need to make dynamic betting in 5 card draw
*/

//Header Files
#include <iostream>
#include <string>
#include <array>

//Self-Made Classes Headers
#include "DeckOfCards.h"
#include "Hand5.h"
#include "Game_5CardDraw.h"



//Using Statements
using namespace std;

//Enumerations


//Function Prototypes
void dealFullHand(DeckOfCards& deck, Hand5& hand);

//Main Function
int main()
{
	cout << "Now testing game object..." << endl << endl;

	Game_5CardDraw fiveCardDraw;
	fiveCardDraw.run();
}

//Function Bodies

	//This works great! Should put this inside a game class like VideoPoker,  tweak for other games
void dealFullHand(DeckOfCards& deck, Hand5& hand) {
	while (hand.count() < hand.size())
	{
		hand.addCard(deck.popNextCard());
	}
}