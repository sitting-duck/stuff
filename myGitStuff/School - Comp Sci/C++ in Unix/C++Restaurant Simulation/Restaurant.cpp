#include "Restaurant.h"

Restaurant::Restaurant()
{
	numTables = 0;
	tableList = NULL;
	numWaiters = 0;
	waiterList = NULL;
}

Restaurant::Restaurant(const Restaurant& _r)
{
	numTables = _r.numTables;
	copyTableList(numTables, _r.tableList);
	numWaiters = _r.numWaiters;
	copyWaiterList(numWaiters, _r.waiterList);
}

Restaurant& Restaurant::operator =(const Restaurant& _r)
{
	numTables = _r.numTables;
	copyTableList(numTables, _r.tableList);
	numWaiters = _r.numWaiters;
	copyWaiterList(numWaiters, _r.waiterList);
	return *this;
}

Restaurant::~Restaurant()
{
	delete[] waiterList;
	delete[] tableList;
}

void Restaurant::copyTableList(int numItems, Table* source)
{
		delete[] tableList;
		tableList = new Table[numItems];
		for(int i = 0; i < numItems; i++)
		{
			tableList[i] = source[i];
		}
}
void Restaurant::copyWaiterList(int _numWaiters, Waiter* source)
{
		delete[] waiterList;
		waiterList = new Waiter[_numWaiters];
		for(int i = 0; i < _numWaiters; i++)
		{
			waiterList[i] = source[i];
//			for(int j = 0; j < waiterList[i].numTables; j++)
//			{
//				tableList[waiterList[i].getTables()[j]].setWaiter(&waiterList[i]);
//			}
		}
}

void Restaurant::readConfigFile(string _fileName)
{
	configFile.open(_fileName);
	if(!configFile.is_open())
	{
		cout << "Was unable to open file." <<endl;
		exit(0);
	}
	makeTableList();
	makeWaiterList();	
	makeMenu();	
	
	
	configFile.close();
}
void Restaurant::readActivityFile(string _fileName)
{
	int currTableNum;
	Tokenizer str("", " ");
	string input;
	string token;
	activityFile.open(_fileName);
	if(!activityFile.is_open())
	{
		cout << "Was unable to open file." << endl;
		exit(0);
	}
	getline(activityFile, input);
	while(!activityFile.eof())
	{
		str.setString(input);

		token = str.next();
		token.erase(0,1);
		currTableNum = atoi(token.c_str());

		processActivity(str, currTableNum);

		input.assign("");
		getline(activityFile, input);
	}



	activityFile.close();
}

void Restaurant::processActivity(Tokenizer& str, int currTableNum)
{
	string token;
	token = str.next();
	switch(token[0])
	{
		case 'P':
		{
			if(tableList[currTableNum-1].getStatus() == IDLE)		
			{
				token.erase(0,1);
				tableList[currTableNum-1].setNumPeople( atoi(token.c_str()));
				tableList[currTableNum-1].setStatus(SEATED); 
			}
			break;
		}
		case 'O': 
		{
			if(tableList[currTableNum-1].getStatus() == SEATED)
			{
				int numTempItems = 0;
				MenuItem* tempItemList[100];
				
				while((token = str.next())!="")
				{
					
					tempItemList[numTempItems] = menu.findItem(token);
					numTempItems++;
				}
				MenuItem** sizedTempItemList = new MenuItem*[numTempItems];
				for(int i = 0; i < numTempItems; i++)
				{
					sizedTempItemList[i] = tempItemList[i];
					tempItemList[i] = NULL;
				}
				Order tempOrder(numTempItems, sizedTempItemList);
				delete[] sizedTempItemList;
				tableList[currTableNum-1].setOrder(tempOrder);
				tableList[currTableNum-1].setStatus(ORDERED);
			}
			break;
		}
		case 'S':
		{
			if(tableList[currTableNum-1].getStatus() == ORDERED)
			{
				tableList[currTableNum-1].setStatus(SERVED);
			}
			break;
		}
		case 'C':
		{
			if(tableList[currTableNum-1].getStatus() == SERVED)
			{
				printCheck(currTableNum);
			}
			break;
		}
		default:
		{
			cout << "Invalid input" << endl;
		}
	}
}

void Restaurant::printTableList()
{
	for(int i =0; i < numTables; i++)
	{
		tableList[i].printTable();
	}
}

