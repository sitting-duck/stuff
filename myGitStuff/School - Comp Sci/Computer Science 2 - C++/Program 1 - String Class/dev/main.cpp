
#include <iostream>
#include <string.h>

#include "ANT_String.h"

using namespace std;

void main()
{
	//Testing empty constructor. Pretty much nothing should happen here
	//but there should be no error. 
	ANT_String Str1;
	cout << "There was no error executing the empty copy constructor" << endl;
	//test successful

	//Testing constructor that takes a c type string. It should make a 
	//copy of the string we pass to it. 
	char myTestString[] = "This is a test string.";
	ANT_String Str2(myTestString);
	Str2.Display();
	cout << endl;
	//now lets change myTestString and make sure it doesn't change
	//the string value in our newly created object. 
	strcpy(myTestString, "Th1s 1s @ t3$t $tr1ng.");
	Str2.Display();
	cout << endl;
	//test successful

	//Testing Compare function that takes char*.  It should return an int indicating 
	//which string was larger.

	char testString2[] = "I am pretty big.";
	char testString3[] = "That string is wimpy.";
	//making the string object the char* will be compared to.
	ANT_String Str3(testString2);
	//Comparing an output 
	int result = Str3.Compare(testString3);
	if(result > 0)
		cout << "testString2 was bigger than testString3" << endl;
	if(result < 0)
		cout << "testString3 was bigger than testString2" << endl;	
	if(result == 0)
		cout << "The two strings were equal." << endl;
	//testString3 should be bigger than testString2
	//test successful.

	//Converting testString3 to object for testing Compare which takes object parameter
	ANT_String Str4(testString3);
	result = Str3.Compare(Str4);

	if(result > 0)
		cout << "Str3 was bigger than Str4" << endl;
	if(result < 0)
		cout << "Str4 was bigger than Str3" << endl;	
	if(result == 0)
		cout << "The two string objects were equal." << endl;
	//Str4 should be bigger than Str3
	//test successful

	//Beging testing Concat (char* version) 

	char testString4[] = "Let's be ";
	char testString5[] = "together!!!";
	char testString6[] = "  Forever!!!";

	ANT_String Str5(testString4);
	Str5.Concat(testString5);

	Str5.Display();
	cout << endl;
	//Should display "Let's be together!!!" on one line.
	//Testing for object version
	//test successful

	ANT_String Str6(testString6);
	Str5.Concat(Str6);
	Str5.Display();
	cout << endl;
	////Should display "Let's be together!!! Forever!!!" on one line.
	


	//Begin testing copy functions
	char testString7[] = "I am a good string.";
	char testString8[] = "I am a very evil string.";
	char testString9[] = "Nay, I am the most evil string.";

	ANT_String Str7(testString7);

	Str7.Copy(testString8);
	Str7.Display();
	cout << endl;

	//Should display "I am a very evil string."
	//test successful

	ANT_String Str8(testString9);
	Str7.Copy(Str8);
	Str7.Display();
	cout  << endl;
	
	//Should display "Nay, I am the most evil string."
	//test successful
	
	//Begin testing length functions
	char testString10[] = "abcd";

	ANT_String Str9(testString10);
	result = Str9.Length();

	cout << "Length of 'abcd' is : " << result << endl;

	//test successful.

	//Beginning Operator testing

	//testing = operator

	char testString11[] = "woot woot!";
	char testString12[] = "blah";

	ANT_String Str10(testString11);
	ANT_String Str11(testString12);

	Str10 = Str11;

	Str10.Display();
	cout << endl;

	//"blah" should be displayed.
	//test successful

	//testing == operator

	bool boolResult = (Str10 == Str11);
	cout << boolResult << endl;

	//test successful

	//testing != operator

	boolResult = (Str10 != Str11);
	cout << boolResult << endl;

	//test successful

	//testing & operator

	ANT_String Str12(Str10&Str11);
	Str12.Display();
	cout << endl;

	//test succesful

	//testing &= operator

	char testString13[] = "connect ";
	char testString14[] = "four!";

	ANT_String Str13(testString13);
	ANT_String Str14(testString14);

	ANT_String Str15(Str13&=Str14);

	Str13.Display();
	cout << endl;

	//test successful

	//testing << operator

	ANT_String Str16;
	cin >> Str16;
	ANT_String Str17 = "testing 1 2 3";
	cout << Str17 << endl;
	cout << Str16;

}

//OUTPUT

//There was no error executing the empty copy constructor
//This is a test string.
//This is a test string.
//testString3 was bigger than testString2
//Str4 was bigger than Str3
//Let's be together!!!
//Let's be together!!!  Forever!!!
//I am a very evil string.
//Nay, I am the most evil string.
//Length of 'abcd' is : 4
//blah
//0
//1
//blahblah
//connect four!
//hello derr
//☺☺☺☺☺☺☺☺☺☺
//Press any key to continue . . .
 