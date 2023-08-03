//	Card Game.cpp - Niall Starkey

//
//	Main source for Card Game project
//

//  HEADERS:  //
#include "pch.h"
#include <crtdbg.h>
#include <iostream>
#include <deque>
#include <vector>

#include "CGameManager.h"

//  FORWARD DECLARATIONS:  //
void PlayGame();

//  MAIN:  //
int main()
{
	PlayGame();	// Call to game function
	_CrtDumpMemoryLeaks();	// Output memory leaks
}

//  FUNCTIONS:  //
void PlayGame()
{
	//  CONSTANTS:  //
	const	VectorString	kDECK_LOCATIONS = { "../Sorceress.txt", "../Wizard.txt" };
	const	int				kSEED = 6;

	//  VARIABLES:  //
	std::unique_ptr<CGameManager>	pGame(new CGameManager);
	PlayerList::iterator			p;

	std::srand(kSEED);	// Seed the random generator
	pGame->SetDeckLocations(kDECK_LOCATIONS);	// Sets the file locations for the desk in the manager
	pGame->LoadPlayers();	// Loads the players and decks

	//  Draws a card from the deck for each player to begin the game.
	for (auto p = pGame->mPlayers.begin(); p != pGame->mPlayers.end(); p++)
	{
		(*p)->StartGame();	// Call to function that draws cards
	}

	//  Loops until the game is over so the game outputs what happens until the
	//  end of play.
	while (!pGame->IsGameOver())
	{
		std::cout << std::endl << "ROUND " << pGame->GetCurrentRound() << std::endl;	// Outputs the current round number

		//  Loops for each player, ensuring both players have their turn before the
		//  end of the round.
		for (auto p = pGame->mPlayers.begin(); p != pGame->mPlayers.end(); p++)
		{
			PlayerList::iterator	player;
			PlayerList::iterator	enemy;
			int						attackingCard = 0;

			player	= pGame->mPlayers.begin();	// Sets player as the current player
			enemy	= pGame->mPlayers.end();
			enemy--;	// Sets enemy as the next in the list

			//  DRAW:  //
			if ((*player)->mDeck.empty())
			{
				break;	// Ends game if no card can be drawn
			}
			else
			{
				(*player)->DrawCard();	// Draws card from the deck to continue play
			}

			//  PLAY:  //
			(*player)->PlayCard(enemy, player);	// Randomly choose a card to play from the hand

			//  DISPLAY TABLE:  //
			if ((*enemy)->GetHealth() > 0)
			{
				pGame->DisplayTable(player);	// Displays card on the table if enemy is still alive
			}

			//  ATTACK:  //
			//  Loops through every card in play for the current player allowing
			//  each card to attack the enemy player.
			for (int i = 0; i < (*player)->mInPlay.size(); i++)
			{
				attackingCard	= i;

				//  Converts the attacking card to the correct class to conduct
				//  attack.
				if ((*player)->mInPlay[attackingCard]->mType == Minion)
				{
					CCardMinion*	pMinion		= dynamic_cast<CCardMinion*>
						((*player)->mInPlay[attackingCard].get());	// Converts ICard to CCardMinion

					//  Attacks enemy player or minion.
					if (pMinion->Attack(enemy))
					{
						//  Checks to see if the enemy has died, stops play if so.
						if ((*enemy)->GetHealth() <= 0)
						{
							break;
						}
					}
				}
				else if ((*player)->mInPlay[attackingCard]->mType == Vampire)
				{
					CCardVampire*	pVampire	= dynamic_cast<CCardVampire*>
						((*player)->mInPlay[attackingCard].get());	// Converts ICard to CCardVampire

					//  Attacks enemy player or minion.
					if (pVampire->Attack(enemy))
					{
						//  Checks to see if the enemy has died, stops play if so.
						if ((*enemy)->GetHealth() <= 0)
						{
							break;
						}
					}
				}
			}

			std::cout << std::endl;	// Outputs empty line to split each players turn output

			//  Checks if the game has ended via an empty deck, or dead player.
			if ((*player)->mDeck.empty() || (*enemy)->GetHealth() <= 0)
			{
				break;
			}

			pGame->EndTurn();	// Ends current players turn
		}

		//  END ROUND:  //
		pGame->IncrementRound();	// Ends current round
	}

	system("PAUSE");	// Pauses to read output text
}