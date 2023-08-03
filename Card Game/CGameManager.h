//  CGameManager.h - Niall Starkey

//
//  Declaration of the game manager class
//

#ifndef CGAME_MANAGER_H
#define CGAME_MANAGER_H

//  HEADERS:  //
#include <iostream>
#include <deque>
#include <algorithm>

#include "Definitions.h"
#include "CFileManager.h"

#include "CardFactory.h"
#include "CCardMinion.h"
#include "CCardFireball.h"
#include "CCardVampire.h"

//  CLASS:  //
class CGameManager
{
//  PRIVATE:  //
private:
	//  CONSTANTS:  //
	const int		mkMAX_ROUND = 30;

	//	VARIABLES:  //
	VectorString	mDeckLocations;
	int				mCurrentRound = 1;

//  PUBLIC:  //
public:
	//  VARIABLES: //
	PlayerList	mPlayers;

	//  GETTERS:  //
	VectorString GetDeckLocations();

	int GetCurrentRound();

	//  SETTERS:  //
	void SetDeckLocations
	(
		VectorString	deckLocations
	);

	//  METHODS:  //
	void LoadPlayers();

	bool IsGameOver();

	void EndTurn();

	void IncrementRound();

	void DisplayTable
	(
		PlayerList::iterator	pPlayer
	);

	//  CONSTURCTORS:  //
	CGameManager();

	//  DESTRUCTORS:  //
	~CGameManager();
};
#endif	// CGAME_MANAGER_H