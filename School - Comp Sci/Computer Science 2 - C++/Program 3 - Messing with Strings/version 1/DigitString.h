#ifndef DIGIT_STRING_H
#define DIGIT_STRING_H

#include "ANT_String.h"
#include "ReadString.h"

#include <iostream>

using namespace std;

class DigitString : public ANT_String
{
public:
	DigitString();
	explicit DigitString(char*);
	explicit DigitString(const char*);
	explicit DigitString(ANT_String&); 
	explicit DigitString(DigitString&);

	istream& READ(istream& In);
	DigitString& Copy(const char*);
	DigitString& Copy(const DigitString&);
	bool CheckDigits() throw(char);
	DigitString& operator=(const char*);
	DigitString& operator=(const DigitString &);
	DigitString& operator &(const DigitString &);

	friend extern ostream& operator<<(ostream&, const DigitString&);
	friend extern istream& operator>>(istream&, DigitString&);
	friend char * ReadString ();


};


#endif