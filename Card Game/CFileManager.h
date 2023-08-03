//  CFileManager.h - Niall Starkey

//
//	Declaration of file manager class
//

#ifndef CFILE_MANAGER_H
#define	CFILE_MANAGER_H

//  HEADERS:  //
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include "Definitions.h"

//  CLASS:  //
class CFileManager
{
public:
	//  FUNCTIONS:  //
	VectorString GetFileText
	(
		std::string		fileLocation
	);

	std::string GetFileName
	(
		std::string		text
	);

	VectorString SplitString
	(
		std::string		text, 
		char			delimiter
	);

	//  CONSTRUCTORS:  //
	CFileManager();

	//  DESTRUCTORS:  //
	~CFileManager();
};

#endif // CFILE_MANAGER_H