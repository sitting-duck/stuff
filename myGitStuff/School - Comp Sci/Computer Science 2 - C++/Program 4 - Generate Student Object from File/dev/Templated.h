#ifndef TEMPLATED_H
#define TEMPLATED_H

#include "stdafx.h"

#define ARRAY_SIZE 25

template <class T>
class Array
{
	private:
		int numOfElements;
		int size;

	public:
		/* Constructors & Destructor */
		Array(int sizeIn = ARRAY_SIZE);	// If no size is specified, create an array of size ARRAY_SIZE - 
																		
		Array(const Array &rightHandSide);	// Copy Constructor
		~Array();							// Must delete the array of objects in the destructor

		/* Accessors */
		int getSize() const;
		int getNumOfElements() const;
		void setIsupport(void* funcPtr);

		/* Operators */
		Array& operator=(const Array&);
		T& operator[](int index);
		const T& operator[](int index) const;
		Array& operator==(const Array&);

		/* Other Methods */
		void add(T &myObj);
		void sort(bool caseInsensitive = false);
		int Array<T>::compare(const void* obj1, const void* obj2);
		int Array<T>::iCompare(const void* obj1, const void* obj2);
		
		T *ptrObjectArray;
};


template <class T>
int Array<T>::compare(const void* obj1, const void* obj2)
{
	int result = 0;

	if( *((T*)obj1) > *((T*)obj2))
		result = 1;
	else if ( *((T*)obj1) < *((T*)obj2))
		result = -1;

	return result;
}

template <class T>
int Array<T>::iCompare(const void* obj1, const void* obj2)
{
	return *((T*)obj1) == *((T*obj2));
}

template <class T>
void Array<T>::sort(bool caseInsensitive)
{
	if (caseInsensitive)
	{
		qsort(this->ptrObjectArray, numOfElements, sizeof(T), T::iCompare);
	}
	else
	{
		qsort(this->ptrObjectArray, numOfElements, sizeof(T), T::compare);
	}
}


template <class T>
void Array<T>::add(T &myObj)
{
	if (this->numOfElements < size)
	{
		ptrObjectArray[numOfElements] = myObj;
		numOfElements++;
	}
	else
	{
		cout << "Cannot add any more objects to this array" << endl;
	}
}

template <class T>
int Array<T>::getSize() const
{
	return size;
}

template <class T>
int Array<T>::getNumOfElements() const
{
	return numOfElements;
}

template <class T>
Array<T>::Array(int sizeIn)		// Default Constructor
{
	size = sizeIn;									// this is the size of the array, i.e. the number of elements it can hold
	ptrObjectArray = new T[size];					// this will invoke the constructor of the Object being created
	numOfElements = 0;
}

template <class T>
void Array<T>::setIsupport(void* funcPtr)
{
	this->iSupportFunction = funcPtr;
}

template <class T>
Array<T>::Array(const Array &rightHandSide)		// Copy Constructor
{
	numOfElements = rightHandSide.numOfElements;
	size = rightHandSide.getSize();
	ptrObjectArray = new T[size];
	for(int i=0; i<size; i++)
	{
		ptrObjectArray[i] = rightHandSide[i];
	}
}

template <class T>
Array<T>::~Array()				// Destructor
{
	delete name;
	delete [] ptrObjectArray;	// Since it is an array of objects
}

/* Operators */
template <class T>
Array<T>&  Array<T>::operator=(const Array &rightHandSide)		// Assignment Operator
{
	bool selfAssignment = false;

	if (this == rightHandSide)	// we are trying to assign the object to iself
	{
		selfAssignment = true;
	}

	if(! selfAssignment)
	{
		delete ptrObjectArray;
		size = rightHandSide.getSize();
		ptrObjectArray = new T[size];

		for(int i=0; i<size; i++)
		{
			ptrObjectArray[i] = rightHandSide[i];
		}
	}

	return *this;
}

template <class T>
Array<T>& Array<T>::operator==(const Array &rightHandSide)
{
	cout << "Need to write Method for Array Template, operator== in Templated.h" << endl;
}

template <class T>
T& Array<T>::operator[](int index)
{
	return ptrObjectArray[index];
}

template <class T>
const T& Array<T>::operator[](int index) const
{
	return ptrObjectArray[index];
}

#endif