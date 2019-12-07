#ifndef RESTAURANT_H
#define RESTAURANT_H

#include <cstdlib>
#include <iostream>
#include <fstream>
#include "Menu.h"
#include "MenuItem.h"
#include "Order.h"
#include "Waiter.h"
#include "Tokenizer.h"
#include "Table.h"

class Waiter;
class Table;
class Restaurant
{
	private: 
		int numTables;
		Table* tableList; 	//holds official list of tables
		int numWaiters;
		Waiter* waiterList;	//holds official list of waiters
		ifstream configFile;
		ifstream activityFile;
		Menu menu;
	public: 
		Restaurant();
		Restaurant(const Restaurant& _r);
		Restaurant& operator = (const Restaurant& _r);
		~Restaurant();

		void readConfigFile(string _fileName);
		void readActivityFile(string _fileName);
		void copyTableList(int numItems, Table* source);
		void copyWaiterList(int _numWaiters, Waiter* source);
		void printTableList();
		void makeTableList();
		void makeWaiterList();
		void makeMenu();
		void addWaiter(const Waiter& _w);
		void printWaiterList();
		void printMenu();
		void processActivity(Tokenizer& str, int currTableNum);
		void printCheck(int currTableNum);
};
#endif
