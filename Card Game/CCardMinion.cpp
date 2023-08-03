//  CCardMinion.cpp - Niall Starkey

//
//	Implementation of Minion card class
//

//  HEADERS:  //
#include "pch.h"
#include "CCardMinion.h"
#include "CCardVampire.h"
#include "CardFactory.h"

//  FUNCTIONS:  //
//  Loads the member variables with the stats of the card, using the passed vector.
void CCardMinion::LoadStats(VectorString stats)
{
	const	int		kTYPE_POS = 0;
	const	int		kNAME_POS = 1;
	const	int		kATTACK_POS = 2;
	const	int		kHEALTH_POS = 3;

	mType		= std::stoi(stats[kTYPE_POS]);
	mName		= stats[kNAME_POS];
	mAttack		= std::stoi(stats[kATTACK_POS]);
	mHealth		= std::stoi(stats[kHEALTH_POS]);
}

//  Attacks an enemy card, or player if there are no active cards, dealing damage
//  equal to the attack value.
bool CCardMinion::Attack(PlayerList::iterator pEnemy)
{
	//  Checks whether to attack the enemy or an enemy card, if the enemy has active
	//  cards.
	if ((*pEnemy)->mInPlay.empty())
	{
		int		enemyHealth = (*pEnemy)->GetHealth();
		enemyHealth -= mAttack;	// Reduces enemy health by attack
		(*pEnemy)->SetHealth(enemyHealth);

		std::string enemyName	= (*pEnemy)->GetName();	// Stores enemy name for output

		std::cout << mName << " attacks " << enemyName << ": " 
			<< enemyName << " health now " << enemyHealth << std::endl;

		return	true;	// Returns true to signal enemy has been attacked
	}
	else
	{
		int		target = 0;
		target	= GetRandom((*pEnemy)->mInPlay.size());	// Gets random number

		//  Handles attacking different enemy types.
		if ((*pEnemy)->mInPlay[target]->mType == Minion)
		{
			CCardMinion*	pEnemyMinion	= dynamic_cast<CCardMinion*>
				((*pEnemy)->mInPlay[target].get());	// Converts ICard to CCardMinion

			pEnemyMinion->mHealth -= mAttack;	// Reduces card health by attack

			std::cout << mName << " attacks "
				<< pEnemyMinion->mName << ": " << pEnemyMinion->mName;

			//  Handles if the enemy card died, and outputs what happened.
			if (pEnemyMinion->mHealth <= 0)
			{
				std::cout << " killed" << std::endl;

				CardList::iterator	p;

				//  Loop through enemy cards in play to find the right card
				for (auto p = (*pEnemy)->mInPlay.begin();
					p != (*pEnemy)->mInPlay.end(); p++)
				{
					//  Handles removing different enemy card types
					if ((*p)->mType == Minion)
					{
						CCardMinion*	pCard	= dynamic_cast<CCardMinion*>
							((*p).get());	// Converts ICard to CCardMinion

						//  Removes card if health matches.
						if (pCard->mHealth == pEnemyMinion->mHealth)
						{
							(*pEnemy)->mInPlay.erase(p);	// Remove card from list
							break;
						}
					}
					else if ((*p)->mType == Vampire)
					{
						CCardVampire*	pCard	= dynamic_cast<CCardVampire*>
							((*p).get());	// Convert ICard to CCardVampire

						//  Removes card if health matches.
						if (pCard->mHealth == pEnemyMinion->mHealth)
						{
							(*pEnemy)->mInPlay.erase(p);	// Remove card from list
							break;
						}
					}
				}
			}
			else
			{
				std::cout << " health is now " << pEnemyMinion->mHealth << std::endl;
			}
		}
		else if ((*pEnemy)->mInPlay[target]->mType == Vampire)
		{
			CCardVampire*	pEnemyVampire	= dynamic_cast<CCardVampire*>
				((*pEnemy)->mInPlay[target].get());	// Converts ICard to CCardVampire

			pEnemyVampire->mHealth -= mAttack;	// Reduce health by attack

			std::cout << mName << " attacks "
				<< pEnemyVampire->mName << ": " << pEnemyVampire->mName;

			//  Handles if enemy card dies, outputs what has happened.
			if (pEnemyVampire->mHealth <= 0)
			{
				std::cout << " killed" << std::endl;

				CardList::iterator	p;

				//  Loops through enemy cards in play.
				for (auto p = (*pEnemy)->mInPlay.begin(); p != (*pEnemy)->mInPlay.end(); p++)
				{
					//  Handles removal of different card types.
					if ((*p)->mType == Minion)
					{
						CCardMinion*	pCard	= dynamic_cast<CCardMinion*>
							((*p).get());	// Converts ICard to CCardMinion

						// Removes card if health matches.
						if (pCard->mHealth == pEnemyVampire->mHealth)
						{
							(*pEnemy)->mInPlay.erase(p);	// Remove card from list
							break;
						}
					}
					else if ((*p)->mType == Vampire)
					{
						CCardVampire*	pCard	= dynamic_cast<CCardVampire*>
							((*p).get());	// Converts ICard to CCardVampire

						//  Removes card if health matches.
						if (pCard->mHealth == pEnemyVampire->mHealth)
						{
							(*pEnemy)->mInPlay.erase(p);	// Remove card from list
							break;
						}
					}
				}
			}
			else
			{
				std::cout << " health is now " << pEnemyVampire->mHealth << std::endl;
			}
		}
	}

	return false;	// Return false if player was not attacked
}

//  Returns a random number within the range (0, number - 1) using a seeded random.
int CCardMinion::GetRandom(const float number)
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
CCardMinion::CCardMinion()
{

}

//  DESTRUCTORS:  //
CCardMinion::~CCardMinion()
{

}