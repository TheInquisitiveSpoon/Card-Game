//	CCardVampire.cpp - Niall Starkey

//
//	Implementation of the Vampire card class
//

//  HEAERS:  //
#include "pch.h"
#include "CCardVampire.h"
#include "CCardMinion.h"

//  FUNCTIONS:  //
//  Loads the member variables with the stats of the card, using the passed vector.
void CCardVampire::LoadStats(VectorString stats)
{
	const	int		kTYPE_POS = 0;
	const	int		kNAME_POS = 1;
	const	int		kATTACK_POS = 2;
	const	int		kHEALTH_POS = 3;
	const	int		kHEAL_POS = 4;

	mType		= std::stoi(stats[kTYPE_POS]);
	mName		= stats[kNAME_POS];
	mAttack		= std::stoi(stats[kATTACK_POS]);
	mHealth		= std::stoi(stats[kHEALTH_POS]);
	mHeal		= std::stoi(stats[kHEAL_POS]);
}

//  Attacks an enemy card, or player if there are no active cards, dealing damage
//  equal to the attack value, and healing equal to the heal value.
bool CCardVampire::Attack(PlayerList::iterator pEnemy)
{
	//  Handles which target to attack, based on if the player has any active cards.
	if ((*pEnemy)->mInPlay.empty())
	{
		int		enemyHealth = (*pEnemy)->GetHealth();
		enemyHealth -= mAttack;	// Reduce enemy health by attack
		(*pEnemy)->SetHealth(enemyHealth);
		mHealth += mHeal;	// Increase current health by heal

		std::string		enemyName = (*pEnemy)->GetName();	// Store enemy name for output

		std::cout << mName << " attacks " << enemyName << ": "
			<< enemyName << " health now " << enemyHealth << std::endl;

		return	true;	// Return true if enemy player attacked
	}
	else
	{
		int		target = 0;
		target	= GetRandom((*pEnemy)->mInPlay.size());	// Gets random number

		CCardMinion*	pEnemyMinion	= dynamic_cast<CCardMinion*>
			((*pEnemy)->mInPlay[target].get());	// Converts ICard to CCardMinion

		pEnemyMinion->mHealth -= mAttack;	// Reduce card health by attack
		mHealth += mHeal;	// Increase health by heal

		std::cout << mName << " attacks "
			<< pEnemyMinion->mName << ": " << pEnemyMinion->mName;

		//  Handles if the enemy card died, and outputs what happened.
		if (pEnemyMinion->mHealth <= 0)
		{
			std::cout << " killed" << std::endl;

			CardList::iterator	p;

			//  Loop through the enemy active cards.
			for (auto p = (*pEnemy)->mInPlay.begin();
				p != (*pEnemy)->mInPlay.end(); p++)
			{
				CCardMinion*	pCard	= dynamic_cast<CCardMinion*>((*p).get());	// Converts ICard to CCardVampire

				//  Removes card if health matches
				if (pCard->mHealth == pEnemyMinion->mHealth)
				{
					(*pEnemy)->mInPlay.erase(p);	// Remove card from list
					break;
				}
			}
		}
		else
		{
			std::cout << " health is now " << pEnemyMinion->mHealth << std::endl;
		}
	}

	return false;	// Return false if enemy player was not attacked
}

//  Returns a random number within the range (0, number - 1) using a seeded random.
int CCardVampire::GetRandom(const float number)
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
CCardVampire::CCardVampire()
{
}

//  DESTRUCTORS:  //
CCardVampire::~CCardVampire()
{
}
