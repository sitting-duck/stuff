#include "Name.h"
#include "ANT_String.h"
#include "ReadString.h"

Name::Name ()
{
}

Name::Name (Name & N): First (N.First), Middle (N.Middle), Last (N.Last)	
{
}

Name::Name (ANT_String & F, ANT_String & M, ANT_String & L): First (F), Middle (M), Last (L)
{
}
Name::Name (const char F [], const char M [], const char L []): First (F), Middle (M), Last (L)
{
}

Name::~Name ()
{
}

ostream& Name::Display (ostream& out) const
{
	First.Display (out);
	cout << " ";
	Middle.Display (out);
	cout << " ";
	Last.Display (out);
	cout << endl;

	return out;
}

int Name::Compare(const Name& N, char whichName) const
{

	switch(whichName)
	{
	case 'f':
	case 'F':
		return First.Compare(N.First);
	case 'm':
	case 'M':
		return Middle.Compare(N.Middle);
	case 'l':
	case 'L':
		return Last.Compare(N.Last);
	}
	
}

int Name::Compare(const Name& N) const
{
	if((First  == N.First)  &&
	   (Middle == N.Middle) &&
	   (Last   == N.Last))
	   return 1;
	else return 0;
}

int Name::Compare( Name& N) const
{
	if((First  == N.First)  &&
	   (Middle == N.Middle) &&
	   (Last   == N.Last))
	   return 1;
	else return 0;
}

int comparatorName( const void * elem1, const void * elem2 )
{
	//	int result = 0;

	//if( *((Name*)elem1) > *((Name*)elem2))
	//	result = -1;
	//else if ( *((Name*)elem1) < *((Name*)elem2))
	//	result = 1;

	//return result;

			int result = 0;

	if( *((Name*)elem1) < *((Name*)elem2))
		result = -1;
	else if ( *((Name*)elem1) > *((Name*)elem2))
		result = 1;

	return result;
}

void Name::Write(Name& N)
{
	((*this).First).Copy(N.First);
	((*this).Middle).Copy(N.Middle);
	((*this).Last).Copy(N.Last);

}

void Name::Write(Name& N, char whichName)
{
	switch(whichName)
	{
		case 'f':
		case 'F':
			((*this).First).Copy(N.First);
		case 'm':
		case 'M':
			((*this).Middle).Copy(N.Middle);
		case 'l':
		case 'L':
			((*this).Last).Copy(N.Last);
	}

}

//void Name::Write(const char* myName, char whichName)
//{
//	switch(whichName)
//	{
//		case 'f':
//		case 'F':
//			((*this).First).Copy(myName);
//		case 'm':
//		case 'M':
//			((*this).Middle).Copy(myName);
//		case 'l':
//		case 'L':
//			((*this).Last).Copy(myName);
//	}
//}


void Name::Write( ANT_String& N, char whichName)
{
	switch(whichName)
	{
		case 'f':
		case 'F':
			((*this).First).Copy(N);
		case 'm':
		case 'M':
			((*this).Middle).Copy(N);
		case 'l':
		case 'L':
			((*this).Last).Copy(N);
	}

}

void Name::Write( ANT_String& F,  ANT_String& M,  ANT_String& L)
{
	((*this).First).Copy(F);
	((*this).Middle).Copy(M);
	((*this).Last).Copy(L);
}

void Name::Write( char S[], char whichName)
{
	switch(whichName)
	{
		case 'f':
		case 'F':
			((*this).First).Copy(S);
		case 'm':
		case 'M':
			((*this).Middle).Copy(S);
		case 'l':
		case 'L':
			((*this).Last).Copy(S);
	}
}

void Name::Write(const char F[], const char M[], const char L[])
{
	((*this).First).Copy(F);
	((*this).Middle).Copy(M);
	((*this).Last).Copy(L);
}

//Get and set methods for first middle and last names

ANT_String Name::GetName()
{
	ANT_String tempFullName_ANT;

	tempFullName_ANT = this->First.ConcatVirgin(" ");
	tempFullName_ANT = tempFullName_ANT.ConcatVirgin(this->Middle);
	tempFullName_ANT = tempFullName_ANT.ConcatVirgin(" ");
	tempFullName_ANT = tempFullName_ANT.ConcatVirgin(this->Last);

	return tempFullName_ANT; 
	
}

ANT_String Name::GetFirst()
{
	return First;
}

void Name::SetFirst(Name& N)
{
	First = N.First;
}

void Name::SetFirst(char* F)
{
	First.Copy(F);
}

void Name::SetFirst(ANT_String& S)
{
	First = S;
}

ANT_String Name::GetMiddle()
{
	return Middle;
}

void Name::SetMiddle(Name& N)
{
	Middle = N.Middle;
}

void Name::SetMiddle(char* M)
{
	Middle.Copy(M);
}

void Name::SetMiddle(ANT_String& S)
{
	Middle = S;
}

ANT_String Name::GetLast()
{
	return Last;
}

void Name::SetLast(Name& N)
{
	Last = N.Last;
}

void Name::SetLast(char* L)
{
	Last.Copy(L);
}

void Name::SetLast(ANT_String& S)
{
	Last = S;
}

//operators

ostream& operator << (ostream& out, const Name& N)
{
	return N.Display(out);
}

istream& operator >> (istream& in, Name& N)
{
	cout << "First Name: ";
	N.SetFirst ( ReadString() );
	cout << "Middle Name: ";
	N.SetMiddle( ReadString() );
	cout << "Last Name: ";
	N.SetLast  ( ReadString() );
	return in;
}

int Name::operator == (const Name& myName )const
{
	return Compare(myName);	
}

Name& Name::operator =	( Name & A)
{
	First = A.First;
	Middle = A.Middle;
	Last   = A.Last;
	return (*this);
}

Name& Name::operator =	(const Name & A)
{
	First = A.First;
	Middle = A.Middle;
	Last   = A.Last;
	return (*this);
}

int Name::operator != (const Name& myName )const
{
	return !(Compare(myName));	
}

bool Name::operator >  (Name& n)
{
	//if( First > n.First)
	//	return true;
	//else if(Middle > n.Middle)
	//	return true;
	//else if(Last > n.Last)
	//	return true;
	//else
	//	return false;

	if(Last > n.Last)
		return true;
	else if(Last == n.Last)
	{
		if(Middle > n.Middle)
			return true;
		else if(Middle == n.Middle)
		{
			if(First > n.First)
				return true;
			else
				return false;
		}
		
	}
}


bool Name::operator <  (Name& n)
{
	//if( First < n.First)
	//	return true;
	//else if(Middle < n.Middle)
	//	return true;
	//else if(Last < n.Last)
	//	return true;
	//else
	//	return false;

		if(Last < n.Last)
		return true;
	else if(Last == n.Last)
	{
		if(Middle < n.Middle)
			return true;
		else if(Middle == n.Middle)
		{
			if(First < n.First)
				return true;
			else
				return false;
		}
		
	}
}


