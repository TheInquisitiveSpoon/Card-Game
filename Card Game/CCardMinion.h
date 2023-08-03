//  CCardMinion.h - Niall Starkey

//
//	Declaration of the Minion card class
//

#ifndef CCARD_MINION_H
#define CCARD_MINION_H

//  HEADERS:  //
#include "Definitions.h"

//  CLASS:  //
class CCardMinion : public ICard
{
public:
	//  MEMBER VARIABLES:  //
	int		mAttack = 0;
	int		mHealth = 0;

	//  FUNCTIONS:  //
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
	CCardMinion();

	//  DESTRUCTORS:  //
	~CCardMinion();
};

#endif	// C_CARD_MINION