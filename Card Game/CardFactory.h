//  CardFactory.h - Niall Starkey

//
//	Factory function declaration to create CCard*** objects
//

#ifndef CARD_FACTORY_H
#define CARD_FACTORY_H

//  HEADERS: //
#include "ICard.h"

//  ENUMS:  //
enum ECardType
{
	Minion		= 1,
	Fireball	= 2,
	Lightning	= 3,
	Bless		= 4,
	Vampire		= 5
};

//  FUNCTIONS:  //
ICard* NewCard(ECardType cardType);

#endif	//	CARD_FACTORY_H