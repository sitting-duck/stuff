#ifndef UPPER_CASE_STRING_H
#define UPPER_CASE_STRING_H

#include <cctype>
#include <iostream>

#include "ANT_String.h"

using namespace std;

class UpperCaseString : public ANT_String
{
public:

	//constructors
	UpperCaseString();
	explicit UpperCaseString(char*);
	explicit UpperCaseString(const char*);
	explicit UpperCaseString(ANT_String&); 
	explicit UpperCaseString(UpperCaseString&);

	//functions
	UpperCaseString& Copy(const char*);
	UpperCaseString& Copy(const UpperCaseString &);
	UpperCaseString& Copy(const ANT_String &);
	
	void ToUpperCase();

	//operators
	UpperCaseString& operator=(const char*);
	UpperCaseString& operator=(const UpperCaseString &);
	UpperCaseString& operator &(const UpperCaseString &);
	friend ostream & operator<<(ostream & out, const UpperCaseString & S);
	friend istream & operator>>(istream& in, UpperCaseString& S);
	

};

#endif 