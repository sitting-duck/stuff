#include <iostream> 
#include <cassert>
#include <cctype>

#include "ANT_String.h"
#include "ReadString.h"
#include "DigitString.h"

DigitString::DigitString()
{
	numChars = 0;
	myStrPtr  = new char [numChars + 1];
	myStrPtr[0] = '\0';
}

DigitString::DigitString(char* str)
{
	Copy((const char *) str);
	assert(CheckDigits());
}

DigitString::DigitString(const char* str)
{
	Copy((const char *) str);
	assert(CheckDigits());
}

DigitString::DigitString(ANT_String& ANTStr) 
{
	//Copy(ANTStr);
	numChars = ANTStr.Length();
	myStrPtr = new char[numChars +1];
	strcpy((*this).myStrPtr, ANTStr.getString() );
	assert(CheckDigits());
}

DigitString::DigitString(DigitString& dStr)
{
	Copy(dStr);
	assert(CheckDigits());
}

DigitString& DigitString::Copy(const char* str )
{
	ANT_String::Copy(str);
	//CheckDigits();
	return * this;
}

DigitString& DigitString::Copy(const DigitString& str)
{
	ANT_String::Copy(str);
	//CheckDigits();
	return * this;
}

bool DigitString::CheckDigits() throw(char)   
{
	char NON_DIGIT_EXCEPTION;
	static bool isDigits;
	isDigits = true;

	try
	{
		for (int i = 0; i < Length(); i++)
		{
			if( isalpha(myStrPtr[i]) || ispunct(myStrPtr[i]))
			{
				NON_DIGIT_EXCEPTION = myStrPtr[i];
				throw NON_DIGIT_EXCEPTION;
			}
		}
	}
	catch (char c)
	{
		cout << "Character: " << c << " is not a number. Please enter a completely numeric string." << endl;
		isDigits = false;
	}

	return isDigits;
}

DigitString& DigitString::operator=(const char* str)
{
	return Copy(str);
}

DigitString& DigitString::operator=(const DigitString& str)
{
	return Copy(str);
}

DigitString & DigitString::operator &(const DigitString & myStringObj)
{
	Concat (myStringObj);
	return * this;
}

ostream& operator<<(ostream& out, const DigitString& S)
{
	return S.Display(out);
}

istream& operator>>(istream& in, DigitString& S)
{
	
	do
	{
		S.Copy(ReadString());
		
	}
	while( !(S.CheckDigits()) );
	return in;
}

/*bool DigitString::operator==(DigitString& myStringObj)
{
	return ((*this).Compare(myStringObj) == 0);
}

bool DigitString::operator==(const DigitString& myStringObj)const
{
	return (Compare(myStringObj) == 0);
}

bool DigitString::operator!=(DigitString& myStringObj)
{
	return !((*this).Compare(myStringObj));
}



void DigitString::operator&=(const DigitString& myStringObj)
{
	(*this).Concat(myStringObj.myStrPtr);
}

bool DigitString::operator>(const DigitString& myStringObj)
{
	return((*this).Compare(myStringObj)<0);
}

bool DigitString::operator>=(const DigitString& myStringObj)
{
	return((*this).Compare(myStringObj)<=0);
}

bool DigitString::operator<(const DigitString& myStringObj)
{
	return((*this).Compare(myStringObj)>0);
}

bool DigitString::operator<=(const DigitString& myStringObj)
{
	return((*this).Compare(myStringObj)>=0);
}

inline ostream & operator<<(ostream & out, const DigitString & S)  
{
	return S.Display(out);
	
}

inline istream & operator>>(istream& in, DigitString& S)  
{
	S.myStrPtr = ReadString();
	return in;
}


char DigitString::operator [] (long i)
		{
		return myStrPtr[i];
		}

char DigitString::operator [] (long i) const
		{
		return myStrPtr[i];
		}*/