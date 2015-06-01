#include "Waiter.h"

Waiter::Waiter()
{
	name = "";
	numTables = 0;
	tables = NULL;
}
Waiter::Waiter(string _name, int _numTables, Table** _tables)
{
	name = _name;
	numTables = _numTables;
	copyTableList(numTables, _tables);
	
}
Waiter::Waiter(const Waiter& _w)
{
	name = _w.name;
	numTables = _w.numTables;
	copyTableList(numTables, _w.tables);
}
Waiter& Waiter::operator =(const Waiter& _w)
{
	name = _w.name;
	numTables = _w.numTables;
	copyTableList(numTables, _w.tables);
	return *this;
}
Waiter::~Waiter()
{
	delete[] tables;
}

void Waiter::copyTableList(int _numTables, Table** _source)
{
		//delete [] tables;
		tables = new Table*[_numTables];
		for(int i = 0; i<_numTables; i++)
		{
			tables[i] = _source[i];
		}
}
void Waiter::printWaiter()
{
	cout << name << " Tables: ";
	for(int i = 0; i < numTables; i++)
	{
		cout << tables[i]->getNumber() << " ";
	}
	cout << endl;
}

string Waiter::getName()
{
	return name;
}
Table** Waiter::getTables()
{
	return tables;
}
int Waiter::getNumTables()
{
	return numTables;
}
