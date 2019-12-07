#include <iostream>

using namespace std;

#include "FixedArray.h"
#include "Array.h"

#define XXX FixedArray<int, -2, 2>

void Func (const FixedArray <int, -5, 5> &);

void main ()
	{
	FixedArray <int, -5, 5>		A1;
	FixedArray <int, -5, 5>		A2;
	FixedArray <int, 0, 10>		A3;
	FixedArray <>				A4;
	FixedArray <int>			A5;

//	FixedArray <FixedArray <int ,-2, 2>, 5, 8>	Array2D;
	FixedArray <XXX, 5, 8>	Array2D;

	A1 = A2;
//	A1 = A3;
	A3 = A4;

	Func (A2);
//	Func (A3);

	Func2 (A1);
	Func2 (A3);
	A1 [0] = 5;
	Func (A1);

	Func2 (Array2D [6]);

	cout << Array2D [5] [0] << endl;
	}

void Func (const FixedArray <int, -5, 5> & Arr)
	{
	cout << Arr [0] << endl;
	}
