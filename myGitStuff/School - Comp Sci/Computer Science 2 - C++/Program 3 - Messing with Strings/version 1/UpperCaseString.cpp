#include "UppercaseString.h"
#include "ANT_String.h"
#include <cassert>
#include <string.h>
#include <cctype>

UpperCaseString::UpperCaseString()
{
	numChars = 0;
	myStrPtr  = new char [numChars + 1];
	myStrPtr[0] = '\0';
}

UpperCaseString::UpperCaseString(char* str)
{
	Copy((const char *) str);
	ToUpperCase();
}

UpperCaseString::UpperCaseString(const char* str)
{
	Copy((const char *) str);
	ToUpperCase();
}

UpperCaseString::UpperCaseString(ANT_String& ANTStr) 
{
	Copy(ANTStr);
	ToUpperCase();
}

UpperCaseString::UpperCaseString(UpperCaseString& uStr)
{
	Copy(uStr);
	ToUpperCase();
}


//FUNCTIONS
void UpperCaseString::ToUpperCase()
{
	for (int i = 0; i < Length(); i++)
	{
		myStrPtr[i] = toupper(myStrPtr[i]);
	}
}

UpperCaseString& UpperCaseString::Copy(const char* str)
{
	ANT_String::Copy(str);
	ToUpperCase();
	return * this;
}

UpperCaseString& UpperCaseString::Copy(const UpperCaseString & str)
{
	ANT_String::Copy(str);
	ToUpperCase();
	return * this;
}

UpperCaseString&  UpperCaseString::Copy(const ANT_String & str)
{
	ANT_String::Copy(str);
	ToUpperCase();
	return * this;
}

UpperCaseString& UpperCaseString::operator=(const char* str)
{
	return Copy(str);
}

UpperCaseString& UpperCaseString::operator=(const UpperCaseString & str)
{
	return Copy(str);
}

UpperCaseString & UpperCaseString::operator &(const UpperCaseString & myStringObj)
{
	Concat (myStringObj);
	return * this;
}

ostream & operator<<(ostream & out, const UpperCaseString & S)  
{
	return S.Display(out);
	
}

istream & operator>>(istream& in, UpperCaseString& S)  
{
	S.Copy(ReadString());
	return in;
}

/*bool UpperCaseString::operator==(UpperCaseString& myStringObj)
{
	return ((*this).Compare(myStringObj) == 0);
}

bool UpperCaseString::operator==(const UpperCaseString& myStringObj)const
{
	return (Compare(myStringObj) == 0);
}

bool UpperCaseString::operator!=(UpperCaseString& myStringObj)
{
	return !((*this).Compare(myStringObj));
}



void UpperCaseString::operator&=(const UpperCaseString& myStringObj)
{
	(*this).Concat(myStringObj.myStrPtr);
}

bool UpperCaseString::operator>(const UpperCaseString& myStringObj)
{
	return((*this).Compare(myStringObj)<0);
}

bool UpperCaseString::operator>=(const UpperCaseString& myStringObj)
{
	return((*this).Compare(myStringObj)<=0);
}

bool UpperCaseString::operator<(const UpperCaseString& myStringObj)
{
	return((*this).Compare(myStringObj)>0);
}

bool UpperCaseString::operator<=(const UpperCaseString& myStringObj)
{
	return((*this).Compare(myStringObj)>=0);
}

inline ostream & operator<<(ostream & out, const UpperCaseString & S)  
{
	return S.Display(out);
	
}

inline istream & operator>>(istream& in, UpperCaseString& S)  
{
	S.myStrPtr = ReadString();
	return in;
}


char UpperCaseString::operator [] (long i)
		{
		return myStrPtr[i];
		}

char UpperCaseString::operator [] (long i) const
		{
		return myStrPtr[i];
		}*/