void Restaurant::makeTableList()
{	
	string input;
	string token;
	int tableNum;
	int numSeats;
	int tempTableIds[100] = {0};
	int tempNumSeats[100] = {0};
	Table* tempTableList;
	int numTempTables = 0;
	Tokenizer str("", " ");
	getline(configFile, input);
	while(input.compare("Waiters:")!= 0)
	{
		if(input.compare("Tables:")==0 || input.size()== 0)
		{
			input.assign("");
			getline(configFile, input);
			continue;
		}
		str.setString(input);
		token = str.next();
		tableNum = atoi(token.c_str());
		tempTableIds[numTempTables] = tableNum;
		token = str.next();
		numSeats = atoi(token.c_str());
		tempNumSeats[numTempTables] = numSeats;
		numTempTables++;
		input.assign("");
		getline(configFile, input);
	}
	tempTableList = new Table[numTempTables];
	for(int i = 0; i < numTempTables; i++)
	{
		Table tempTable(tempTableIds[i], tempNumSeats[i]);
		tempTableList[i] = tempTable;
	}
	numTables = numTempTables;
	copyTableList(numTempTables, tempTableList);
	delete[] tempTableList;

}
void Restaurant::printCheck(int currTableNum)
{
	cout << "Table #" << currTableNum << " Check" << endl;
	cout << "Waiter: " << tableList[currTableNum-1].getWaiter()->getName();
	cout << " Party Size: " << tableList[currTableNum-1].getNumPeople();
	tableList[currTableNum-1].getOrder()->printOrder();
	tableList[currTableNum-1].setStatus(IDLE);
}	
void Restaurant::makeWaiterList()
{
	string input;
	string token;
	string tempName;
	int tempTableNumList[100] = {0};
	int numTempTables = 0;
	Table** tempTables = NULL;


	Tokenizer str("", " ");

	getline(configFile, input);
	while(input.compare("Menu:") != 0)
	{
		if(input.size() == 0)
		{
			input.assign("");
			getline(configFile, input);
			continue;
		}
		str.setString(input);
		token = str.next();
		tempName = token;
		while((token = str.next())!= "")
		{
			tempTableNumList[numTempTables] = atoi(token.c_str());
			numTempTables++;
		}
		tempTables = new Table*[numTempTables];

		for(int i = 0; i < numTempTables; i++)
		{
			tempTables[i] = &tableList[tempTableNumList[i]-1];
			 tempTableNumList[i] = 0;
		}
		Waiter tempWaiter(tempName, numTempTables, tempTables);
		addWaiter(tempWaiter);


		input.assign("");
		getline(configFile, input);
		delete[] tempTables;
		numTempTables = 0;

	}
	Waiter* addrInWaiters = NULL;
	for(int j = 0; j < numWaiters; j++)
	{
		for(int i = 0; i < waiterList[j].getNumTables(); i++)
		{
			addrInWaiters = &waiterList[j];
			tableList[waiterList[j].getTables()[i]->getNumber()-1].setWaiter(addrInWaiters);
		}
	}	
}
void Restaurant::addWaiter(const Waiter& _r)
{

	Waiter* tempWaiterList = new Waiter[numWaiters+1];
	for(int i = 0; i < numWaiters; i++)
	{
		tempWaiterList[i] = waiterList[i];
	}
	delete[] waiterList;
	waiterList = new Waiter[numWaiters+1];
	copyWaiterList(numWaiters+1, tempWaiterList);
	delete[] tempWaiterList;
	waiterList[numWaiters] = _r;

//	for(int j = 0; j < waiterList[numWaiters].numTables; j++)
//	{
//		
//		tableList[waiterList[numWaiters].getTables()[j]].setWaiter(&waiterList[i]);
//	}

	numWaiters++;

}
void Restaurant::printWaiterList()
{
	for(int i = 0; i < numWaiters; i++)
	{
		waiterList[i].printWaiter();
	}
}
void Restaurant::makeMenu()
{
	string input;
	string token;
	Tokenizer str("", " ");
	string code;
	string name;
	double price;
	
	getline(configFile, input);
	while(!configFile.eof())
	{
		if(input.size() == 0)
		{
			input.assign("");
			getline(configFile,input);
			continue;
		}
		str.setString(input);
		token = str.next();
		code = token;
		token = str.next();
		name = token;
		token = str.next();
		price = atof(token.c_str());
		

		MenuItem tempItem(code, name, price);
		menu.addItem(tempItem);

		input.assign("");
		getline(configFile, input);
	}

}
void Restaurant::printMenu()
{
	menu.printMenu();
}
