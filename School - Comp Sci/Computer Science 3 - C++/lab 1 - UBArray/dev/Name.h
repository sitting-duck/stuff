#ifndef NAME_H
#define NAME_H

#include <iostream>

using namespace std;

#include "ANT_String.h"

class Name
	{
	private:
		ANT_String	First;
		ANT_String	Middle;
		ANT_String	Last;

	public:
				Name	();
				Name	(Name &);
				Name	(ANT_String & L, ANT_String & F, ANT_String & M);
				Name	(const char L [], const char F [], const char M []);
				~Name	();
		ostream&	Display	(ostream&) const;
		
		int Compare(const Name&, char whichName)const;
		int Compare(const Name& N)const;
		int Compare(Name& N)const;
		void Write(Name&);
		void Write(Name&, char);
		void Write(ANT_String&, char);
		void Write(ANT_String&, ANT_String&, ANT_String&);
		void Write( char S[], char whichName);
		void Write(const char F[], const char M[], const char L[]);
		
		ANT_String GetName();
		
		ANT_String GetFirst();
		void SetFirst(Name&);
		void SetFirst(char*);
		void SetFirst(ANT_String&);

		ANT_String GetMiddle();
		void SetMiddle(Name&);
		void SetMiddle(char*);
		void SetMiddle(ANT_String&);

		ANT_String GetLast();
		void SetLast(Name&);
		void SetLast(char*);
		void SetLast(ANT_String&);

		//operators
		Name&		operator =	( Name&);
		Name&		operator =	(const Name&);
		int operator == (const Name&)const;
		int operator != (const Name&)const;
		bool operator >  (Name&);
		bool operator <  (Name&);


		//friends
		friend extern ostream& operator << (ostream& out, const Name& N);
		friend extern istream& operator >> (istream& in, Name& N);
		friend int comparatorName( const void * elem1, const void * elem2 );
	};



#endif
