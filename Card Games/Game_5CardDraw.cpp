/*
*	Class Definitions: Hand5
*/

/*
*	Working Notes:
*		Currently working on game loop - bettingRound
*/

//Header Files
#include <fstream>
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

	//Open NPC Names file and generate 4 names
	ifstream inNames("NPC_Names.txt", ios::in | ios::binary);
	if (inNames) {
		char genName[10];
		while (m_ptrsPlayers.size() < numPlayers) {
			inNames.seekg(rollNumber(0, 99) * sizeof(genName));
			inNames.read(genName, sizeof(genName));
			m_ptrsPlayers.push_back(createNPC(genName));
		}
	}
} //end of default constructor

Game_5CardDraw::~Game_5CardDraw() {
	//Deallocate memory for each player
	while (!m_ptrsPlayers.empty()) {
		delete m_ptrsPlayers.back();
		m_ptrsPlayers.pop_back();
	}
}



//Static Private Data Members
mt19937 Game_5CardDraw::s_RandGen(chrono::steady_clock::now().time_since_epoch().count());


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

Player* Game_5CardDraw::createNPC(char npcName[10]) {
	//Create Player pointer
	Player* pNewPlayer = nullptr;

	//Attempt to create new NPC
	try
	{
		pNewPlayer = new NPC5Card(npcName);
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
	//All Players buy in / blinds
	buyInRound();

	//Deal cards to all players
	dealHands();

	//Betting Round (1 time around)
	bettingRound();
	
	//Draw/Replace Round (up to 5 cards per player)
	replaceRound();

	//Betting Round (1 time around, unless down to 2 players)
	bettingRound();

	//Showdown (determine winner & give payout)
	showdown();
	
	//PRINTING ALL PLAYERS' HANDS FOR TESTING PURPOSES
	printHands();

	//Prep for new game
	resetGame();

	//Ask user to continue playing (check if user can't buy in again)
	return false;
} //end of "gameLoop()"


//Private Member Functions
void Game_5CardDraw::buyInRound() {
	//Announce buy in amount for game
	cout << "Buy-in for this game is " << m_iBuyIn << " credits." << endl;
	
	//Iterate through all players backwards, have them place bets of the buyIn amounts, add to pot
	for (auto revItPlayer = m_ptrsPlayers.rbegin(); revItPlayer != m_ptrsPlayers.rend(); ++revItPlayer) {
		unsigned int iBuyInRet = (*revItPlayer)->placeBuyIn(m_iBuyIn);
		cout << '\t' << (*revItPlayer)->getName() << ((iBuyInRet != 0) ? " has bought in!" : " doesn't have enough credits to play.") << endl;
		m_iCurrentPot += iBuyInRet;
	}

	//Announce update pot
	cout << "The starting pot for this game is " << m_iCurrentPot << " credits." << endl;
} //end of "buyInRound()"

void Game_5CardDraw::dealHands() {
	//Shuffle deck
	cout << "Shuffling deck... ";
	m_Deck.shuffle();
	cout << "Deck shuffled." << endl;

	//Deal up to 5 cards per player (uses number of cards dealt to User to check)
	cout << "Dealing cards to each player... ";
	while (m_ptrsPlayers[0]->getHandCount() < m_ptrsPlayers[0]->getHandSize()) {
		//Iterate through all players backwards, deal 1 card to each active player
		for (auto revItPlayer = m_ptrsPlayers.rbegin(); revItPlayer != m_ptrsPlayers.rend(); ++revItPlayer) {
			if ((*revItPlayer)->getActiveStatus()) {
				(*revItPlayer)->addCard(m_Deck.popNextCard());
			}
		}
	}
	cout << "All cards have been dealt." << endl;

	//Set each active player's hand rank
	for (auto itPlayer = m_ptrsPlayers.begin(); itPlayer != m_ptrsPlayers.end(); ++itPlayer) {
		if ((*itPlayer)->getActiveStatus()) {
			(*itPlayer)->determineHandRank();
		}
	}
} //end of "dealHands()"

void Game_5CardDraw::bettingRound() {
	unsigned int iMinimumBet = m_iMinBet;

	//Iterate through all players backwards, if they're active have them determine bets until all bets are equalized
	auto revItPlayer = m_ptrsPlayers.rbegin();
	while (revItPlayer != m_ptrsPlayers.rend()) {
		//cycle through players to bet
		for (revItPlayer = m_ptrsPlayers.rbegin(); revItPlayer != m_ptrsPlayers.rend(); ++revItPlayer) {
			if ((*revItPlayer)->getActiveStatus()) {
				unsigned int iCurrentBet = (*revItPlayer)->determineBet(iMinimumBet);
				if (iCurrentBet != 0) {
					iMinimumBet = iCurrentBet;
				}
			}
		}

		//search for an active player who does not have an updated bet
		revItPlayer = find_if_not(m_ptrsPlayers.rbegin(), m_ptrsPlayers.rend(), [&iMinimumBet](Player* player) 
			{ return (player->getActiveStatus() && player->getCurrentBet() == iMinimumBet) || !player->getActiveStatus(); });
	}

	//Apply everyone's stored bet to the pot
	for (revItPlayer = m_ptrsPlayers.rbegin(); revItPlayer != m_ptrsPlayers.rend(); ++revItPlayer) {
		m_iCurrentPot += (*revItPlayer)->placeCurrentBet();
	}

	//Announce the updated pot
	cout << "The pot is now " << m_iCurrentPot << " credits." << endl;
} //end of "bettingRound()"

void Game_5CardDraw::replaceRound() {
	cout << "\nNEED TO CODE REPLACE ROUND" << endl;

	printHands();

	//Iterate through all players backwards, if they're active have them take their replace card round turn.
	for (auto revItPlayer = m_ptrsPlayers.rbegin(); revItPlayer != m_ptrsPlayers.rend(); ++revItPlayer) {
		if ((*revItPlayer)->getActiveStatus()) {
			vector<size_t> replaceCardsIndexes = (*revItPlayer)->determineReplaceCardsIndexes();

			//replace cards here
			if (replaceCardsIndexes.size() > 0) {
				for (auto it = replaceCardsIndexes.cbegin(); it != replaceCardsIndexes.cend(); ++it) {
					(*revItPlayer)->replaceCardAt(*it, m_Deck.popNextCard());
				}
			}

			//announce number of cards replaced
			cout << '\t' << (*revItPlayer)->getName();
			if (replaceCardsIndexes.size() == 0) {
				cout << " kept all their cards." << endl;
			}
			else {
				cout << " replaced " << replaceCardsIndexes.size() << " card" << ((replaceCardsIndexes.size() == 1) ? "." : "s.") << endl;
			}

			//update hand rank
			(*revItPlayer)->determineHandRank();
		}
	}

	cout << endl;
}

void Game_5CardDraw::resetGame() {
	//Reset each player's hands and active status
	for (auto itPlayer = m_ptrsPlayers.begin(); itPlayer != m_ptrsPlayers.end(); ++itPlayer) {
		(*itPlayer)->clearHand();
		(*itPlayer)->setActiveStatus(true);
		//check for new variables added
	}

	//Reinitialize the deck
	m_Deck.initDeck();
}

void Game_5CardDraw::showdown() {
	//Find winner based on largest hand
	auto itWinner = max_element(m_ptrsPlayers.begin(), m_ptrsPlayers.end(), [](Player* pLHS, Player* pRHS) 
		{ return pLHS->getHand() < pRHS->getHand() && pLHS->getActiveStatus() && pRHS->getActiveStatus(); });

	//Check if there are multiple winners
	int iWinners = count_if(m_ptrsPlayers.cbegin(), m_ptrsPlayers.cend(), [&itWinner](Player* pOtherPlayer) 
		{ return (*itWinner)->getHand() == pOtherPlayer->getHand() && pOtherPlayer->getActiveStatus(); });
	
	//Add all winners to vector of Player*
	vector<Player*> ptrsWinners;
	auto itCurrentPlayer = m_ptrsPlayers.begin();
	for (int i = 0; i < iWinners; ++i) {
		itCurrentPlayer = find_if(itCurrentPlayer, m_ptrsPlayers.end(), [&itWinner](Player* pOtherPlayer) 
			{ return (*itWinner)->getHand() == pOtherPlayer->getHand() && pOtherPlayer->getActiveStatus(); });
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
	
	//Any leftover credits in pot from integer rounding will be rolled over into next pot
} //end of "showdown()"

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

unsigned int Game_5CardDraw::rollNumber(unsigned int low, unsigned int high) {
	return uniform_int_distribution<unsigned int> {low, high}(s_RandGen);
}