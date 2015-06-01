#include "ANT_String.h"
#include "Address.h"
#include "DString.h"

//constructors
Address::Address()\
	: Number("XXX"), Street("XXX"), City("XXX"), State("XXX"), Zip("55555")
{

}

Address::Address(Address & A)\
	:Number(A.Number), Street(A.Street), City(A.City), State(A.State), Zip(A.Zip)
{

}

Address::Address(ANT_String Number, ANT_String Street, ANT_String City, ANT_String State, DString<char, 5> Zip)\
	:Number(Number), Street(Street), City(City), State(State), Zip(Zip)
{

}

Address::Address(char Number[] , char Street[] , char City[], char State[], char Zip[])\
	:Number(Number), Street(Street), City(City), State(State), Zip(Zip)
{

}

Address::~Address()
{

}

ostream& Address::Display(ostream& out) const
{
	out << Number << endl;
	out << Street << endl;
	out << City   << endl;
	out << State  << endl;
	out << Zip.getString() << endl;
	return out;

}

int Address::Compare(Address& A)
{
	if(Number == A.Number &&
	   Street == A.Street &&
	   City   == A.City   &&
	   State  == A.State  &&
	   Zip    == A.Zip      )
	{
		return 1;
	}
	return 0;

}

ANT_String& Address::GetAddress()
{
	ANT_String myTempAddress;
	myTempAddress = Number.ConcatVirgin(" ");
	myTempAddress = myTempAddress.ConcatVirgin(Street);
	myTempAddress = myTempAddress.ConcatVirgin(" ");
	myTempAddress = myTempAddress.ConcatVirgin(City);
	myTempAddress = myTempAddress.ConcatVirgin(" ");
	myTempAddress = myTempAddress.ConcatVirgin(State);
	myTempAddress = myTempAddress.ConcatVirgin(" ");
	myTempAddress = myTempAddress.ConcatVirgin(Zip.getString());

	return myTempAddress;
}

ANT_String& Address::GetNumber()
{
	return Number;
}

void Address::SetNumber(Address& A)
{
	Number = A.Number;
}

void Address::SetNumber(ANT_String& A)
{
	Number = A;
}

void Address::SetNumber(char* A)
{
	Number = A;
}

ANT_String& Address::GetStreet()
{
	return Street;
}

void Address::SetStreet(Address& A)
{
	Street = A.Street;
}

void Address::SetStreet(ANT_String& A)
{
	Street = A;
}

void Address::SetStreet(char* A)
{
	Street = A;
}

ANT_String& Address::GetCity()
{
	return City;
}

void Address::SetCity(Address& A)
{
	City = A.City;
}

void Address::SetCity(ANT_String& A)
{
	City = A;
}

void Address::SetCity(char* A)
{
	City = A;
}

ANT_String& Address::GetState()
{
	return State;
}

void Address::SetState(Address& A)
{
	State = A.State;
}

void Address::SetState(ANT_String& A)
{
	State = A;
}

void Address::SetState(char* A)
{
	State = A;
}


DString<char, 5>& Address::GetZip()
{
	return Zip;
}

void Address::SetZip(DString<char, 5>& Z)
{
	Zip = Z;
}

void Address::SetZip(ANT_String& A)
{
	Zip.setString(A.getString());
}

void Address::SetZip(char* A)
{
	Zip.setString(A);
}

//operators!!!

Address& Address::operator =	( Address & A)
{
	Number = A.Number;
	Street = A.Street;
	City   = A.City;
	State  = A.State;
	Zip    = A.Zip;
	return (*this);
}

Address& Address::operator =	(const Address & A)
{
	Number = A.Number;
	Street = A.Street;
	City   = A.City;
	State  = A.State;
	Zip    = A.Zip;
	return (*this);
}

bool Address::operator ==	( Address& A )
{
	return Compare(A);
}

bool Address::operator != ( Address & A)
{
	return !Compare(A);
}

ostream& operator << (ostream& out, const Address& A)
{
	return A.Display(out);
}

istream& operator >> (istream& in, Address& A)
{
	cout << "Number: ";
	A.SetNumber	 ( ReadString() );
	cout << "Street: ";
	A.SetStreet	 ( ReadString() );
	cout << "City: ";
	A.SetCity	 ( ReadString() );
	cout << "State: ";
	A.SetState	 ( ReadString() );
	cout << "Zip: ";
	A.SetZip	 ( ReadString() );
	return in;
}
