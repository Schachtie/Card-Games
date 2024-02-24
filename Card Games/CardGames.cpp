/*
*	Author: Trenton Schacht
*
*	Simulates select Card Games on Console/Terminal
* 
* 
*	Working Notes: Currently on "Hand5" class, final project is to store tieBreakers
*					Next class: Player (user... inheritance?)
*/

//Header Files
#include <iostream>
#include <string>
#include <array>

//Self-Made Classes Headers
#include "DeckOfCards.h"
#include "Hand5.h"



//Using Statements
using namespace std;

//Enumerations


//Function Prototypes
void dealFullHand(DeckOfCards& deck, Hand5& hand);

//Main Function
int main()
{
	/*DeckOfCards deck;
	cout << deck << endl;
	deck.shuffle();
	cout << deck << endl;
	Hand5 hand;
	cout << hand << endl;
	dealFullHand(deck, hand);
	cout << hand << endl;
	cout << deck << endl;*/

	PlayingCard card1(7, 1);
	PlayingCard card2(7, 2);
	PlayingCard card3(7, 3);
	PlayingCard card4(1, 3);
	PlayingCard card5(7, 4);

	Hand5 hand1;
	cout << hand1 << endl;
	hand1.addCard(card1);
	hand1.addCard(card2);
	hand1.addCard(card3);
	hand1.addCard(card4);
	hand1.addCard(card5);

	cout << hand1 << endl;

	hand1.setRank();

	cout << endl << hand1 << endl;


	
}

//Function Bodies

	//This works great! Should put this inside a game class like VideoPoker,  tweak for other games
void dealFullHand(DeckOfCards& deck, Hand5& hand) {
	while (hand.count() < hand.size())
	{
		hand.addCard(deck.popNextCard());
	}
}