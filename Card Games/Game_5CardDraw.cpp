/*
*	Class Definitions: Hand5
*/

/*
*	Working Notes:
*		Currently working on game loop - bettingRound
*/

//Header Files
#include "Game_5CardDraw.h"
#include "User5Card.h"
#include "NPC5Card.h"

using namespace std;

//Constructor
Game_5CardDraw::Game_5CardDraw() {
	//Deck should be initialized implicitly using its default constructor (might need to use new)
	
	//Set buyIn,minBet, currentPot amounts
	m_iBuyIn = 5;
	m_iMinBet = 1;
	m_iCurrentPot = 0;

	//Set players to max and add all players (user + NPCs)
	numPlayers = s_iMAXPLAYERS;
	m_ptrsPlayers.push_back(createUser());
	while (m_ptrsPlayers.size() < numPlayers)
	{
		m_ptrsPlayers.push_back(createNPC());
	}
} //end of default constructor

Game_5CardDraw::~Game_5CardDraw() {
	//Deallocate memory for each player
	while (!m_ptrsPlayers.empty()) {
		delete m_ptrsPlayers.back();
		m_ptrsPlayers.pop_back();
	}
}

//Public Member Functions

//Run Game Function
void Game_5CardDraw::run() {
	
	//Welcome message

	//Menu (Play, rules, quit)
		//switch for menu

	//Verify settings are correct (number of players specifically)

	//gameLoop call
	while (gameLoop());

	//Thanks for playing!

	
	;
} //THIS MIGHT WANT TO USE POLYMORPHISM AND BE CALLED IN "GAME" CLASS

//Protected Member Functions

Player* Game_5CardDraw::createNPC() {
	//Create Player pointer
	Player* pNewPlayer = nullptr;

	//Attempt to create new NPC
	try
	{
		pNewPlayer = new NPC5Card();
	}
	catch (bad_alloc& memoryAllocEx)
	{
		//PUT ERROR MESSAGE HERE OR SOMETHING
	}

	return pNewPlayer;
}

Player* Game_5CardDraw::createUser() {
	//Create Player pointer
	Player* pNewPlayer = nullptr;

	//Attempt to create new user
	try
	{
		pNewPlayer = new User5Card();
	}
	catch (bad_alloc& memoryAllocEx)
	{
		//PUT ERROR MESSAGE HERE OR SOMETHING
	}

	return pNewPlayer;
}


//Game Loop Function: Returns true to continue, false to end
bool Game_5CardDraw::gameLoop() {

	//Check if all players can afford to play

	//All Players buy in / blinds
	buyInRound();

	//Deal cards to all players (all hands should fill)
	dealHands(); //this is looking great!

	//Announce starting pot
	cout << endl << "The pot is: " << m_iCurrentPot << " credits." << endl;

	//TESTING CLEAR THIS OR MOVE THIS
	printHands();

	//Betting Round (1 time around)
	bettingRound();

	//Announce current pot
	cout << endl << "The pot is: " << m_iCurrentPot << " credits." << endl;
	
	//Draw/Replace Round (up to 5 cards per player)
	replaceRound();

	//Betting Round (1 time around, unless down to 2 players)
	bettingRound();

	//Announce final pot
	cout << endl << "The pot is: " << m_iCurrentPot << " credits." << endl;

	//Showdown (determine winner & give payout)
	showdown();
	

	//PREP FOR NEW GAME

	//Clear all hands

	//Reset deck

	//Ask user to continue playing (check if user can't buy in again)
	return false;
}


//Private Member Functions
void Game_5CardDraw::buyInRound() {
	//Iterate through all players backwards, have them place bets of the buyIn amounts, add to pot
	for (auto revItPlayer = m_ptrsPlayers.rbegin(); revItPlayer != m_ptrsPlayers.rend(); ++revItPlayer) {
		//Check if player has enough credits to buy in
		if ((*revItPlayer)->getCredits() > m_iBuyIn) {
			m_iCurrentPot += (*revItPlayer)->Player::placeBet(m_iBuyIn);
		}
		else {
			(*revItPlayer)->setActiveStatus(false);
		}
	}
}

