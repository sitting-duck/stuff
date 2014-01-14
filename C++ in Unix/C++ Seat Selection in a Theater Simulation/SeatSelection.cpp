#include "SeatSelection.h"
#include <cstdlib>
#include <iostream>

using namespace std;

SeatSelection::SeatSelection()
{
	numRows = 0;
	firstRow = 0;
	numAvailable = 0;
}

SeatSelection::SeatSelection(int _firstRow, int _numRows)
{
	seats = new bool*[_numRows];
	for(int i = 0; i < _numRows; i++)
	{
		//seats[i] = new bool[10];
		seats[i] = (bool*)calloc(10, sizeof(bool));
	}

	numRows = _numRows;
	firstRow = _firstRow;	
	numAvailable = _numRows*10;


}

SeatSelection::~SeatSelection()
{
	for(int i=0; i<numRows;i++)
	{
		delete [] seats[i];
	}
	delete seats;
}

void SeatSelection::SetSeatsToTaken(int _row, int _column, int _numPpl)
{
	//update class var numAvailable
	numAvailable -= _numPpl;

	int numRows = _numPpl/10;

	for(int i = numRows; i >= 0; i--)
	{
		//go backwards and set all the seats in the seats array to 1's
		for(;_numPpl > 0; _numPpl--)
		{
			seats[_row][_column] = 1;
			_column--;
		}
	}
	
}

bool SeatSelection::seatParty(int _numPpl)
{  //this function will try to find a spot for the given number of people. They must be seated consecutively if at all
	//possible. If not it will seat them at the next available spots.
	
	int ConsecutiveSeats = 0;
	
	for(int row = 0; row < numRows; row++)
	{
		ConsecutiveSeats = 0; //if we've reached the end of the row without the required num of consecutive seats we start over.
		for(int column = 0; column < 10; column++)
		{
			if(seats[row][column] == 0)
			{
			//	cout << "Consecutive Seats = " << ConsecutiveSeats << endl;
				ConsecutiveSeats++;
			}
			else//the current seat is taken before we find enough for numPpl
			{
			//	cout << "This seat is taken" << endl;
				ConsecutiveSeats = 0;
				continue; 
			}
			
			if(ConsecutiveSeats == _numPpl) //we've found a spot for them to sit
			{
			//	cout << "Found a spot at (" << row << "," << column << ")" << endl;
				//numAvailable -= _numPpl;
				SetSeatsToTaken(row, column, _numPpl);
				printTicket(row, column, _numPpl);
				return 1;
			}
		}//end columns for loop
	}//end rows for loop

	//if we've reached this point, we've gone through the entire array and not found enough consecutive seats 
	//to seat the party on a single row. These loops below will seat party members at the first available spots found.
	
	int seatsFound = 0;
	int seatsRow[_numPpl];
	int seatsColumn[_numPpl];

	for(int row = 0; row < numRows; row++)
	{
		for(int column = 0; column < 10; column++)
		{
			if(seats[row][column] == 0 && seatsFound != _numPpl)
			{
				seats[row][column] = 1;
				seatsRow[seatsFound] = row;
				seatsColumn[seatsFound] = column;
				seatsFound++;
			}
			if(seatsFound == _numPpl)
			{
				numAvailable -= _numPpl;
				printTicket(seatsRow, seatsColumn, _numPpl);//this needs to be fixed
				return 1;
			}
		}
	}	

	//if we've reached this point, we have been unable to seat the party.
	cout << "I'm sorry, we were unable to seat you. :(" << endl;	
	return 0;
}

void SeatSelection::printTicket(int _row, int _column, int _numPpl)
{
	cout << "Your seats are: ";
	for(int i= 0; i < _numPpl; i++)
	{
		_column++;
		cout << _row + firstRow << (char)((_column - _numPpl) + 'A') << " ";
	}
	cout << "." << endl;

}

void SeatSelection::printTicket(int* _row, int* _column, int _numPpl)
{
	cout << "\nYour seats are:";
	for(int i = 0; i < _numPpl; i++)
	{
		cout << " " << firstRow + _row[i] << (char)(_column[i] + 'A') << " ";
	}
	cout << "." << endl;
}

void SeatSelection::printSection()
{
	cout << endl;
	for(int row = 0; row < numRows; row++)
	{
		for(int chair = 0; chair < 10; chair++)
		{
			cout << seats[row][chair];
		}
		cout << endl;
	}
}

int SeatSelection::getNumAvailable()
{
	return numAvailable;
}
