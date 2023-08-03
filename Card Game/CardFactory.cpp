//  CardFactory.h - Niall Starkey

//
//  Factory function implementation to create CCard*** objects
//

//  HEADERS:  //
#include "pch.h"
#include "CardFactory.h"
#include "CCardMinion.h"
#include "CCardFireball.h"
#include "CCardLightning.h"
#include "CCardBless.h"
#include "CCardVampire.h"

//  Returns derived class constructor based on card type.
ICard* NewCard(ECardType cardType)
{
	switch (cardType)
	{
		case Minion:
		{
			return	new		CCardMinion();	// Returns new Minion card
		}

		case Fireball:
		{
			return	new		CCardFireball();	// Returns new Fireball card
		}

		case Lightning:
		{
			return	new		CCardLightning();	// Returns new Lightning card
		}

		case Bless:
		{
			return	new		CCardBless();	// Returns new Bless card
		}

		case Vampire:
		{
			return	new		CCardVampire();	// Returns new Vamire card
		}
	}
}
