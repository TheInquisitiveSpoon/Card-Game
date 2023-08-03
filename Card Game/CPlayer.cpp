// CPlayer.cpp - Niall Starkey

//
//	Implementation of the Player class
//

//  HEADERS:  //
#include "pch.h"
#include "CPlayer.h"
#include "CardFactory.h"
#include "CCardFireball.h"
#include "CCardLightning.h"
#include "CCardBless.h"
#include "CCardVampire.h"

//  GETTERS:  //
//  Getter function for the player name.
std::string CPlayer::GetName()
{
	return	mName;
}

//  Getter function for the player health.
int CPlayer::GetHealth()
{
	return	mHealth;
}

//  Getter function for the player last turn.
int CPlayer::GetLastTurn()
{
	return	mLastTurn;
}

	//  SETTERS:  //
//  Setter function for the player name.
void CPlayer::SetName(std::string name)
{
	mName = name;
}

//  Setter function for the player health.
void CPlayer::SetHealth(int health)
{
	mHealth	= health;
}

//  Setter function for the player last turn.
void CPlayer::SetLastTurn(int turn)
{
	mLastTurn = turn;
}

//  METHODS:  //
//  Starts the game by drawing the first card from the deck.
void CPlayer::StartGame()
{
	std::cout << mName << " begins with " << (*mDeck.begin())->mName << std::endl;

	mHand.push_back(move((*mDeck.begin())));	// Move card from deck to hand
	mDeck.pop_front();
}

//  Draws another card from the deck into the hand.
void CPlayer::DrawCard()
{
	std::cout << mName << " draws " << (*mDeck.begin())->mName << std::endl;

	mHand.push_back(move((*mDeck.begin())));	// Move card from deck to hand
	mDeck.pop_front();
}

//  Plays a random card from the hand, if it is a spell then it will activate it's
//  effect immediately and then remove it from the hand, if it is a minion it will
//  add it to the inplay list.
void CPlayer::PlayCard(std::deque<std::unique_ptr<CPlayer>>::iterator pEnemy,
	std::deque<std::unique_ptr<CPlayer>>::iterator pPlayer)
{
	int		cardPosition = GetRandom(mHand.size());	// Gets a random number

	std::cout << mName << " plays " << mHand[cardPosition]->mName << std::endl;

	std::deque<std::unique_ptr<ICard>>::iterator	p;

	//  Loops through the hand list to find the card.
	for (auto p = mHand.begin(); p != mHand.end(); p++)
	{
		//  Checks if the card name matches the chosen card.
		if ((*p)->mName == mHand[cardPosition]->mName)
		{
			//  Handles the activation and removal or moving of the chosen card based
			//  on the card type.
			if ((*p)->mType == Minion || (*p)->mType == Vampire)
			{
				mInPlay.push_back(move((*p)));	// Moves a minion or vampire to the inplay list
				mHand.erase(p);	// Erases the card from the hand
				break;
			}
			else if ((*p)->mType == Fireball)
			{
				CCardFireball*	pFireball	= dynamic_cast<CCardFireball*>((*p).get());	// Converts ICard to CCardFireball
				pFireball->Activate(pEnemy);	// Activates the fireball spell
				mHand.erase(p);	// Erases the card from the hand
				break;
			}
			else if ((*p)->mType == Lightning)
			{
				CCardLightning*		pLightning	= dynamic_cast<CCardLightning*>
					((*p).get());	// Converts ICard to CCardLightning
				pLightning->Activate(pEnemy);	// Activates the lightning spell
				mHand.erase(p);	// Erases the card from the hand
				break;
			}
			else if ((*p)->mType == Bless)
			{
				CCardBless*		pBless	= dynamic_cast<CCardBless*>((*p).get());	// Converts ICard to CCardBless
				pBless->Activate(pEnemy, pPlayer);	// Activates the bless spell
				mHand.erase(p);	// Erases the card from the hand
				break;
			}
		}
	}
}

//  Returns a random number within the range (0, number - 1) using a seeded random.
int CPlayer::GetRandom(const float number)
{
	int		random = static_cast<int>(static_cast<double> (rand()) /
		(RAND_MAX + 1) * (number + 1));	// Get number between (0, number)

	if (random != 0)
	{
		random--;	// Reduce number if it isn't 0
	}

	return	random;
}

//  CONSTRUCTORS:  //
CPlayer::CPlayer()
{
	const	int		kDEFAULT_HEALTH = 30;

	SetHealth(kDEFAULT_HEALTH);	// Sets the initial health of the player
}

//  DESTRUCTORS:  //
CPlayer::~CPlayer()
{
}
