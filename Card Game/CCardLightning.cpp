//  CCardLightning.cpp - Niall Starkey

//
//	Implementation of the Lightning card class
//

//  HEADERS:  //
#include "pch.h"
#include "CCardLightning.h"
#include "CCardMinion.h"

//  FUNCTIONS:  //
//  Loads the member variables with the stats of the card, using the passed vector.
void CCardLightning::LoadStats(VectorString stats)
{
	const	int		kTYPE_POS = 0;
	const	int		kNAME_POS = 1;
	const	int		kATTACK_POS = 2;

	mType		= stoi(stats[kTYPE_POS]);
	mName		= stats[kNAME_POS];
	mAttack		= stoi(stats[kATTACK_POS]);
}

//  Inflicts 1 point of damage to the enemy player and all their active cards.
void CCardLightning::Activate(PlayerList::iterator pEnemy)
{
	std::cout << mName << " activated: inflicted " << mAttack
		<< " to all enemies" << std::endl;

	int		enemyHealth = (*pEnemy)->GetHealth();
	enemyHealth -= mAttack;	//	Reduces enemy health by attack
	(*pEnemy)->SetHealth(enemyHealth);

	//  Loops through enemy cards in play.
	auto p = (*pEnemy)->mInPlay.begin();
	while (p != (*pEnemy)->mInPlay.end())
	{
		CCardMinion*	pMinion		= dynamic_cast<CCardMinion*>((*p).get());	// Converts ICard to CCardMinion

		pMinion->mHealth -= mAttack;	// Reduces card health by attack

		//  Removes card if it is dead, otherwise increments loop.
		if (pMinion->mHealth <= 0)
		{
			p	= (*pEnemy)->mInPlay.erase(p);	// Remove card from list
		}
		else
		{
			p++;	// Increment loop
		}
	}
}

//  Returns a random number within the range (0, number - 1) using a seeded random.
int CCardLightning::GetRandom(const float number)
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
CCardLightning::CCardLightning()
{
}

//  DESTRUCTORS:  //
CCardLightning::~CCardLightning()
{
}
