#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <string>
#include "Student.h"
#include <algorithm>

/* Static Assignments */
int Student::numOfStudentObjects = 0;

/* Constructors & Destructor */
Student::Student()
{
//	cout << endl << "Student() constructor invoked" << endl;
	this->name = NULL;
	this->setGrades(0,0,0,0,0);
	this->initialized = false;
}

Student::Student(string nameIn)
{
//	cout << endl << "Student(nameIn) constructor invoked" << endl;
	this->initialized = true;
	this->setName(nameIn);
	this->setGrades(0,0,0,0,0);

	numOfStudentObjects++;
}

Student::Student(string nameIn, int val1, int val2, int val3, int val4, int val5)
{
//	cout << endl << "Student(name & vals) constructor invoked" << endl;
	this->initialized = true;
	this->name = NULL;

	this->setName(nameIn);
	this->setGrades(val1, val2, val3, val4, val5);

	numOfStudentObjects++;
}

Student::~Student()
{
	delete name;
	delete [] grades;

	numOfStudentObjects--;
}

/* Accessors */
string Student::getName()
{
	return (*name);
}

void Student::setName(string newName)
{
//	cout << "Setting name" << endl;
	if (!(this->initialized)) 
	{ 
		this->initialized = true;
		this->numOfStudentObjects++;
//		cout << "Initialized object in setName" << endl;
	}

	delete name;
	name = new string(newName);
}

int* Student::getGrades()
{
	return this->grades;
}

void Student::setGrades(int* gradesIn)
{
	for (int i=0; i<5; i++)
		grades[i] = gradesIn[i];
}

void Student::setGrades(int val1, int val2, int val3, int val4, int val5)
{
	average = ((float)(val1 + val2 + val3 + val4 + val5) / (float)5);

	grades[0] = val1;
	grades[1] = val2;
	grades[2] = val3;
	grades[3] = val4;
	grades[4] = val5;
}

/* Print Methods */
void Student::printStudentGrades()
{
	for(int i=0; i<5; i++)
	{
		cout << setw(4) << right << grades[i];
	}
}

void Student::printStudentName()
{
	cout << setw(20) << left << getName();
}

void Student::printStudentAverage()
{
	cout << setw(6) << right << setiosflags(ios::fixed | ios::right) << setprecision(2) << average;
}

void Student::printStudentInfo()
{
	cout << "Name: ";
	printStudentName();
	cout << "    ";
	
	cout << "Grades: ";
	printStudentGrades();
	cout << "    ";

	cout << "Average: ";
	printStudentAverage();
	cout << endl;
}

void Student::printNumOfObjects()
{
	cout << "Number of instantiated Student Objects is: ";
	cout << numOfStudentObjects << endl;
}

/* Operators */

void Student::operator=(Student &rightHandSide)
{
	this->average = rightHandSide.average;
	this->setName(rightHandSide.getName());
	this->setGrades(rightHandSide.getGrades());
}

int Student::operator==(Student &rightHandSide)
{
	return this->getName().compare(rightHandSide.getName());
}

bool Student::operator<(Student &rightHandSide)
{
	return ( (this->getName().compare(rightHandSide.getName())) == -1);
}

bool Student::operator>(Student &rightHandSide)
{
	return ( (this->getName().compare(rightHandSide.getName())) == 1);
}

int Student::compare(const void* Student1, const void* Student2)
{
	return ((Student*) Student1)->getName().compare(((Student*)Student2)->getName());
}

int Student::iCompare(const void* Student1, const void* Student2)
{
	string s1 = ((Student*) Student1)->getName();
	string s2 = ((Student*) Student2)->getName();
	
	transform(s1.begin(), s1.end(), s1.begin(), ::toupper);
	transform(s2.begin(), s2.end(), s2.begin(), ::toupper);

	return s1.compare(s2);
}
