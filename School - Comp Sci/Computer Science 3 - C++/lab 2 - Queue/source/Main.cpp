#include <iostream>
#include "UBArray.h"
#include "UBStack.h"
#include "Queue.h"

using namespace std;


void main ()
{
	try
	{
		Queue Q1;

		WCS_String Einstein("Einstein");
		WCS_String Tesla("Tesla");
		WCS_String Newton("Newton");
		WCS_String Euler("Euler");

		Q1.QueueFunc(Einstein);
		Q1.QueueFunc(Tesla);
		Q1.QueueFunc(Newton);
		Q1.QueueFunc(Euler);

		cout << Q1[1] << endl;
		cout << Q1[2] << endl;
		cout << Q1[3] << endl;
		cout << Q1[4] << endl << endl;

		//mfucking off by one errors

		Q1.DeQueueFunc();

		//cout << Q1[1] << endl; "Element Not Found."
		cout << Q1[2] << endl;
		cout << Q1[3] << endl;
		cout << Q1[4] << endl << endl;

		Q1.DeQueueFunc();

		//cout << Q1[2] << endl; "Element Not Found."
		cout << Q1[3] << endl;
		cout << Q1[4] << endl << endl;

		Q1.DeQueueFunc();
		//cout << Q1[3] << endl; "Element Not Found."
		cout << Q1[4] << endl << endl;

		Q1.DeQueueFunc();
		//cout << Q1[4] << endl; "Element Not Found."

		Q1.QueueFunc(Einstein);
		Q1.QueueFunc(Tesla);
		Q1.QueueFunc(Newton);
		Q1.QueueFunc(Euler);

		cout << Q1[1] << endl;
		cout << Q1[2] << endl;
		cout << Q1[3] << endl;
		cout << Q1[4] << endl << endl;

		while(1)
		{
			Q1.AcceptCommand();
			Q1.Print();
		}


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

