#include <iostream>
#include "ANT_String.h"
#include "ReadString.h"
#include "UppercaseString.h"
#include "DigitString.h"

using namespace std;
	
void main()  
{
	cout << "Testing for the UPPERCASE CLASS: " << endl << endl << endl;
	UpperCaseString UStr1("hello hello hello");
	UpperCaseString UStr2("Hello there!");
	UpperCaseString UStr3("Alright already!");

	cout << "Ustr1 = " << UStr1 << endl;
	cout << "Ustr2 = " << UStr2 << endl;
	cout << "Ustr3 = " << UStr3 << endl;

	UStr1 = UStr2;

	cout << "After assignment UStr1 is now: " << UStr1 << endl;


	cout << "Testing == operator: " << endl;
	if(UStr1 == UStr2)
		cout << "UStr1 and UStr2 are equal." << endl;
	else
		cout << "UStr1 and UStr2 are NOT equal." << endl;

	if(UStr1 == UStr3)
		cout << "UStr1 and UStr3 are equal." << endl;
	else
		cout << "UStr1 and UStr3 are NOT equal." << endl;

	
	cout << "Testing < > <= >= Operators:" << endl; 
	cout << "Ustr1 = " << UStr1 << endl;
	cout << "Ustr2 = " << UStr2 << endl;
	cout << "Ustr3 = " << UStr3 << endl;

	if(UStr1 > UStr3)
		cout << "UStr1 > UStr3" << endl;
	else
		cout << "UStr1 <= UStr3" << endl;

	if(UStr1 >= UStr3)
		cout << "UStr1 >= UStr3" << endl;
	else
		cout << "UStr1 < UStr3" << endl;

	if(UStr1 < UStr2)
		cout << "UStr1 < UStr2" << endl;
	else
		cout << "UStr1 >= UStr2" << endl;

	if(UStr1 <= UStr2)
		cout << "UStr1 <= UStr2" << endl;
	else
		cout << "UStr1 > UStr2" << endl;

	//testing & and &= operators
	cout << "testing & and &= operators" << endl;
	UpperCaseString UStr5("Hello ");
	UpperCaseString UStr6("World!");
	cout << "Ustr5 = " << UStr5 << endl;
	cout << "Ustr6 = " << UStr6 << endl;
	UStr5 = (UStr5 & UStr6);
	cout << "Ustr5 now = " << UStr5 << endl << endl;
	UpperCaseString UStr7(" Goodbye World!");
	cout << "Ustr7 = " << UStr7 << endl;
	UStr5 &= UStr7;
	cout << "UStr5 &= UStr7" << endl;
	cout << "Ustr5 is now: " << UStr5 << endl;


	
	//testing >> operator ; already tested << operator
	cout << "Testing >> (input) operator: please enter a string" << endl;
	UpperCaseString UStr4;
	cin >> UStr4;
	cout << UStr4 << endl;

	//testing for [] operator
	cout << "testing for [] operator" << endl;
	UpperCaseString UStr8 ("abcdefg");
	cout << UStr8[0] << endl;


	//************************************************************************************************
	//testing for the DigitString class
	//************************************************************************************************

	cout << "Testing for the DIGITSTRING CLASS: " << endl << endl << endl;
	DigitString DStr1("1234");
	DigitString DStr2("5678");
	
	////Testing Assertions *************************************************************************
	////uncomment and one line at a time and execute to see assertions.							  **
	////recomment afterword, and uncomment the next line and execute, to test the next assertion. **
	////********************************************************************************************
	char a = 'a';
	char* myCharPntr = &a;
	ANT_String myNonDigitString("not a digit");
	//DigitString DStr3("not a number");
	//DigitString DStr3(myCharPntr);
	//DigitString DStr3(myNonDigitString);


	DigitString DStr3("99999");
	cout << "Dstr1 = " << DStr1 << endl;
	cout << "Dstr2 = " << DStr2 << endl;
	

	DStr1 = DStr2;

	cout << "After assignment DStr1 is now: " << DStr1 << endl;


	cout << "Testing == operator: " << endl;
	if(DStr1 == DStr2)
		cout << "DStr1 and DStr2 are equal." << endl;
	else
		cout << "DStr1 and DStr2 are NOT equal." << endl;

	if(DStr1 == DStr3)
		cout << "DStr1 and DStr3 are equal." << endl;
	else
		cout << "DStr1 and DStr3 are NOT equal." << endl;

	
	cout << "Testing < > <= >= Operators:" << endl; 
	cout << "Dstr1 = " << DStr1 << endl;
	cout << "Dstr2 = " << DStr2 << endl;
	cout << "Dstr3 = " << DStr3 << endl;

	if(DStr1 > DStr3)
		cout << "DStr1 > DStr3" << endl;
	else
		cout << "DStr1 <= DStr3" << endl;

	if(DStr1 >= DStr3)
		cout << "DStr1 >= DStr3" << endl;
	else
		cout << "DStr1 < DStr3" << endl;

	if(DStr1 < DStr2)
		cout << "DStr1 < DStr2" << endl;
	else
		cout << "DStr1 >= DStr2" << endl;

	if(DStr1 <= DStr2)
		cout << "DStr1 <= DStr2" << endl;
	else
		cout << "DStr1 > DStr2" << endl;

	//testing & and &= operators
	cout << "testing & and &= operators" << endl;
	DigitString DStr5("867564");
	DigitString DStr6("534231");
	cout << "Dstr5 = " << DStr5 << endl;
	cout << "Dstr6 = " << DStr6 << endl;
	DStr5 = (DStr5 & DStr6);
	cout << "Dstr5 now = " << DStr5 << endl << endl;
	DigitString DStr7("111222333");
	cout << "Dstr7 = " << DStr7 << endl;
	DStr5 &= DStr7;
	cout << "DStr5 &= DStr7" << endl;
	cout << "Dstr5 is now: " << DStr5 << endl;

	
	//testing >> operator ; already tested << operator
	cout << "Testing >> (input) operator: Please enter a numeric string:" << endl;
	DigitString DStr4;
	cin >> DStr4;
	cout << DStr4 << endl;

	//testing for [] operator
	cout << "testing for [] operator" << endl;
	DigitString DStr8("12345");
	cout << DStr8[0] << endl;



}