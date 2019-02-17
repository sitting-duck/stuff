#include "Employee.h"

Employee::Employee(int initId, string initName,
	double initHourlyPay,
	int initNumDeps, int initType)
{
	bool status = set(initId, initName, initHourlyPay,
		initNumDeps, initType);
	if (!status)
	{
		id = 0;
		name = "";
		hourlyPay = 0.0;
		numDeps = 0;
		type = 0;
	}
}

int Employee::getId()
{
	return id;
}

string Employee::getName()
{
	return name;
}

double Employee::getHourlyPay()
{
	return hourlyPay;
}

int Employee::getNumDeps()
{
	return numDeps;
}

int Employee::getType()
{
	return type;
}

bool Employee::set(int newId, string newName, double newHourlyPay,
	int newNumDeps, int newType)
{
	bool status = false;
	if (newId > 0 && newHourlyPay > 0 && newNumDeps >= 0 &&
		newType >= 0 && newType <= 1)
	{
		status = true;
		id = newId;
		name = newName;
		hourlyPay = newHourlyPay;
		numDeps = newNumDeps;
		type = newType;
	}
	return status;

}