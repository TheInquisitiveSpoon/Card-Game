//	CCardBless - Niall Starkey

//
//	Declaration of the Bless card class
//

#ifndef CCARD_BLESS_H
#define CCARD_BLESS_H

//  HEADERS:  //
#include "Definitions.h"

//  CLASS:  //
class CCardBless : public ICard
{
public:
	//  MEMBER VARIABLES:  //
	int		mAttack = 0;
	int		mHeal = 0;

	//  FUNCTIONS:  //
	void LoadStats
	(
		VectorString	stats
	);

	void Activate
	(
		PlayerList::iterator	pEnemy,
		PlayerList::iterator	pPlayer
	);

	int GetRandom
	(
		const float		number
	);

	//  CONSTRUCTORS:  //
	CCardBless();

	//  DESTRUCTORS:  //
	~CCardBless();
};

#endif	//	CCARD_BLESS_H