//	CCardBless.cpp - Niall Starkey

//
//	Implementation of the Bless card class
//

//  HEADERS:  //
#include "pch.h"
#include "CCardBless.h"
#include "CCardMinion.h"
#include "CCardVampire.h"
#include "CardFactory.h"

//  FUNCTIONS:  //
//  Loads the member variables with the stats of the card, using the passed vector.
void CCardBless::LoadStats(VectorString stats)
{
	const	int		kTYPE_POS = 0;
	const	int		kNAME_POS = 1;
	const	int		kATTACK_POS = 2;
	const	int		kHEAL_POS = 3;

	mType		= stoi(stats[kTYPE_POS]);
	mName		= stats[kNAME_POS];
	mAttack		= stoi(stats[kATTACK_POS]);
	mHeal		= stoi(stats[kHEAL_POS]);
}

//  Chooses a target at random from all friendly/enemy minions/players and deals
//  either 2 damage or heals 2 points of health.
void CCardBless::Activate(PlayerList::iterator pEnemy,
	PlayerList::iterator pPlayer)
{
	const	int		kENEMY_MINIONS = 0;
	const	int		kENEMY_PLAYER = 1;
	const	int		kFRIENDLY_MINIONS = 2;
	const	int		kFRIENDLY_PLAYER = 3;

	const	int		kPOSSIBLE_ACTIONS = 4;
	int				target = GetRandom(kPOSSIBLE_ACTIONS);

	std::cout << mName << " activated: ";

	//  Chooses which action to take, based on what number the random generator
	//  returned.
	if (target == kENEMY_MINIONS)
	{
		target	= GetRandom((*pEnemy)->mInPlay.size());	// Gets random number

		//  Handles attacking different card types.
		if ((*pEnemy)->mInPlay.at(target)->mType == Minion)
		{
			CCardMinion*	pMinion		= dynamic_cast<CCardMinion*>
				((*pEnemy)->mInPlay.at(target).get());	// Converts ICard to CCardMinion

			pMinion->mHealth -= mAttack;	// Reduce health by attack of card

			//  Handles whether the enemy card has died, and outputs what has
			//  happened.
			if (pMinion->mHealth > 0)
			{
				std::cout << pMinion->mName << " health is now "
					<< pMinion->mHealth << std::endl;
			}
			else
			{
				CardList::iterator	p;

				//  Loops through enemy card in play to find what card to remove.
				for (auto p = (*pEnemy)->mInPlay.begin();
					p != (*pEnemy)->mInPlay.end(); p++)
				{
					CCardMinion*	pCard	= dynamic_cast<CCardMinion*>((*p).get());	//  Converts ICard to CCardMinion

					//  Checks if card in the list has the same health and removes it.
					if (pCard->mHealth == pMinion->mHealth);
					{
						std::cout << pMinion->mName << " killed" << std::endl;
						(*pEnemy)->mInPlay.erase(p);	// Removes card from list
						break;
					}
				}
			}
		}
		else if ((*pEnemy)->mInPlay.at(target)->mType == Vampire)
		{
			CCardVampire*	pVampire	= dynamic_cast<CCardVampire*>
				((*pEnemy)->mInPlay.at(target).get());	// Converts ICard to CCardVampire

			pVampire->mHealth -= mAttack;	// Reduce health by attack of card

			//  Handles whether the enemy card has died, and outputs what has
			//  happened.
			if (pVampire->mHealth > 0)
			{
				std::cout << pVampire->mName << " health is now "
					<< pVampire->mHealth << std::endl;
			}
			else
			{
				CardList::iterator	p;

				//  Loops through enemy card in play to find what card to remove.
				for (auto p = (*pEnemy)->mInPlay.begin();
					p != (*pEnemy)->mInPlay.end(); p++)
				{
					CCardVampire*	pCard	= dynamic_cast<CCardVampire*>((*p).get());	// Converts ICard to CCardVampire

					//  Checks if card in the list has the same health and removes it.
					if (pCard->mHealth == pVampire->mHealth);
					{
						std::cout << pVampire->mName << " killed" << std::endl;
						(*pEnemy)->mInPlay.erase(p);	// Removes card from list
						break;
					}
				}
			}
		}
	}
	else if (target == kENEMY_PLAYER)
	{
		int		enemyHealth = (*pEnemy)->GetHealth();
		enemyHealth -= mAttack;	// Reduces enemy health by attack value
		(*pEnemy)->SetHealth(enemyHealth);

		std::cout << (*pEnemy)->GetName() << " health is now "
			<< enemyHealth << std::endl;
	}
	else if (target == kFRIENDLY_MINIONS)
	{
		target	= GetRandom((*pEnemy)->mInPlay.size());	// Gets random number

		//  Handles healing different card types.
		if ((*pEnemy)->mInPlay.at(target)->mType == Minion)
		{
			CCardMinion*	pMinion		= dynamic_cast<CCardMinion*>
				((*pEnemy)->mInPlay.at(target).get());	// Converts ICard to CCardMinion

			pMinion->mHealth += mHeal;	// Adds health to card

			std::cout << pMinion->mName << " health is now "
				<< pMinion->mHealth << std::endl;
		}
		else if((*pEnemy)->mInPlay.at(target)->mType == Vampire)
		{
			CCardVampire*	pVampire	= dynamic_cast<CCardVampire*>
				((*pEnemy)->mInPlay.at(target).get());	// Converts ICard to CCardVampire

			pVampire->mHealth += mHeal;	// Adds health to card

			std::cout << pVampire->mName << " health is now "
				<< pVampire->mHealth << std::endl;
		}
	}
	else if (target == kFRIENDLY_PLAYER)
	{
		int		playerHealth = (*pPlayer)->GetHealth();
		playerHealth += mHeal;	//  Adds health to player
		(*pPlayer)->SetHealth(playerHealth);

		std::cout << (*pPlayer)->GetName() << " health is now "
			<< playerHealth << std::endl;
	}
}

//  Returns a random number within the range (0, number - 1) using a seeded random.
int CCardBless::GetRandom(const float number)
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
CCardBless::CCardBless()
{
}

//  DESTRUCTORS:  //
CCardBless::~CCardBless()
{
}
