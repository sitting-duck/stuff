#include "Restaurant.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
	string configFile = "config.txt";
	string activityFile = "activity.txt";
	Restaurant restaurant;
	restaurant.readConfigFile(configFile);
//	restaurant.printWaiterList();
//	restaurant.printMenu();

	restaurant.readActivityFile(activityFile);

	restaurant.printTableList();	

	return 0;
}
