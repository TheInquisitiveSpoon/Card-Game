//  ICard.h - Niall Starkey

//
//  Interface class for all card classes
//

#ifndef ICARD_H
#define ICARD_H

//  HEADERS:  //
#include <string>
#include <vector>
#include <deque>
#include <memory>

//  CLASS:  //
class ICard
{
public:
	//  MEMBER VARIABLES:  //
	std::string		mName = "";
	int				mType = 0;

	//  FUNCTIONS:  //
	virtual void LoadStats
	(
		std::vector<std::string>	stats

	) = 0;

	//  CONSTRUCTORS:  //
	//  No construction needed.

	//  DECONSTRUCTORS:  //
	virtual ~ICard() {}
};

#endif	// I_CARD