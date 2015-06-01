#include <iostream>

using namespace std;

#include "RAFile.h"

int main ()
	{
		try
		{
			RAFile	RA1;
			WCS_String FileName("crap.txt");
	
			RA1.Open(FileName);
			WCS_String s1("Ashley is an doo doo head.");
			RA1.Insert(0, s1);
			WCS_String r1("");
			RA1.Read(0, r1);
			cout << "At 0:" << r1 << endl;
			WCS_String s2("Sam");
			RA1.Insert(2, s2);
			
		}
		catch(int e)
		{
			switch(e)
			{
				case RAFile::CannotOpenFile:
					{
						cout << "Cannot open file." << endl;
						break;
					}
				default:
				{
				cout << "Unknown Exception Thrown." << endl;
				break;
				}
			}
		}


	}
