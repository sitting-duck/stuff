#ifndef STUDENT_H
#define STUDENT_H

#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

class Student
{
	private:
		bool initialized;
		string* name;
		int grades[5];
		float average;
		static int numOfStudentObjects;

	public:
		/* Constructors & Destructor */
		Student();
		Student(string nameIn);
		Student(string nameIn, int val1, int val2, int val3, int val4, int val5);
		~Student();

		/* Accessors */
		void setName(string newName);
		string getName();

		void setGrades(int val1, int val2, int val3, int val4, int val5);
		void setGrades(int* gradesIn);
		int* getGrades();

		/* Operators */
		//int operator==(const Student &rightHandSide);

		void operator=(Student &rightHandSide);
		bool operator>(Student &rightHandSide);
		bool operator<(Student &rightHandSide);
		int operator==(Student &rightHandSide);

		/* Print Methods */
		void printStudentInfo();
		void printStudentName();
		void printStudentGrades();
		void printStudentAverage();
		static void printNumOfObjects();

		/* Other Methods */
		static int compare(const void* Student1, const void* Student2);
		static int iCompare(const void* Student1, const void* Student2);
};

#endif