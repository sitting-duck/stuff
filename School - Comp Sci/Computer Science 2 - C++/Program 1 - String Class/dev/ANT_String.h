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
		ANT_String(ANT_String&);
		~ANT_String();
		
		//void Display(ANT_String);
		ostream& Display(ostream & = cout) const;
		int Compare (const char*)const;
		int Compare (const ANT_String)const;
		ANT_String& Concat(const char*);
		ANT_String& Concat(const ANT_String);
		ANT_String& Copy(const char*);
		ANT_String& Copy(const ANT_String);
		int Length();
	
		istream& READ(istream& In);

		//operators
		ANT_String &	operator =	( ANT_String &);
		bool			operator ==	( ANT_String&) ;
		bool			operator ==	( char [])	   ;
		bool			operator != ( ANT_String &);
		ANT_String &	operator &	(const ANT_String &);
		ANT_String &	operator &=	(const ANT_String &);
		
		//friends
		friend extern ostream& operator<<(ostream&, const ANT_String&);
		friend extern istream& operator>>(istream&, ANT_String&);
		 

	private: 
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

inline int ANT_String::Compare(const ANT_String StrObj)const 
{
	return strcmp(myStrPtr, StrObj.myStrPtr);
}

 inline int ANT_String::Length()
 {
	return strlen(myStrPtr);
 }



#endif