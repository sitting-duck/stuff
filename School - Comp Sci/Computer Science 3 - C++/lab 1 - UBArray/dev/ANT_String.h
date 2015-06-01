#ifndef ANT_STRING_H
#define ANT_STRING_H

#include <iostream>

using namespace std;

typedef unsigned int uint;

class ANT_String 
{
	public:  //member function prototypes go here.

		ANT_String();
		ANT_String(char*);
		ANT_String(const char*);
		ANT_String(ANT_String&);
		~ANT_String();
		
		ostream& Display(ostream & = cout) const;
		int Compare (const char*)const;
		int Compare (const ANT_String&)const;
		ANT_String& Concat(const char*);
		ANT_String& Concat(const ANT_String&);
		char* ConcatVirgin(const char*);
		char* ConcatVirgin(const ANT_String&);
		virtual ANT_String& Copy(const char*);
		virtual ANT_String& Copy(const ANT_String&);
		int Length();
		int Length()const;
		char* getString();

		//operators
		ANT_String&	operator =	( ANT_String &);
		const ANT_String&	operator =	(const ANT_String &);
		ANT_String&	operator =	(char* myCharPtr);
		bool			operator ==	( ANT_String&) ;
		bool			operator ==	( const ANT_String&)const ;
		bool			operator ==	( char [])	   ;
		bool			operator != ( ANT_String &);
		ANT_String &	operator &	(const ANT_String &);
		void	operator &=	(const ANT_String &);
		bool operator>(const ANT_String&);
		const bool operator>(const ANT_String&)const;
		bool operator>=(const ANT_String&);
		bool operator<(const ANT_String&);
		const bool operator<(const ANT_String&)const;
		bool operator<=(const ANT_String&);
		char operator [] (long i) const;
		char operator [] (long i);
		
		//friends
		friend extern ostream& operator<<(ostream&, const ANT_String&);
		friend extern istream& operator>>(istream&, ANT_String&);
		friend char * ReadString ();
		 

	protected: 
		uint numChars;	 
		char* myStrPtr;  
};

inline ostream& ANT_String::Display (ostream& out)const
{
	return out << myStrPtr;
}

inline int ANT_String::Compare (const char* Str)const
{
	return strcmp(myStrPtr, Str);
}

inline int ANT_String::Compare(const ANT_String& StrObj)const 
{
	return(strcmp(myStrPtr, StrObj.myStrPtr));
}


 inline int ANT_String::Length()
 {
	return numChars;
 }

 inline int ANT_String::Length() const
 {
	return numChars;
 }



#endif