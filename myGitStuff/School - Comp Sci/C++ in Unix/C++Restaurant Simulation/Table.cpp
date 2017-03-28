#include "Table.h"

Table::Table()
{
	tableId=0;
	status = IDLE;
	numPeople = 0;
	waiter = NULL;
	maxSeats = 0;
}

Table::Table(const Table& _r)
{
	tableId = _r.tableId;
	status = _r.status;
	numPeople = _r.numPeople;
	order = _r.order;
	waiter = _r.waiter;
	maxSeats = _r.maxSeats;
}
Table& Table::operator =(const Table& _r)
{
	tableId = _r.tableId;
	status = _r.status;
	maxSeats = _r.maxSeats;
	numPeople = _r.numPeople;
	order = _r.order;
	waiter = _r.waiter;
	return *this;	
}
Table::~Table()
{

}
Table::Table(int tblid, int mseats):maxSeats(mseats)	// initialization, IDLE
{
	tableId = tblid;
	status = IDLE;
	numPeople = 0;
	waiter = NULL;
}
void Table::printTable()
{
	cout << "ID: " << tableId << " Status: " << status << " MaxSeats: " << maxSeats << " Num People: " << numPeople;
	if(waiter == NULL)
	{
		cout << " Waiter: NULL "; 
	}
	else
	{
		cout << " Waiter: " << waiter->getName();
	}
	if(order.getNumItems() == 0)
	{
		cout << " Order: NULL";
	}
	else
	{
		cout << " Order: ";
		for(int i = 0; i < order.getNumItems(); i++)
		{
			cout << order.getItemsp()[i]->getCode() << " ";
			
		}

	}
	cout << endl;
}
int Table::getNumber()
{
	return tableId;
}
void Table::setWaiter(Waiter* _waiter)
{
	waiter = _waiter;
}
Waiter* Table::getWaiter()
{
	return waiter;
}
void Table::setNumPeople(int num)
{
	numPeople = num;
}
void Table::setStatus(TableStatus _status)
{
	status = _status;
}
int Table::getNumPeople()
{
	return numPeople;
}
void Table::setOrder(Order& _order)
{
	if(status == SEATED)
	{
		order = _order;
		status = ORDERED;
	}
	else
	{
		cout << "Can not take order of empty party" << endl;
	}
}
Order* Table::getOrder()
{
	return &order;
}
TableStatus Table::getStatus()
{
	return status;
}
