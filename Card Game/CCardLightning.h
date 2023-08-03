//  CCardLightning.h - Niall Starkey

//
//	Declaration of the Lightning card class
//

#ifndef CCARD_LIGHTNING_H
#define CCARD_LIGHTNING_H

//  HEADERS:  //
#include <algorithm>
#include "Definitions.h"

//  CLASS:  //
class CCardLightning : public ICard
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
	CCardLightning();

	//  DESTRUCTORS:  //
	~CCardLightning();
};

#endif	//	CCARD_LIGHTNING_H