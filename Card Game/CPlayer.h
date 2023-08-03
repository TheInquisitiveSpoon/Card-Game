//  CPlayer.h - Niall Starkey

//
//	Declaration of the Player class
//

#ifndef CPLAYER_H
#define CPLAYER_H

//  HEADERS:  //
#include <iostream>
#include <string>
#include <deque>

#include "ICard.h"

//  CLASS:  //
class CPlayer
{
//  PRIVATE:  //
private:
	//  VARIABLES:  //
	std::string		mName	= "";
	int				mHealth = 0;
	int				mLastTurn = 0;

//  PUBLIC:  //
public:
	//  VARIABLES:  //
	std::deque<std::unique_ptr<ICard>>	mDeck;
	std::deque<std::unique_ptr<ICard>>	mHand;
	std::deque<std::unique_ptr<ICard>>	mInPlay;

	//  GETTERS:  //
	std::string GetName();

	int GetHealth();

	int GetLastTurn();

	//  SETTERS:  //
	void SetName
	(
		std::string		name
	);

	void SetHealth
	(
		int		health
	);

	void SetLastTurn
	(
		int		turn
	);

	//  METHODS:  //
	void StartGame();

	void DrawCard();

	int GetRandom
	(
		const	float	number
	);

	void PlayCard
	(
		std::deque<std::unique_ptr<CPlayer>>::iterator	pEnemy,
		std::deque<std::unique_ptr<CPlayer>>::iterator	pPlayer
	);

	//  CONTRUCTORS:  //
	CPlayer();

	//  DESTRUCTORS:  //
	~CPlayer();
};

#endif	// CPLAYER_H