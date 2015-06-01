#include <iostream>
#include <string>
#include "Student.h"
#include "DString.h"
#include "Name.h"
#include "FLString.h"

//initialization of count
unsigned int Student::Count = 0;

	/* Constructors & Destructor */
Student::Student()
{
	Count++;
}

Student::Student(Student& s)
{
	name = s.name;
	address = s.address;
	idNum = s.idNum;
	phoneNum = s.phoneNum;
	Count++;
}

Student::Student(const Student& s)
{
	name = s.name;
	address = s.address;
	idNum = s.idNum;
	phoneNum = s.phoneNum;
	Count++;
}

Student::Student(ANT_String& first, ANT_String& middle, ANT_String& last, ANT_String& number, ANT_String& street, ANT_String& city, ANT_String& state, DString<char, 5>& zipIn, DString<char, 9>& idNumIn, DString<char, 10>& phoneNumIn)
{//this constructor will be useful for taking raw input from a file.
	name.SetFirst(first);
	name.SetMiddle(middle);
	name.SetLast(last);
	
	address.SetNumber(number);
	address.SetStreet(street);
	address.SetCity(city);
	address.SetState(state);
	address.SetZip(zipIn);

	this->idNum.setString(idNumIn);
	this->phoneNum.setString(phoneNumIn);
	//do you think the length checking ought to happen here, or in the FLString constructors, or both?
	Count++;
}

Student::~Student()
{
	Count--;
}

	/* Accessors */

void Student::setStudent(Student& s)
{	
	name = s.name;
	address = s.address;
	idNum = s.idNum;
	phoneNum = s.phoneNum;
}

void Student::setStudent(Name n, Address a, DString<char, 9> i, DString<char, 10> p)
{
	name = n;
	address = a;
	idNum = i;
	phoneNum = p;
}

const Name& Student::getName() const
{
	return name;
}

ANT_String Student::getFirstName()
{
	return name.GetFirst();
}

ANT_String Student::getMiddleName()
{
	return name.GetMiddle();
}

ANT_String Student::getLastName()
{
	return name.GetLast();
}

const Address& Student::getAddress() const 
{
	return address;
}

const DString<char, 9>& Student::getIdNum() const
{
	return idNum;
}

const DString<char, 10>& Student::getPhoneNum() const
{
	return phoneNum;
}

	/*IO Methods*/
void Student::printStudentName() 
{
	//cout << setw(20) << left << getName();
}

void Student::printStudentInfo()
{
	cout << "STUDENT: ";
	cout << name.GetLast() << ", " << name.GetFirst() << " " << name.GetMiddle() << endl;
	cout << address.GetNumber() << " " << address.GetStreet() << endl;
	cout << address.GetCity() << " " << address.GetState() << ", ";
	(address.GetZip()).Display();
	cout << endl;
	cout << "ID NUMBER: ";
	cout << idNum.getString() << endl;
	cout << "PHONE NUMBER: ";
	cout << phoneNum.getString() << endl;
}

	/* Operators */

Student& Student::operator=(Student &rhs)
{
	name = rhs.name;	      
	address = rhs.address;  
	idNum = rhs.idNum;		
	phoneNum = rhs.phoneNum; 
	
	return *this;
}

bool Student::operator==(Student &rhs)
{
	if( name == rhs.name	      &&
		address == rhs.address    &&
		idNum == rhs.idNum		  &&
		phoneNum == rhs.phoneNum   )
	{
		return true;
	}
	else
	{
	return false;
	}
	
}

inline ostream & operator<<(ostream & out, const Student & S)  
{
	return S.Display(out);	
}

inline ostream& Student::Display (ostream& out)const
{
	return out << name;
}

inline istream & operator>>(istream& in, Student& S)  
{
	S.getFirstName() = ReadString();
	return in;
}



int comparatorStudentName(const void* Student1, const void* Student2)
{
	Student * s1 = (Student*)Student1;
	Student * s2 = (Student*)Student2;
	
	return comparatorName((const void *) & s1->getName(), (const void *) & s2->getName());
}

//template<class T, int size>
int comparatorStudentIdNum(const void* Student1, const void* Student2)
{
	Student * s1 = (Student*)Student1;
	Student * s2 = (Student*)Student2;
	
	return comparatorDString((const void *)&(s2->idNum), (const void *)&(s1->idNum) );
}

