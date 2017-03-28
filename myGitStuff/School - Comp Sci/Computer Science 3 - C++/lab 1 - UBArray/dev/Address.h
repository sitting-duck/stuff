#ifndef ADDRESS_H
#define ADDRESS_H

#include <iostream>

using namespace std;

#include "ANT_String.h"
#include "DString.h"

class Address 
{
private:
	ANT_String Number;
	ANT_String Street;
	ANT_String City;
	ANT_String State;
	DString<char, 5> Zip;

public:
	Address();
	Address(Address &);
	Address(ANT_String, ANT_String, ANT_String, ANT_String, DString<char, 5>); 
	Address(char[], char [], char [], char[], char[]);	
	~Address();
		
	
	ostream& Display(ostream&) const;
	int Compare(Address&);

		/*Getters and Setters*/
	ANT_String& GetAddress();
	//void SetAddress(Address& a);
	//void SetAddress(char*); //will take and parse a string to set address

	ANT_String& GetNumber();
	void SetNumber(Address&);
	void SetNumber(ANT_String&);
	void SetNumber(char*);

	ANT_String& GetStreet();
	void SetStreet(Address&);
	void SetStreet(ANT_String&);
	void SetStreet(char*);

	ANT_String& GetCity();
	void SetCity(Address&);
	void SetCity(ANT_String&);
	void SetCity(char*);

	ANT_String& GetState();
	void SetState(Address&);
	void SetState(ANT_String&);
	void SetState(char*);

	DString<char, 5>& GetZip();
	void SetZip(DString<char, 5>&);
	void SetZip(ANT_String&);
	void SetZip(char*);

	//operators
	Address&		operator =	( Address &);
	Address&		operator =	(const Address &);
	bool			operator ==	( Address& );
	bool			operator != ( Address &);
		
	//friends
	friend extern ostream& operator << (ostream& out, const Address& A);
	friend extern istream& operator >> (istream& in, Address& A);
};

#endif