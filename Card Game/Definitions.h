//	Definitions - Niall Starkey

//
//	Type definitions to support card game
//

#ifndef DEFINITIONS_H
#define	DEFINITIONS_H

//  HEADERS:  //
#include "pch.h"
#include <vector>
#include <deque>
#include <memory>
#include "CPlayer.h"

//  TYPE DEFINITIONS:  //
typedef		std::unique_ptr<CPlayer>	PlayerPointer;
typedef		std::deque<PlayerPointer>	PlayerList;

typedef		std::unique_ptr<ICard>		CardPointer;
typedef		std::deque<CardPointer>		CardList;

typedef		std::vector<std::string>	VectorString;

#endif // !DEFINITIONS_H
