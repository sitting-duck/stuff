#pragma once

#include <string>
#include <iostream>
#include "FLString.h"

using namespace std;

template <class T = char, int size = 1>
class DString : public FLString<T, size>
{

	public:
		/* Constructors & Destructor */
		DString();															
		DString(T* start);
		~DString();							

		/* Operators */
		DString<T, size>& operator=(const DString<T, size>& rhs);
		
		//greater than less than derp derp

			/*Other*/
		
		//template<class T, int size> 
		friend int comparatorDString( const void * elem1, const void * elem2 );
		
};

/*Constructors*/
template <class T, int size>
DString<T, size>::DString()
{
	memset(ObjectFLString,  '0' ,size);
	ObjectFLString[size] = '\0';
}

template <class T, int size>
DString<T, size>::DString(T* start)
{
	memcpy (ObjectFLString, start, size + 1);
	ObjectFLString[size] = '\0';
}

template <class T, int size>
DString<T, size>::~DString()				// Destructor
{
}
	/* Operators */
template <class T, int size>
DString<T, size>&  DString<T, size>::operator=(const DString<T, size> &rhs)// Assignment Operator
{
//	if(!(this == rhs))
//	{
		for(int i=0; i < size; i++)
		{
			ObjectFLString[i] = rhs[i];
		}
//	}
	ObjectFLString[size] = '\0';

	return *this;
}

//template<class T, int size>
inline int comparatorDString( const void * elem1, const void * elem2 )
{
	//	int result = 0;

	//if( *((DString<T, size>*)elem1) > *((DString<T, size>*)elem2))
	//	result = 1;
	//else if ( *((DString<T, size>*)elem1) < *((DString<T, size>*)elem2))
	//	result = -1;

	//return result;

	int result = 0;
	if( *((DString<char, 9>*)elem1) < *((DString<char, 9>*)elem2))
		result = 1;
	//else if ( *((DString<char, 9>*)elem1) > *((DString<char, 9>*)elem2))
	else	
	result = -1;

	return result;

}