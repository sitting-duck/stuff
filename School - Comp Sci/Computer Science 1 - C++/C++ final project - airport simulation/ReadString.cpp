#include <iostream>

using namespace std;

#include <memory.h>

#include "ReadString.h"

void SkipSpaces ()
	{
	char	c;

	while ((c = cin.get ()) == ' ');
	cin.unget ();
	}

char * ReadString ()
	{
	const	int	StartSize		(50);
			int	CurrentNumChars	(0);
			int	CurrentSize		(StartSize);
			char *	pStr;
			char	c;

	pStr = new char [StartSize + 1];
	//SkipSpaces ();
	while ((c = getchar())) != '/n')
		{
		pStr [CurrentNumChars] = c;
		CurrentNumChars++;
		if (CurrentNumChars >= CurrentSize)
				{
				char * pTemp;

				CurrentSize += StartSize;
				pTemp = new char [CurrentSize + 1];
				memcpy (pTemp, pStr, CurrentNumChars);
				delete [] pStr;
				pStr = pTemp;
				}
			else;
		}
	pStr [CurrentNumChars] = '\0';
	return pStr;
	}
