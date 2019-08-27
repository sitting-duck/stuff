#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>

using namespace std;

class Employee
{
private:
	int id; // employee ID
	string name; // employee name
	double hourlyPay; // pay per hour
	int numDeps; // number of dependents
	int type; // employee type

public:
	Employee(int initId = 0, string initName = "",
		double initHourlyPay = 0.0,
		int initNumDeps = 0, int initType = 0); // Constructor

	bool set(int newId, string newName, double newHourlyPay,
		int newNumDeps, int newType);

	int getId();
	string getName();
	double getHourlyPay();
	int getNumDeps();
	int getType();

};

#endif // EMPLOYEE_H

