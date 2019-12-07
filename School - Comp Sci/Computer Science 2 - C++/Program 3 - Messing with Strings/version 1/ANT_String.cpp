#include "ANT_String.h"
#include <string.h>
#include <cassert>

//Implementation Section

//constructors
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

ANT_String::ANT_String(const char* Str)
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

//funtions
ANT_String& ANT_String::Concat(const char* Str)
{
	char* tmpPtr = new char[numChars + 1];
	strcpy(tmpPtr, myStrPtr);
	myStrPtr[numChars] = '\0';//

	delete[] myStrPtr;
	myStrPtr = new char [numChars + strlen(Str) + 1];

	strcpy(myStrPtr, tmpPtr);
	strcpy(myStrPtr + numChars, Str);
	numChars+=strlen(Str);

	return *this;
}

ANT_String& ANT_String::Concat(const ANT_String& Str)
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

char* ANT_String::ConcatVirgin(const char* Str)
{
	char* tmpPtr = new char[numChars + 1];
	strcpy(tmpPtr, myStrPtr);
	strcpy(myStrPtr + numChars, Str);
	
	return tmpPtr;
}

char* ANT_String::ConcatVirgin(const ANT_String& Str)
{
	char* tmpPtr = new char[strlen(myStrPtr) + 1];
	strcpy(tmpPtr, myStrPtr);
	strcpy(myStrPtr+numChars, Str.myStrPtr);
	return tmpPtr;
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

ANT_String& ANT_String::Copy(const ANT_String& str)
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

char* ANT_String::getString()
{
	return myStrPtr;
}

//operators

ANT_String& ANT_String::operator=(ANT_String& myStringObj) 
{
	return (*this).Copy(myStringObj);
}

ANT_String& ANT_String::operator=(char* myCharPtr)
{
	Copy(myCharPtr);
	return (*this);
}

bool ANT_String::operator==(ANT_String& myStringObj)
{
	return ((*this).Compare(myStringObj) == 0);
}

bool ANT_String::operator==(const ANT_String& myStringObj)const
{
	return (Compare(myStringObj) == 0);
}

bool ANT_String::operator!=(ANT_String& myStringObj)
{
	return !((*this).Compare(myStringObj));
}

ANT_String& ANT_String::operator&(const ANT_String& myStringObj)
{

	(*this).ConcatVirgin(myStringObj.myStrPtr);
	return *this;
}

void ANT_String::operator&=(const ANT_String& myStringObj)
{
	(*this).Concat(myStringObj.myStrPtr);
}

bool ANT_String::operator>(const ANT_String& myStringObj)
{
	return((*this).Compare(myStringObj)<0);
}

bool ANT_String::operator>=(const ANT_String& myStringObj)
{
	return((*this).Compare(myStringObj)<=0);
}

bool ANT_String::operator<(const ANT_String& myStringObj)
{
	return((*this).Compare(myStringObj)>0);
}

bool ANT_String::operator<=(const ANT_String& myStringObj)
{
	return((*this).Compare(myStringObj)>=0);
}

inline ostream & operator<<(ostream & out, const ANT_String & S)  
{
	return S.Display(out);
	
}

inline istream & operator>>(istream& in, ANT_String& S)  
{
	S.myStrPtr = ReadString();
	return in;
}


char ANT_String::operator [] (long i)
		{
		return myStrPtr[i];
		}

char ANT_String::operator [] (long i) const
		{
		return myStrPtr[i];
		}
