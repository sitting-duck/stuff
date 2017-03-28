// Templated.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Templated.h"
#include "Student.h"
#include <Windows.h>
#include <fstream>

void printAllStudentsInfo(Array<Student>* Students);

#define NAME_SIZE 1024
#define LINE_SIZE 80

int _tmain(int argc, _TCHAR* argv[])
{
	string fileName = "ProgramSixData.txt";
	string userInput;
	fstream inputFile;

	FILE *fp = NULL;
	char fullname[NAME_SIZE];
	char line[NAME_SIZE];

	/* Get Handles to the console */
	HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	/* Set console colors */
	SetConsoleTextAttribute(hStdOut, (WORD)(0x9F));
	system("cls");	// clear the screen


	Array<Student> *Students = new Array<Student>;

	do 
	{
		memset((void *)fullname, 0x0, NAME_SIZE);
	
		cout << endl << "Please enter the name of the input file or enter QUIT to exit: ";
		cin.getline(fullname, NAME_SIZE-1, '\n');

		if(strncmp(fullname,"QUIT", 4) ==  0)
		{
			cout << "Program terminated on user request." << endl;
			exit(1);
		}

		if( (fp=fopen(fullname,"r")) == NULL)
		{	cout << "Unable to open file " << fullname << endl;	}

	} while (fp == NULL);
	
	// Reaching here means we were able to open the file successfully.

	do
	{
		int v1, v2, v3, v4, v5;
		char c1, c2, c3, c4;

		fscanf(fp, "%s[^\n]",line);
		if(strncmp(line,"EOF",3) == 0)
		{ break; }

		fscanf(fp,"%d%c%d%c%d%c%d%c%d[^\n]",&v1,&c1,&v2,&c2,&v3,&c3,&v4,&c4,&v5);

		Student* tmpStudent = new Student((string)line, v1, v2, v3, v4, v5);
		Students->add(*tmpStudent);

	} while (1);

	fclose(fp);

	//cout << "The students uploaded are: " << endl;
	//printAllStudentsInfo(Students);
	SetConsoleTextAttribute(hStdOut, (WORD)(0x9B));
	cout << endl << "The students sorted (case sensitive) are: " << endl << endl;

	SetConsoleTextAttribute(hStdOut, (WORD)(0x9F));
	Students->sort();
	printAllStudentsInfo(Students);


	SetConsoleTextAttribute(hStdOut, (WORD)(0x9B));

	cout << endl << "The students sorted (case insensitive) are: " << endl << endl;

	SetConsoleTextAttribute(hStdOut, (WORD)(0x9F));
	Students->sort(true);
	printAllStudentsInfo(Students);

	return 0;
}

void printAllStudentsInfo(Array<Student>* Students)
{
	for(int i=0; i< Students->getNumOfElements(); i++)
	{
		Students->ptrObjectArray[i].printStudentInfo();
		cout << endl;
	}
}