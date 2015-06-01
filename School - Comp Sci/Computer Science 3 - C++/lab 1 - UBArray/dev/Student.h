#pragma once

#include <iostream>
#include <string>
#include <iomanip>

#include "DString.h"
#include "Name.h"
#include "Address.h"

using namespace std;

class Student
{
	private:
		Name name;
		Address address;

		DString<char, 9>  idNum; 
		DString<char, 10> phoneNum;
		static unsigned int Count;
		

	public:
		/* Constructors & Destructor */
		Student();
		Student(Student& s);
		Student(const Student& s);
		Student(ANT_String&, ANT_String&, ANT_String&, ANT_String&, ANT_String&, ANT_String&, ANT_String&, DString<char, 5>&, DString<char, 9>&, DString<char, 10>&); 
		~Student();

		/* Accessors */
		const Name& getName() const;
		ANT_String getFirstName();
		ANT_String getMiddleName();
		ANT_String getLastName();
		const Address& getAddress()const;
		const DString<char, 9>& getIdNum() const;
		const DString<char, 10>& getPhoneNum() const;

		void setStudent(Student&);
		void setStudent(Name, Address, DString<char, 9>, DString<char, 10>); 

		static unsigned int getStudentCount(){return Count;}

		//void setAddress(

		/* Operators */
		Student& operator=(Student &rightHandSide);
		bool operator>(Student &rightHandSide);
		bool operator<(Student &rhs);
		bool operator==(Student &rhs);

		/* Print Methods */
		void printStudentInfo();
		void printStudentName();
		ostream& Display (ostream& out)const;
		friend extern ostream & operator<<(ostream & out, const Student & S);
		friend extern istream & operator>>(istream& in, Student& S);

		/* Other Methods */
		friend int comparatorStudentName(const void* Student1, const void* Student2);
		friend int comparatorStudentIdNum(const void* Student1, const void* Student2);
		//compare idNum


};




