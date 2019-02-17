#ifndef PAYCHECK_H
#define PAYCHECK_H

#include "Employee.h"

struct PayCheck {
	Employee employee;
	int numberHoursWorked;

	PayCheck(Employee _employee, int _numberHoursWorked) {
		employee = _employee;
		numberHoursWorked = _numberHoursWorked;
	}

	~PayCheck() {}
};

#endif
