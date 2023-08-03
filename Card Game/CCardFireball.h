//  CCardFireball.h - Niall Starkey

//
//	Declaration of the Fireball card class
//

#ifndef CCARD_FIREBALL_H
#define CCARD_FIREBALL_H

//  HEADERS: //
#include "Definitions.h"

//  CLASS:  //
class CCardFireball : public ICard
{
public:
	//  MEMBER VARIABLES:  //
	int		mAttack = 0;

	//  FUNCTIONS:  //
	void LoadStats
	(
		VectorString	stats
	);

	void Activate
	(
		PlayerList::iterator	pEnemy
	);

	int GetRandom
	(
		const float		number
	);

	//  CONSTRUCTORS:  //
	CCardFireball();

	//  DESTRUCTORS:  //
	~CCardFireball();
};

#endif	//	CCARD_FIREBALL_H