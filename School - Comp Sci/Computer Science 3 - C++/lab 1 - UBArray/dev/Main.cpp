#include <iostream>
#include <string>
#include <string.h>

using namespace std;

#include "UBArray.h"
#include "Student.h"
#include "ANT_String.h"
#include "ReadString.h"

void Func (const UBArray <char, int> &);

void main ()
	{
		try
		{
//**************************************************************************
//				TESTING DATA TYPE STRING, INDEX TYPE INTEGER		
//**************************************************************************
		//testing constructors
		UBArray <string, int>		UB1;
		
		//testing bracket operators
		UB1 [1]	= "Why Hello World!";
		UB1 [2] = "Fancy meeting you here.";
		UB1 [3] = "You come here a lot?";
	
		//testing size function
		cout << "Number of Elements is " << UB1.Size () << endl;
		
		cout << "Testing GetFirst: " << UB1.GetFirst()<< endl;
		cout << "Testing GetNext:  " << UB1.GetNext() << endl;
		cout << "Testing GetNext:  " << UB1.GetNext() << endl;


		//some nifty pointer stuff that you can do
		//UB1.GetFirst () = 'd';

			cout << "testing 'At()' function at 1: " << UB1.At(1) << endl;
			cout << "testing 'At()' function at 2: " << UB1.At(2) << endl;
			cout << "testing 'At()' function: at 3: " << UB1.At(3) << endl;

			cout << "testing 'Remove()' function at 1: " << UB1.Remove(1) << endl;
			cout << "testing 'Remove()' function at 2: " << UB1.Remove(2) << endl;
			cout << "testing 'Remove()' function: at 3: " << UB1.Remove(3) << endl;

			cout << "Number of Elements is " << UB1.Size () << endl;

//			cout << "testing 'Remove()' function: at 4: " << UB1.Remove(4) << endl;
//			cout << "testing 'GetFirst()' function: " << UB1.GetFirst() << endl;
//			cout << "testing 'GetNext()' function: " << UB1.GetNext() << endl;
//			cout << "testing 'GetLast()' function: " << UB1.GetLast() << endl;
//			cout << "testing 'GetPrev()' function: " << UB1.GetPrev() << endl;

			UB1 [1]	= "Why Hello World!";
			UB1 [2] = "Fancy meeting you here.";
			UB1 [3] = "You come here a lot?";

			cout << "testing 'GetFirst()' function: " << UB1.GetFirst() << endl;
			cout << "testing 'GetNext()' function: " << UB1.GetNext() << endl;
			cout << "testing 'GetLast()' function: " << UB1.GetLast() << endl;
			cout << "testing 'GetPrev()' function: " << UB1.GetPrev() << endl;

//**************************************************************************
//				TESTING MULTIPLE DATA TYPE ELEMENTS, INDEX TYPE STRING		
//**************************************************************************
		//testing constructors
		ANT_String Stallman("Stallman");
		ANT_String Torvalds("Torvalds");
		ANT_String Turing("Turing");

		Name nStallman("Stallman", "GNU", "Richard");
		Name nTorvalds("Torvalds", "Linux", "Linus");
		Name nTuring("Turing", "SkyNet", "Alan");

		Address a;
		DString<char, 9>  idNum; 
		DString<char, 10> phoneNum;

		Student Richard;		
		Richard.setStudent(nStallman,a, idNum, phoneNum); 
		
		Student Linus;		
		Linus.setStudent(nTorvalds,a, idNum, phoneNum); 
		
		Student Alan;		
		Alan.setStudent(nTuring,a, idNum, phoneNum); 


		UBArray <class Student, class ANT_String> UB2;
		//testing bracket operators
		UB2 [Stallman]	= Richard;
		UB2 [Torvalds] = Linus;
		UB2 [Turing] = Alan;
	
		//testing size function
		cout << "Number of Elements is " << UB2.Size () << endl;
		
		cout << "Testing GetFirst: " << UB2.GetFirst()<< endl;
		cout << "Testing GetNext:  " << UB2.GetNext() << endl;
		cout << "Testing GetNext:  " << UB2.GetNext() << endl;


//		//some nifty pointer stuff that you can do
//		//UB2.GetFirst () = 'd';

			cout << "testing 'At()' function at 1: " << UB2.At(Stallman) << endl;
			cout << "testing 'At()' function at 2: " << UB2.At(Torvalds) << endl;
			cout << "testing 'At()' function: at 3: " << UB2.At(Turing) << endl;

			cout << "testing 'Remove()' function at 1: " << UB2.Remove(Stallman) << endl;
			cout << "testing 'Remove()' function at 2: " << UB2.Remove(Torvalds) << endl;
			cout << "testing 'Remove()' function: at 3: " << UB2.Remove(Turing) << endl;

			cout << "Number of Elements is " << UB2.Size () << endl;
//
////			cout << "testing 'Remove()' function: at 4: " << UB2.Remove(4) << endl;
////			cout << "testing 'GetFirst()' function: " << UB2.GetFirst() << endl;
////			cout << "testing 'GetNext()' function: " << UB2.GetNext() << endl;
////			cout << "testing 'GetLast()' function: " << UB2.GetLast() << endl;
////			cout << "testing 'GetPrev()' function: " << UB2.GetPrev() << endl;
//
			UB2 [Stallman]	= Richard;
			UB2 [Torvalds] = Linus;
			UB2 [Turing] = Alan;

			cout << "testing 'GetFirst()' function: " << UB2.GetFirst() << endl;
			cout << "testing 'GetNext()' function: " << UB2.GetNext() << endl;
			cout << "testing 'GetLast()' function: " << UB2.GetLast() << endl;
			cout << "testing 'GetPrev()' function: " << UB2.GetPrev() << endl;

//**************************************************************************
//								END TESTING
//**************************************************************************
			
		}
		catch(Exceptions e)
		{
			switch(e)
			{
			case 1: 
				{
				cout << "Linked List is empty." << endl;
				break;
				}
			case 2:
				{
				cout << "GetFirst not called. Before GetNext or GetPrev can be called." << endl;
				break;
				}
			case 3:
				{
				cout << "No Next Element Found." << endl;
				break;
				}
			case 4:
				{
				cout << "No Previous Element Found." << endl;
				break;
				}
			case 5: 
				{
				cout << "Element Not Found." << endl;
				break;
				}
			default:
				{
				cout << "Unknown Exception Thrown." << endl;
				break;
				}
			}
		}
		catch(...)
		{
			cout << "Unknown Exception Thrown." << endl;
		}

		
}	

