//******************************************************************
// Assignment 8 - Test Scores
// Programmer: Jeremy Gelwix
// Completed : 11/18/2018
// Status    : Complete
//
// This program processes test scores for a class
//
//******************************************************************


#include <iostream>			// input/output declarations
#include <iomanip> 			// i/o manupulator declarations
#include <string>			// string declarations
using namespace	std;

void inputGrades(int *, int);

int main()
{
	int *testGrades = nullptr;
	int numStudents;

	cout << "How many student grades do you wish to enter?" << endl;
	cin >> numStudents;

	testGrades = new int[numStudents];

	inputGrades(testGrades, numStudents);

	cout << *testGrades << endl;

	system("pause");

}

//*****************************************************************
// Function: inputGrades
//
// This functions takes the user inputs for grades
//*****************************************************************
void inputGrades(int *gArray, int students)
{
	for (int count = 0; count < students; count++)
	{
		cout << "Enter the test grade for the student: " << endl;
		cin >> gArray[count];
		while (gArray[count] < 0 || gArray[count] > 104)
		{
			cout << "INVALID ENTRY! Pleae enter a score from 0 to 104.";
			cin >> gArray[count];
		}
	}
}