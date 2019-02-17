#include <iostream> // for std terminal intput and output
#include <fstream>  // for opening, reading, writing, and closing files
#include <stdio.h> // for tokening string input from the inpt files
#include <string.h> // for using std::strings in place of char*
#include <vector>
#include "Employee.h" 
#include "Paycheck.h"

using namespace std;

void printUsage();
char* tokenizeString(char* stringToTokenize, const char* delimiterString);
bool isDelimiter(char charInQuestion, const char* delimiterString);

int main(int argc, char** argv)
{
	// first we parse the contents of master.txt to extract the employee data
	if (argc != 3) {
		cout << "ERROR: incorrect number of arguments" << endl;
		printUsage();
		return -1; // user did not supply the correct number of arguments so we exit. 
	}

	cout << "\tgot filename: " << argv[1] << " for master text file input. " << endl;

	// create a std::string to store this filename for the master employee info input file
	std::string masterFileName = argv[1];	

	// we create an input file stream so that we can check that the master file passed to the
	// program exists. If it doesn't exist, we print an error message and exit the program.
	ifstream masterInputFileStream;
	masterInputFileStream.open(masterFileName.c_str(), std::ifstream::in);

	// the constructor for ifstream can't return a value to let us know if it failed or not
	// because it is a constructor. Instead we check the ios failbit to see if the file exists
	// and was opened correctly
	if (masterInputFileStream.fail()) {
		cout << "\tmaster file: " << masterFileName.c_str() << " was unable to be opened. Exiting program." << endl;
		return -1;
	}
	else {
		cout << "\t" << masterFileName.c_str() << " was opened successfully." << endl;
	}

	// create a std::string to store the filename for the transactions input file
	std::string transactionFileName = argv[2];

	// again, create an input file stream to check for the existence of this file and then open it
	ifstream transactionInputFileStream;
	transactionInputFileStream.open(transactionFileName.c_str(), std::ifstream::in);
	
	// if the file was unable to be opened we exit the program, there is nothing more to be done. 
	if (transactionInputFileStream.fail()) {
		cout << "\ttransaction file: " << transactionFileName.c_str() << " was unable to be opened. Exiting program." << endl;
		return -1;
	}
	else {
		cout << "\t" << transactionFileName.c_str() << " was opened successfully." << endl;
	}

	// grab the data from the master text file and create an employee for each line in the file
	char oneline[1024];
	vector<PayCheck> paychecks;
	while (!masterInputFileStream.eof())
	{
		masterInputFileStream.getline(oneline, 1024, '\n');
		cout << "got line: " << oneline << endl;

		char* charPtr;
		//charPtr = strtok(oneline, " ");

		charPtr = tokenizeString(oneline, " ");
		cout << "got employee id: " << charPtr << endl;
		int employeeId = atoi(charPtr);

		if (employeeId == 0) {
			cout << "WARNING: employee id 0 is invalid. This employee will not be paid and will not be included in the payroll report." << endl;
			continue;
		}

		charPtr = tokenizeString(NULL, " ");
		string firstName = charPtr;
		cout << "got first name: " << firstName.c_str() << endl;
		
		charPtr = tokenizeString(NULL, " ");
		string lastName = charPtr;
		cout << "got last name: " << lastName.c_str() << endl;

		string fullName = firstName + lastName;

		charPtr = tokenizeString(NULL, " ");
		string poundSymbol = charPtr;
		cout << "got pound symbol: " << poundSymbol.c_str() << endl;

		charPtr = tokenizeString(NULL, " ");
		double payRatePerHour = atof(charPtr);
		cout << "got pay per hour: " << payRatePerHour << endl;

		charPtr = tokenizeString(NULL, " ");
		int numberOfDependents = atoi(charPtr);
		cout << "got number of dependents: " << numberOfDependents << endl;

		charPtr = tokenizeString(NULL, " ");
		int typeOfEmployee = atoi(charPtr);
		cout << "got type of employee: " << typeOfEmployee << endl;


		// get the line for the employee id and the number of hours works from the transactions text file
		cout << "from transactions file: " << endl;
		transactionInputFileStream.getline(oneline, 1024, '\n');

		Employee employee(employeeId, fullName, payRatePerHour, numberOfDependents, typeOfEmployee);
		

		cout << "got line: " << oneline << endl;
		charPtr = tokenizeString(oneline, " ");
		cout << "employee id is: " << charPtr << endl;
		
		charPtr = tokenizeString(NULL, " ");
		int numberOfHoursWorked = atoi(charPtr);
		cout << "got number of hours worked: " << numberOfHoursWorked << endl;
		
		//PayCheck()
	}	
	
	masterInputFileStream.close();
	transactionInputFileStream.close();
	system("pause");
	return 1;
}

