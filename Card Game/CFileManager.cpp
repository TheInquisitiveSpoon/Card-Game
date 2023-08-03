//	CFileManager.cpp - Niall Starkey

//
//	Implementation for the file manager class
//

//  HEADERS:  //
#include "pch.h"
#include "CFileManager.h"

//  FUNCTIONS:  //
//  Reads the file passed and returns a vector of strings containing the file text.
VectorString CFileManager::GetFileText(std::string fileLocation)
{
	VectorString	fileText;
	std::string		line = "";
	std::ifstream	infile;

	infile.open(fileLocation);	// Opens the file specified

	//  Loops until the end of the file adding each line to the container.
	while (!infile.eof())
	{
		getline(infile, line);	// Gets line text
		fileText.push_back(line);	// Stores line text in container
	}

	infile.close();	// Closes file to prevent errors
	return	fileText;	// Return the file text
}

//  Removes the unnecessary text from the file name leaving just the name of the
//  player.
std::string CFileManager::GetFileName(std::string text)
{
	std::string		name = "";
	const char		kSTART_CHAR = '/';
	const char		kEND_CHAR = '.';

	//  Loops through the length of the text.
	for (int i = 0; i < text.length(); i++)
	{
		//  Checks whether the current char is the same as the start char.
		if (text[i] == kSTART_CHAR)
		{
			//  Loops through the rest of the text.
			for (int j = (i + 1); j < text.length(); j++)
			{
				//  Checks whether the current char is the same as the end char.
				if (text[j] == kEND_CHAR)
				{
					return	name;	// Returns the file name
				}
				else
				{
					name += text[j];	// Adds the current char to the file name
				}
			}
		}
	}
}

//  Splits a string using a given character as the delimiter.
VectorString CFileManager::SplitString(std::string text, char delimiter)
{
	VectorString		container;
	std::stringstream	stream(text);
	std::string			token = "";

	//  Loops every time the delimiter is found in the text.
	while (std::getline(stream, token, delimiter))
	{
		container.push_back(token);	// Stores the read text in the container
	}

	return	container;	// Returns a vector of all the strings from the text
}

//  CONSTRUCTORS:  //
CFileManager::CFileManager()
{
}

//  DESTRUCTORS:  //
CFileManager::~CFileManager()
{
}
