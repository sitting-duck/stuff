#include <iostream>
#include "SeatSelection.h"
#include <limits.h>
#include <cstdlib>
#include <cctype>

using namespace std;

int getSeatingType();
int getNumPplAndCheckIfThereAreEnoughSeats(SeatSelection& _SeatSection);
int getNumber();
char getYesOrNo();

int main()
{
	int seatingType = 0;
	int numPpl = 0;
	
	char repeat;
	SeatSelection premium(1,5);
	SeatSelection regular(6, 15);

	do
	{				
		seatingType = getSeatingType();
		if(seatingType == 1)
		{
			numPpl = getNumPplAndCheckIfThereAreEnoughSeats(premium);
			premium.seatParty(numPpl);
			//show the user the new state of the section
			cout << "\nSection after transaction." << endl;
			premium.printSection();
		}
		else // seatingType must == 2
		{
			numPpl = getNumPplAndCheckIfThereAreEnoughSeats(regular);
			regular.seatParty(numPpl);
			//show the user the new state of the section
			cout << "\nSection after transaction." << endl;
			regular.printSection();
		}	

		

		cout << "\nPurchase another set of tickets? (y/n): ";
		repeat = getYesOrNo();

		
	}while( repeat == 'y' || repeat == 'Y');
	
	return 0;
	
}

int getSeatingType()
{	
	cout << "\nPremium(1) or Regular(2): ";
		
		int SeatingType = getNumber();
		while( (SeatingType != 1) && (SeatingType != 2) )
		{
			cout << endl << "Invalid Input: Please enter 1 or 2." << endl;			
			SeatingType = getNumber();
		}		
		return SeatingType;
}

int getNumPplAndCheckIfThereAreEnoughSeats(SeatSelection& _SeatSection)
{	
	cout << "There are " << _SeatSection.getNumAvailable() << " seats available in this section: " << endl;
	cout << "\nPlease enter the number of people in your party: ";
	int numPpl = getNumber();
		
	while(numPpl <= 0)
	{
		cout << "Please enter a positive number of people for your party:" ;
		numPpl = getNumber();
		cout << endl;
	}
	while(numPpl > _SeatSection.getNumAvailable())
	{
		cout << "There are not enough seats available. I'm sorry :(" << endl;
		cout << "There are " << _SeatSection.getNumAvailable() << " available in this section. " << endl;
		cout << "Please enter the number of people in your party: ";		
		numPpl = getNumber();
	}

	return numPpl;
}

int getNumber()
{//this function will keep asking the user for input until the user enters a bonafide number
	//the programmer can change the size of the buffer if necessary
	
	char inputBuffer[100];
	int number;
	bool isNumber = false;
	
	do
	{
		cin.clear();
		cin.getline(inputBuffer, 100);
		if(!(isalpha((int)*inputBuffer)))
		{
			number = atoi(inputBuffer);
			isNumber = true;
		}
		else
		{
			cout << endl << "Invalid Input: Input was not a number." << endl;
			cout << "Please enter a number: ";			
			isNumber = false;
		}		
	}while(!isNumber);
			
		return number;
}

char getYesOrNo()
{
	char response;

	cin >> response;		

	while( !(response == 'y' || response == 'n') )
	{
		cout << "Invalid input: Please enter y or n: ";

		cin >> response;
	}
	
	cin.clear();
	cin.ignore();
	return response;
}

