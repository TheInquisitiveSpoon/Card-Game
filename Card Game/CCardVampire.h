//	CCardVampire.h - Niall Starkey

//
//	Declaration for the Vampire card class
//

#ifndef CCARD_VAMPIRE_H
#define CCARD_VAMPIRE_H

//  HEADERS:  //
#include "Definitions.h"

//  CLASS:  //
class CCardVampire : public ICard
{
public:
	//  MEMBER VARIABLES:  //
	int		mAttack = 0;
	int		mHealth = 0;
	int		mHeal = 0;

	// FUNCTIONS:  //
	void LoadStats
	(
		VectorString	stats
	);

	bool Attack
	(
		PlayerList::iterator	pEnemy
	);

	int GetRandom
	(
		const float		number
	);

	//  CONSTRUCTORS:  //
	CCardVampire();

	//  DESTRUCTORS:  //
	~CCardVampire();
};

#endif	// CCARD_VAMPIRE_H