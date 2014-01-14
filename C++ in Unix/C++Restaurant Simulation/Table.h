#ifndef TABLE_H
#define TABLE_H
#include "Order.h"
#include "Waiter.h"

enum TableStatus { IDLE, SEATED, ORDERED, SERVED };

class Waiter; // to take care of circular reference.

class Table 
{
private:
	int tableId;		// table number
	int maxSeats;	// table seat capacity
	TableStatus status;	// current status, you can use assign like
				// status = IDLE;
	int numPeople;		// number of people in current party
	Order order;		// current party's order
	Waiter *waiter;		// pointer to waiter for this table

public:
	Table();
	Table(int tblid, int mseats);	// initialization, IDLE
	Table(const Table& _r);
	Table& operator =(const Table& _r);
	~Table();
	void assignWaiter(Waiter *person); 	// initially no waiter
	void partySeated(int npeople);		// process IDLE --> SEATED
	void partyOrdered(Order *order);	// process SEATED --> ORDERED
	void partyServed(void);			// process ORDERED --> SERVED
	void partyCheckout(void);		// process SERVED --> IDLE
	void printTable();
	int getNumber();
	void setWaiter(Waiter* _waiter);
	Waiter* getWaiter();
	void setNumPeople(int num);
	void setStatus(TableStatus _status);
	int getNumPeople();
	void setOrder(Order& _order);
	TableStatus getStatus();
	Order* getOrder();
};
#endif
