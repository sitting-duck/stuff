#ifndef MY_CLASS_H
#define MY_CLASS_H

#include "master.h"

class myClass
{
public: 
	myClass();
	myClass(const myClass&);
	~myClass();

	static uint getCount(){return Count;}

private:
	
	static uint Count;
	
};





#endif