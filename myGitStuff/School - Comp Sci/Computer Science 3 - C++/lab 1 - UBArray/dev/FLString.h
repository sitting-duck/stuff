#pragma once

#include <iostream>
#include <string>

template <class T, int size>
class FLString
{
	protected:

		T ObjectFLString[size + 1];

	public:
		/* Constructors & Destructor */
		FLString();															
		FLString(const FLString<T, size> &rhs);
		FLString(T* start);
		~FLString();							
		
		/* Accessors */
		const T* getString()const;
		void setString(T*);
		void setString(FLString<T, size> &rhs);

		/* Operators */
		FLString<T, size>& operator=(const FLString<T, size>& rhs);
		T& operator[](int index);
		const T& operator[](int index) const;
		bool operator ==(const FLString<T, size>& rhs);
		bool operator > (FLString<T, size>& s);
		bool operator < (FLString<T, size>& s);

		
		//ostream & operator << (std::ostream& out, const FLString<T, size>& S);
		//istream & operator >> (std::istream& in, FLString<T, size>& S);
		 
			/*IO Methods*/
		void Display();
		void InputString();

			/*Other Methods*/
		//friend int comparatorFLString( const void * elem1, const void * elem2 );
};

	/*Constructors*/
template <class T, int size>
FLString<T, size>::FLString()
{
	memset(ObjectFLString,  '\0' ,size);
	ObjectFLString[size] = '\0';

}

template <class T, int size>
FLString<T, size>::FLString(const FLString<T, size> &rhs)		// Copy Constructor
{
	for(int i = 0; i < size; i++)
	{
		ObjectFLString[i] = rhs.ObjectFLString[i];
	}
	ObjectFLString[size] = '\0';
}

template <class T, int size>
FLString<T, size>::FLString(T* start)
{
	memcpy (ObjectFLString, start, size);
	ObjectFLString[size + 1] = '\0';
}

template <class T, int size>
FLString<T, size>::~FLString()				// Destructor
{
}

template <class T, int size>
const T* FLString<T, size>::getString()const
{
	return &ObjectFLString[0];
}

template <class T, int size>
void FLString<T, size>::setString(T* start)
{
	memcpy (ObjectFLString, start, size);
	ObjectFLString[size] = '\0';
}

template <class T, int size>
void FLString<T, size>::setString(FLString<T, size> &rhs)
{
	for(int i = 0; i < size; i++)
	{
		ObjectFLString[i] = rhs.ObjectFLString[i];
	}
	ObjectFLString[size] = '\0';
}

	/* Operators */
template <class T, int size>
FLString<T, size>&  FLString<T, size>::operator=(const FLString<T, size> &rhs)// Assignment Operator
{
	bool selfAssignment = false;

	if (this == rhs)	// if we are trying to assign the object to iself
	{
		selfAssignment = true;
	}

	if(! selfAssignment)
	{
		for(int i=0; i< size; i++)
		{
			ObjectFLString[i] = rhs[i]; //would be safer to use memcpy...?
		}
	}
	ObjectFLString[size] = '\0';

	return *this;
}

template <class T, int size>
bool FLString<T, size>::operator==(const FLString<T, size> &rhs)
{
	int result = memcmp(ObjectFLString, rhs.ObjectFLString, size*(sizeof(T)));
	
	if(result == 0)
	{
		return true;	
	}
	else
	{
		return false;
	}
}

template <class T, int size>
T& FLString<T, size>::operator[](int index) //set
{
	return ObjectFLString[index];
}

template <class T, int size> //get
const T& FLString<T, size>::operator[](int index) const
{
	return ObjectFLString[index];
}

//template <class T, int size>
//ostream & operator << (ostream & out, const FLString<T, size> & S)
//{
//	return out << S.ObjectFLString;
//}
//
//template <class T, int size>
//istream & operator >> (istream& in, FLString<T, size>& S)  
//{
//	char c;
//	cout << "Please enter a string " << size << " digits long:  ";
//
//	for(int i = 0; i < 5; i++)
//	{
//		c = cin.get();
//		S.ObjectFLString[i] = c;
//	}
//	S.ObjectFLString[5] = '\0';
//
//	//S.ObjectFLString = ReadString();
//	return in;
//}



template <class T, int size>
void FLString<T, size>::Display()
{
	cout << ObjectFLString;
}

template <class T, int size>
void FLString<T, size>::InputString()
{
	char c;
	cout << "Please enter a string " << size << " digits long:  ";

	for(int i = 0; i < size; i++)
	{
		c = cin.get();
		S.ObjectFLString[i] = c;
	}
	S.ObjectFLString[size] = '\0';

	//S.ObjectFLString = ReadString();
	//return in;
}

//template<class T, int size>
//int comparatorFLString( const void * elem1, const void * elem2 )
//{
//		int result = 0;
//
//	if( *((FLString<T, size>*)elem1) > *((FLString<T, size>*)elem2))
//		result = 1;
//	else if ( *((FLString<T, size>*)elem1) < *((FLString<T, size>*)elem2))
//		result = -1;
//
//	return result;
//}

template<class T, int size>
bool FLString<T, size>::operator > (FLString<T, size>& s)
{
	if(strncmp(ObjectFLString, s.ObjectFLString, size) == 0)
		return false;

	if(strncmp(ObjectFLString, s.ObjectFLString, size) > 0)
		return true;

	if(strncmp(ObjectFLString, s.ObjectFLString, size) < 0)
		return false;

}

template<class T, int size>
bool FLString<T, size>::operator < (FLString<T, size>& s)
{
	if(strncmp(ObjectFLString, s.ObjectFLString, size) == 0)
		return false;

	if(strncmp(ObjectFLString, s.ObjectFLString, size) > 0)
		return false;

	if(strncmp(ObjectFLString, s.ObjectFLString, size) < 0)
		return true;
}

