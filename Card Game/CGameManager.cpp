//  HEADERS:  //
#include "pch.h"
#include "CGameManager.h"

//  GETTERS:  //
//  Getter function for the mDeckLocations member variable.
VectorString CGameManager::GetDeckLocations()
{
	return	mDeckLocations;
}

//  Getter function for the mCurrentRound member variable.
int CGameManager::GetCurrentRound()
{
	return	mCurrentRound;
}

//  SETTERS:  //
//  Setter function for the mDeckLocations member variable.
void CGameManager::SetDeckLocations(VectorString deckLocations)
{
	mDeckLocations	= deckLocations;
}

//  METHODS:  //
//  Reads each file in mDeckLocations and creates a player using the file information
//  also creating the players deck.
void CGameManager::LoadPlayers()
{
	std::unique_ptr<CFileManager>	fileManager(new CFileManager);

	//  Loops through the deck locations.
	for (int i = 0; i < mDeckLocations.size(); i++)
	{
		VectorString	cards = fileManager->GetFileText(mDeckLocations[i]);	// Gets the text for each card in deck
		PlayerPointer	pPlayer(new CPlayer);	// Creates a new player
		pPlayer->SetName(fileManager->GetFileName(mDeckLocations[i]));	// Sets player name to the deck location file name

		//  Loops through each card in the deck.
		for (int j = 0; j < cards.size(); j++)
		{
			VectorString	stats = fileManager->SplitString(cards[j], ' ');	// Splits the card information into a vector

			//  Loops through each stat in the container.
			if (stoi(stats[0]) < stats.size())
			{
				ECardType		cardType = (ECardType)stoi(stats[0]);	// Determines the card type

				CardPointer		pNewCard(NewCard(cardType));	// Creates new class of the card type
				pNewCard->LoadStats(stats);	// Loads card stats using the container
				pPlayer->mDeck.push_back(move(pNewCard));	// Adds card to player deck list
			}
		}

		mPlayers.push_back(move(pPlayer));	// Adds player to list
	}
}

//  Outputs the name and health of each card in play.
void CGameManager::DisplayTable(PlayerList::iterator pPlayer)
{
	std::cout << "Cards on table: ";

	CardList::iterator	p;

	//  Loops through each card in play.
	for (auto p = (*pPlayer)->mInPlay.begin(); p != (*pPlayer)->mInPlay.end(); p++)
	{
		//  Handles text output for different card types.
		if ((*p)->mType == Minion)
		{
			CCardMinion*	pMinion		= dynamic_cast<CCardMinion*>((*p).get());	// Converts ICard to CCardMinion
			std::cout << pMinion->mName << "(" << pMinion->mHealth << ") ";
		}
		else if ((*p)->mType == Vampire)
		{
			CCardVampire*	pVampire	= dynamic_cast<CCardVampire*>((*p).get());	// Converts ICard to CCardVampire
			std::cout << pVampire->mName << "(" << pVampire->mHealth << ") ";
		}
	}

	std::cout << std::endl;
}

//  Checks whether the game is over or not, based on if each player has cards left
//  in their deck and if they are alive, or if the max round has been reached.
bool CGameManager::IsGameOver()
{
	PlayerList::iterator	p;

	//  Returns true if the max round has been reached.
	if (mCurrentRound > mkMAX_ROUND)
	{
		return	true;
	}

	//  Loops through each player in the game.
	for (auto p = mPlayers.begin(); p != mPlayers.end(); p++)
	{
		//  Returns true if the player is dead.
		if ((*p)->GetHealth() <= 0)
		{
			std::cout << (*p)->GetName() << " has been killed" << std::endl;
			return	true;
		}

		//  Returns true if the player has no more cards in the deck.
		if ((*p)->mDeck.empty())
		{
			std::cout << (*p)->GetName() << " has no more cards." << std::endl;
			return	true;
		}
	}

	return	false;	// Return false if no conditions are met
}

//  Ends the turn of the current player, sorting the player list on their last time.
void CGameManager::EndTurn()
{
	PlayerList::iterator	p;

	//  Loops through the player list.
	for (auto p = mPlayers.begin(); p != mPlayers.end(); p++)
	{
		//  Changes the last turn for each player.
		if (p != mPlayers.begin())
		{
			int		lastTurn = (*p)->GetLastTurn() + 1;	// Add 1 to the last turn of the enemy player
			(*p)->SetLastTurn(lastTurn);
		}
		else
		{
			(*p)->SetLastTurn(0);	// Reset the last turn of the current player
		}
	}

	//  Sorts the player list in ascending order of their last turn.
	std::sort(mPlayers.begin(), mPlayers.end(), [](PlayerPointer& firstPlayer,
		PlayerPointer& secondPlayer) {return firstPlayer->GetLastTurn() >
		secondPlayer->GetLastTurn();  });
}

//  Adds 1 to the current round counter.
void CGameManager::IncrementRound()
{
	mCurrentRound++;
}

//  CONSTRUCTORS:  //
CGameManager::CGameManager()
{
}

//  DESTRUCTORS:  //
CGameManager::~CGameManager()
{
	mPlayers.~deque();
}