char* tokenizeString(char* stringToTokenize, const char* delimiterString) {
	cout << "tokenizeString: " << endl;
	cout << "\tstringToTokenize: " << stringToTokenize << endl;
	cout << "\tdelimiterString: '" << delimiterString <<  "'" << endl;

	char currentChar = stringToTokenize[0];

	//eat leading whitespace
	int i = 0;
	while (currentChar == ' ') { 
		cout << "leading whitespace removed" << endl;
		i++; 
		currentChar = stringToTokenize[i];
	}

	cout << "currentChar: '" << currentChar << "'" << endl;

	
	while (currentChar != '\0')
	{
		cout << "currentChar: '" << currentChar << "'" << endl;
		if (isDelimiter(currentChar, delimiterString))
		{
			cout << "found delimiter '" << currentChar << "'" << endl;
			stringToTokenize[i] = NULL;
			return &stringToTokenize[i];
		}
		i++;
	}
}

bool isDelimiter(char charInQuestion, const char* delimiterString)
{
	cout << "isDelimiter: charInQuestion: '" << charInQuestion << "' delimiter string: '" << delimiterString << "'" << endl;

	char currentChar = delimiterString[0];
	int i = 0;
	while (currentChar != '\0')
	{
		if (charInQuestion == delimiterString[i])
		{
			cout << "char in question: " << charInQuestion << " equals delimeter: " << delimiterString[i]  << " in delim string: " << delimiterString << endl;
			return true;
		}
		i++;
	}
	return false;
}


void printUsage()
{
	cout << "Payroll Report:" << endl << endl;
	cout << "Usage: Employee_Project.exe <master.txt> <trans.txt>" << endl << endl;
	cout << "This program takes two files as input and prints a payroll report to a text file." << endl << endl;

	cout << "<master.txt>: \nA text file containing employee information." << endl;
	cout << "The master file has one line of input per employee containing :" << endl;
	cout << "employee ID number(integer value)" << endl;
	cout << "name(20 characters) - see Hint 6 below on how to input the name" << endl;
	cout << "pay rate per hour(floating - point value)" << endl;
	cout << "number of dependents(integer value)" << endl;
	cout << "type of employee(0 for union, 1 for management)" << endl;
	cout << "This file is ordered by ID number and contains information for 6 emplyees.You can assume that there is exactly" << endl;
	cout << "one space between the employee ID number and the name.You can also assume that the name occupies 20" << endl;
	cout << "columns in the file.Important: See the Requirements / Hints section at the bottom of this page for more" << endl;
	cout << "information on the input files." << endl << endl;

	cout << "<trans.txt>: \nA text file containing number of horus worked per week for each employee" << endl;
	cout << "This file is also ordered by employee ID number and contains information for the 6 employees.Note: You can" << endl;
	cout << "assume that the master file and the transaction file have the same number of records, and that the first hours" << endl;		
	cout << "worked is for the first employee, etc.You can also assume that the employee IDs in the master file are exactly" << endl;
	cout << "the same as the employee IDs in the transaction file." << endl << endl;

}

