#include "ANT_String.h"
#include <string.h>
#include <cassert>

//Implementation Section
ANT_String::ANT_String(): numChars(0)
{
	myStrPtr  = new char [numChars + 1];
	myStrPtr[0] = '\0';

}

ANT_String::ANT_String(char* Str)
{
	//this constructor will accept a string and make an object 
	//containing a copy of the string passed to it. 
	numChars = strlen(Str);
	myStrPtr = new char[numChars +1 ];
	strcpy((*this).myStrPtr, Str);
}

ANT_String::ANT_String(ANT_String& StrObj)
{
	//This constructor will accept an object and make an object
	//containing a copy of the string passed to it.
	numChars = StrObj.numChars;
	myStrPtr = new char[numChars +1];
	strcpy((*this).myStrPtr, StrObj.myStrPtr);
}

ANT_String::~ANT_String()
{
	delete[] myStrPtr;
}

ANT_String& ANT_String::Concat(const char* Str)
{
	char* tmpPtr = new char[numChars + 1];
	strcpy(tmpPtr, myStrPtr);

	delete[] myStrPtr;
	myStrPtr = new char [numChars + strlen(Str) + 1];

	strcpy(myStrPtr, tmpPtr);
	strcpy(myStrPtr + numChars, Str);
	numChars+=strlen(Str);

	return *this;
}

ANT_String& ANT_String::Concat(const ANT_String Str)
{
	char* tmpPtr = new char [strlen(myStrPtr) + 1];
	strcpy(tmpPtr, myStrPtr);

	delete [] myStrPtr;
	myStrPtr = new char [numChars + Str.numChars + 1];

	strcpy(myStrPtr, tmpPtr);
	strcpy(myStrPtr + numChars, Str.myStrPtr);
	numChars += Str.numChars;

	return *this;
}

ANT_String& ANT_String::Copy(const char* str)
{
	if(strlen(str)> numChars)
	{
	delete[] myStrPtr;
	myStrPtr = new char [strlen(str) +1];
	strcpy(myStrPtr, str);
	}
	else;
	numChars = strlen(str);
	strcpy(myStrPtr, str);
	return *this;
}

ANT_String& ANT_String::Copy(const ANT_String str)
{
	if(str.numChars> numChars)
	{
	delete[] myStrPtr;
	myStrPtr = new char [str.numChars +1];
	strcpy(myStrPtr,str.myStrPtr);
	}
	else;
	numChars = str.numChars;
	strcpy(myStrPtr, str.myStrPtr);
	return *this;
}

//operators

ANT_String& ANT_String::operator=(ANT_String& myStringObj) 
{
	return (*this).Copy(myStringObj);
}

bool ANT_String::operator==(ANT_String& myStringObj)
{
	return (*this).Compare(myStringObj);
}

bool ANT_String::operator!=(ANT_String& myStringObj)
{
	return !((*this).Compare(myStringObj));
}

ANT_String& ANT_String::operator&(const ANT_String& myStringObj)
{

	(*this).Concat(myStringObj.myStrPtr);
	return *this;
}

ANT_String& ANT_String::operator&=(const ANT_String& myStringObj)
{
	(*this).Concat(myStringObj.myStrPtr);
	return *this;
}

#pragma warning (disable:4996)

#ifndef	STRING_SIZE
#define	STRING_SIZE	5000

istream& ANT_String::READ(istream & In)
	{
	char			c;
	char *			pTemp;
	long			CharCount;
	long			MaxSize;

	delete [] myStrPtr;
	myStrPtr = new char [STRING_SIZE + 1];
	CharCount = 0;
	MaxSize = STRING_SIZE;
	while ((c = static_cast <char> (In.get ()) != '\n') && !In.eof ())
		{
		myStrPtr [CharCount++] = c;
		if (CharCount >= numChars)
				{
				pTemp = new char [(MaxSize += STRING_SIZE) + 1];
				memcpy (pTemp, myStrPtr, CharCount);
				delete [] myStrPtr;
				myStrPtr = pTemp;
				}
			else;
		}
	myStrPtr [CharCount] = '\0';
	return In;
	}

inline ostream & operator<<(ostream & out, const ANT_String & S)  
{
	//S.Display();
	return S.Display(out);
	
}


inline istream & operator>>(istream& in, ANT_String& S)  
{
	return S.READ(in);
}

#pragma warning (default:4996)

#endif