void Game_5CardDraw::dealHands() {
	//Shuffle deck
	m_Deck.shuffle();

	//Deal up to 5 cards per player
	while (m_ptrsPlayers[0]->getHandCount() < m_ptrsPlayers[0]->getHandSize()) {
		//Iterate through all players backwards, deal 1 card to each active player
		for (auto revItPlayer = m_ptrsPlayers.rbegin(); revItPlayer != m_ptrsPlayers.rend(); ++revItPlayer) {
			if ((*revItPlayer)->getActiveStatus()) {
				(*revItPlayer)->addCard(m_Deck.popNextCard());
			}
		}
	}

	//Set each active player's hand rank
	for (auto itPlayer = m_ptrsPlayers.begin(); itPlayer != m_ptrsPlayers.end(); ++itPlayer) {
		if ((*itPlayer)->getActiveStatus()) {
			(*itPlayer)->determineHandRank();
		}
	}
}

void Game_5CardDraw::bettingRound() {
	//Minimum bet starts at 1
	unsigned int minimumBet = 1;

	//Iterate through all players backwards, have them place bet. Each bet must be >= the previous bet or person is out of the game
	for (auto revItPlayer = m_ptrsPlayers.rbegin(); revItPlayer != m_ptrsPlayers.rend(); ++revItPlayer) {
		if ((*revItPlayer)->getActiveStatus() && (*revItPlayer)->getCredits() >= minimumBet) {
			m_iCurrentPot += (*revItPlayer)->placeBet(minimumBet);
		}
		else {
			(*revItPlayer)->setActiveStatus(false);
		}
	}
}

void Game_5CardDraw::replaceRound() {
	;
}

void Game_5CardDraw::showdown() {
	//Find winner based on largest hand
	auto itWinner = max_element(m_ptrsPlayers.begin(), m_ptrsPlayers.end(), [](Player* pLHS, Player* pRHS) { return pLHS->getHand() < pRHS->getHand(); });

	//Check if there are multiple winners
	int iWinners = count_if(m_ptrsPlayers.cbegin(), m_ptrsPlayers.cend(), [&itWinner](Player* pOtherPlayer) { return (*itWinner)->getHand() == pOtherPlayer->getHand(); });
	
	//Add all winners to vector of Player*
	vector<Player*> ptrsWinners;
	auto itCurrentPlayer = m_ptrsPlayers.begin();
	for (int i = 0; i < iWinners; ++i) {
		itCurrentPlayer = find_if(itCurrentPlayer, m_ptrsPlayers.end(), [&itWinner](Player* pOtherPlayer) { return (*itWinner)->getHand() == pOtherPlayer->getHand(); });
		if (itCurrentPlayer != m_ptrsPlayers.end()) {
			ptrsWinners.push_back(&(**itCurrentPlayer));
		}
	}

	//Distribute pot to winners
	for (itWinner = ptrsWinners.begin(); itWinner != ptrsWinners.end(); ++itWinner) {
		//Determine split for each person
		unsigned int payout = m_iCurrentPot / iWinners;
		m_iCurrentPot -= payout;
		
		//Announce winner and payout
		cout << (*itWinner)->getName() << " was awarded " << payout << " credits for winning with a " << (*itWinner)->getHandRankString() << "." << endl;

		//Give payout
		(*itWinner)->givePayout(payout);
	}
}

//Testing Functions

//Prints name, credits, cards, hand rank
void Game_5CardDraw::printHands() const {
	for (auto itPlayer = m_ptrsPlayers.cbegin(); itPlayer != m_ptrsPlayers.cend(); ++itPlayer) {
		cout << endl;
		cout << (*itPlayer)->getName() << endl;
		cout << "Credits: " << (*itPlayer)->getCredits() << endl;
		cout << (*itPlayer)->getHand() << endl;
	}
}