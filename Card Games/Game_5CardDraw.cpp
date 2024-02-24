/*
*	Class Definitions: Hand5
*/

/*
*	Working Notes:
*
*/

//Header Files
#include "Game_5CardDraw.h"

using namespace std;

//Constructor
Game_5CardDraw::Game_5CardDraw() {

}

//Public Member Functions

//Run Game Function
void Game_5CardDraw::run() {
	
	//Welcome message

	//Menu (Play, rules, quit)
		//switch for menu

	//gameLoop call
	while (gameLoop());

	//Thanks for playing!

	
	;
} //THIS MIGHT WANT TO USE POLYMORPHISM AND BE CALLED IN "GAME" CLASS

//Protected Member Functions

//Game Loop Function: Returns true to continue, false to end
bool Game_5CardDraw::gameLoop() {

	//All Players buy in / blinds


	//Deal cards to all players (all hands should fill)


	//Betting Round (1 time around)

	
	//Draw/Replace Round (up to 5 cards per player)


	//Betting Round (1 time around, unless down to 2 players)


	//Showdown (determine winner)


	//Ask user to continue playing
	return false;
}