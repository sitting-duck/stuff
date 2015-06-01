#ifndef WAITER_H
#define WAITER_H
#include <string>
#include "Table.h"


class Table; // to take care of circular reference.

class Waiter
{
private:
	string name;	// waiter's name
	int numTables;	// number of tables waiter is in-charge for
	Table** tables;	// waiter's table list

public:
	Waiter();
	Waiter(string _name, int _numTables, Table** _tables);
	Waiter(string name, string TableList, Table *table); 
	Waiter(const Waiter& _w);
	Waiter& operator =(const Waiter& _w);
	~Waiter();
	// waiter's name, his table list as a string, table array pointer
	void copyTableList(int _numTables, Table** _source);
	void printWaiter();
	string getName();
	Table** getTables();
	int getNumTables();

};

#endif
