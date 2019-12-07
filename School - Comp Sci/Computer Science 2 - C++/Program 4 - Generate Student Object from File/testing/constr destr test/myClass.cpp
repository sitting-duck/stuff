#include <iostream>
#include <string.h>

#include "myClass.h"

uint myClass::Count = 0;

myClass::myClass()
{
	Count++;
}

myClass::myClass(const myClass& rhs)
{
	Count++;
}

myClass::~myClass()
{
	Count--;
}