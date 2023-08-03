//  CCardFireball.cpp - Niall Starkey

//
//	Implementation of the Fireball card class
//

//  HEADERS:  //
#include "pch.h"
#include "CCardFireball.h"
#include "CCardMinion.h"
#include "CCardVampire.h"
#include "CardFactory.h"

//  FUNCTIONS:  //
//  Loads the member variables with the stats of the card, using the passed vector.
void CCardFireball::LoadStats(VectorString stats)
{
	const	int		kTYPE_POS = 0;
	const	int		kNAME_POS = 1;
	const	int		kATTACK_POS = 2;

	mType		= stoi(stats[kTYPE_POS]);
	mName		= stats[kNAME_POS];
	mAttack		= stoi(stats[kATTACK_POS]);
}

//  Randomly chooses a target between the enemy player and enemy minions, with the 
//  enemy player having a 75% chance to be attacked, inflicts 3 points of damage to
//  the chosen target.
void CCardFireball::Activate(PlayerList::iterator pEnemy)
{
	const	int		kPOSSIBLE_ACTIONS = 4;
	const	int		kATTACK_PLAYER_CHANCE = 3;

	int				random = GetRandom(kPOSSIBLE_ACTIONS);	// Gets random number

	//  Handles attacking the enemy player or attacking an enemy card
	if (random < kATTACK_PLAYER_CHANCE)
	{
		int		enemyHealth = (*pEnemy)->GetHealth();
		enemyHealth -= mAttack;	// Reduces enemy health by attack
		(*pEnemy)->SetHealth(enemyHealth);

		std::cout << mName << " activated: " << (*pEnemy)->GetName()
			<< " health is now " << enemyHealth << std::endl;
	}
	else
	{
		int		target = GetRandom((*pEnemy)->mInPlay.size());	// Gets random number

		CCardMinion*	pMinion		= dynamic_cast<CCardMinion*>
			((*pEnemy)->mInPlay[target].get());	// Converts from ICard to CCardMinion

		pMinion->mHealth -= mAttack;	// Reduced minion health by attack

		std::cout << mName << " activated: " << pMinion->mName;
		
		//  Handles whether enemy card is dead, and outputs what has occured.
		if (pMinion->mHealth > 0)
		{
			std::cout << " health is now " << pMinion->mHealth << std::endl;
		}
		else
		{
			PlayerList::iterator	p;

			//  Loops through enemy table to find card to remove.
			for (auto p = (*pEnemy)->mInPlay.begin();
				p != (*pEnemy)->mInPlay.end(); p++)
			{
				//  Handles removal of different card types.
				if ((*p)->mType == Minion)
				{
					CCardMinion*	pCard = dynamic_cast<CCardMinion*>((*p).get());	// Converts ICard to CCardMinion

					//  Removes card if health matches.
					if (pCard->mHealth == pMinion->mHealth)
					{
						std::cout << pMinion->mName << " killed" << std::endl;
						(*pEnemy)->mInPlay.erase(p);	// Removes card from list
						break;
					}
				}
				else if ((*p)->mType == Vampire)
				{
					CCardVampire*	pCard = dynamic_cast<CCardVampire*>((*p).get());	// Converts ICard to CCardVampire

					//  Removes card if health matches.
					if (pCard->mHealth == pMinion->mHealth)
					{
						std::cout << pMinion->mName << " killed" << std::endl;
						(*pEnemy)->mInPlay.erase(p);	// Removes card from list
						break;
					}
				}
			}
		}
	}
}

//  Returns a random number within the range (0, number - 1) using a seeded random.
int CCardFireball::GetRandom(const float number)
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
CCardFireball::CCardFireball()
{

}

//  DESTRUCTORS:  //
CCardFireball::~CCardFireball()
{

}
