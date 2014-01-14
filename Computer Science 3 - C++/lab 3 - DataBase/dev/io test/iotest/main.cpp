#include <fstream>
#include <iostream>
#include "File.h"

using namespace std;

void main()
{
	char str[10];

	//creates an instance of ofstream and opens example.txt
	ofstream a_file("stuff.txt");
	//outputs to example.txt through a file.
	//a_file<<"This text will now be inside of example.txt";
	//close the file stream explicitly
	
	//Open for reading the file
//	ifstream b_file("stuff.txt");
	//Reads one string from the file
//	b_file>>str;
	//Should output 'this'
	//cout << str << endl;
	//cin.get(); //wait for a keypress
	//b_file is closed implicitly here.

	a_file.seekp(0);
	a_file.write("This is going to be in the file.", 32);
	a_file.seekp(8);
	a_file.write("This is going to be in the file.", 32);
	a_file.seekp(0);
	a_file.write("Hello, ", 7);
	a_file.close();

	a_file.clear();
	a_file.write("ashley", 6);

	File f1;
	

}