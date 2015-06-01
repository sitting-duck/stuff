#include <iostream>
#include <limits.h>
#include <memory.h>
#include <fstream>
#include "UBArray.h"
#include "ReadString.h"

using namespace std;

const	int		MaxNodes	(12);

int GetInteger();
int GetNumNodes();
char GetNode(int); 	
int GetCost(int ,int[MaxNodes][MaxNodes]);
void SetCost(int, int[MaxNodes][MaxNodes]);
int GetCostNodesKnown(char, char, int[MaxNodes][MaxNodes]);
void SetCostNodesKnown(char, char, int, int[MaxNodes][MaxNodes]);
void FindMinPath(int, int[MaxNodes][MaxNodes]); //this should maybe return a string
int CalculateCost(int NumNodes, int Cost[MaxNodes][MaxNodes], char* tempPath);
void ReadCostFile(int &NumNodes, int Cost[MaxNodes][MaxNodes]);
void PrintCostGrid(int NumNodes, int Cost[MaxNodes][MaxNodes], int highestcost);


void main()
{
	
		
	//Arrays of stuff		
	int		MinCost		(INT_MAX);
	char	CurrPath	[MaxNodes];
	char	MinPath		[MaxNodes];
	bool	Visited		[MaxNodes];

	int	CostTest[MaxNodes][MaxNodes] = 	
	{
	//		 A   B   C  D  E  F  G  H  I  J   K   L
	/*A*/	{0,  1,  2, 3, 4, 5, 6, 7, 8, 9, 10, 11}, //A
	/*B*/	{1,  0,  1, 2, 3, 4, 5, 6, 7, 8,  9, 10}, //B
	/*C*/	{2,  1,  0, 1, 2, 3, 4, 5, 6, 7,  8, 9 }, //C
	/*D*/	{3,  2,  1, 0, 1, 2, 3, 4, 5, 6,  7, 8 }, //D
	/*E*/	{4,  3,  2, 1, 0, 1, 2, 3, 4, 5,  6, 7 }, //E
	/*F*/	{5,  4,  3, 2, 1, 0, 1, 2, 3, 4,  5, 6 }, //F
	/*G*/	{6,  5,  4, 3, 2, 1, 0, 1, 2, 3,  4, 5 }, //G
	/*H*/	{7,  6,  5, 4, 3, 2, 1, 0, 1, 2,  3, 4 }, //H
	/*I*/	{8,  7,  6, 5, 4, 3, 2, 1, 0, 1,  2, 3 }, //I
	/*J*/	{9,  8,  7, 6, 5, 4, 3, 2, 1, 0,  1, 2 }, //J
	/*K*/	{10, 9,  8, 7, 6, 5, 4, 3, 2, 1,  0, 1 }, //K
	/*L*/	{11, 10, 9, 8, 7, 6, 5, 4, 3, 2,  1, 0 }  //L
	//		 A   B   C  D  E  F  G  H  I  J   K   L
		};

		int	Cost[MaxNodes][MaxNodes] = 	
	{
	//		 A    B   C   D   E   F   G   H   I   J   K   L
	/*A*/	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, //A
	/*B*/	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, //B
	/*C*/	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, //C
	/*D*/	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, //D
	/*E*/	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, //E
	/*F*/	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, //F
	/*G*/	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, //G
	/*H*/	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, //H
	/*I*/	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, //I
	/*J*/	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, //J
	/*K*/	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, //K
	/*L*/	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}  //L
	//		  A   B   C   D   E   F   G   H   I   J   K   L
		};

	int NumNodes;
	int myCost;
	char FirstNode;
	char SecondNode;
	
	cout << "Travellling Saleman Program " << endl << endl;

	//Begin Program Entry Here!////////////////////////////////////////////////////////////
	while(1)
	{
		cout << endl;
		ReadCostFile(NumNodes, Cost);
		FindMinPath(NumNodes, Cost);
		cout << endl;
	}
	///////////////////////////////////////////////////////////////////////////////////////
}

int GetNumNodes()
{
	int NumNodes = 0;
	bool ValidNumNodes = false;
	

	cout << "Please enter the number of nodes in the network." << endl;
	cout << "Can only have a max of 12 nodes and a min of 2 nodes." << endl;	
	while(ValidNumNodes == false)
	{
		NumNodes = GetInteger();

		if(NumNodes >= 2 && NumNodes <= 12)
		{
			ValidNumNodes = true;
			cout << "NumNodes is : " << NumNodes << endl << endl;
		}
		else
		{
			ValidNumNodes = false;
			NumNodes = 0;
			cout << "Invalid Input: Please enter a number 1-12." << endl;
			cout << "NumNodes: " ;
		}
		
	}
	return NumNodes;
}

int GetInteger()
{
	int myInt = 0;
	int place = 0;
	int i = 9999999;

			//getinteger()
		while( (i = cin.get()) != '\n')
		{	
			switch(i)
			{
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
					if(place == 0)
					{
						myInt += (i - '0');
					}
					else
					{
						myInt *= 10;
						myInt += (i - '0');
					}
					break;			
				default:					
					cout << "	Invalid Input." << endl;
					break;
			}
			place++;
		}
		place = 0;//reset place to zero. for fuk sake.

		return myInt;
}

char GetNode(int NumNodes)
{
	bool InputValid = false;
	int i = 99999;
	char Node;
	char LastValidNode = ((NumNodes + 'A') - 1);
	
	cout << "	There are only " << NumNodes << " nodes in your network." << endl;
	cout << "	You may only enter A - " << LastValidNode << endl;
	cout << "	Enter Node: ";

	while(InputValid == false)
	{
		i = cin.get();
		cin.ignore();
		if( (i > 64 && i < ((NumNodes + 'A') - 1)) || (i > 96 && i < ((NumNodes + 'a'))) )
				{
					InputValid = true;					
					Node = toupper(i);
				}
		else
		{	
			cout << "Error: Invalid Input." << endl;
			cout << "There are only " << NumNodes << " nodes in your network." << endl;
			cout << "You may only enter A - " << LastValidNode << endl;
			cout << "Please re-enter your last input, correctly this time:" << endl;
			InputValid = false;
		}
	}
	//for testing
	cout << "You entered: " << Node << endl;
	return Node;

}

int GetCost(int NumNodes, int Cost[12][12])
{
	char cFirstNode = GetNode(NumNodes);
	char cSecondNode = GetNode(NumNodes);
	return GetCostNodesKnown(cFirstNode, cSecondNode, Cost);
}

void SetCost(int NumNodes, int Cost[MaxNodes][MaxNodes])
{
	
	cout << "Enter the path you would like to set the cost for." << endl;
	cout << "You will enter the first node and then the second node." << endl;

	char cFirstNode = GetNode(NumNodes);
	char cSecondNode = GetNode(NumNodes);
	int iFirstNode = cFirstNode - 'A';
	int iSecondNode = cSecondNode - 'A';

	cout << "Please enter the cost of this path: " << endl;
	int myCost = GetInteger();
	Cost[iFirstNode][iSecondNode] = myCost;
	
}

int GetCostNodesKnown(char FirstNode, char SecondNode, int Cost[12][12])
{
	int iFirstNode = FirstNode - 'A';
	int iSecondNode = SecondNode - 'A';

	int tempcost = Cost[iFirstNode][iSecondNode];
	cout << "Cost is: " << tempcost << endl;;
	return tempcost;
}

void SetCostNodesKnown(char FirstNode, char SecondNode, int NumNodes, int Cost[MaxNodes][MaxNodes])
{
	
	int iFirstNode = FirstNode - 'A';
	int iSecondNode = SecondNode - 'A';

	cout << "Please enter the cost of this path: " << endl;
	int myCost = GetInteger();
	Cost[iFirstNode][iSecondNode] = myCost;
	
}

void FindMinPath(int NumNodes, int Cost[MaxNodes][MaxNodes])
{
	fstream myFile;
	
	switch(NumNodes) //what a clooj...
	{
		case 2:
			myFile.open("2.txt", ios_base::in);
			break;
		case 3:
			myFile.open("3.txt", ios_base::in);
			break;
		case 4:
			myFile.open("4.txt", ios_base::in);
			break;
		case 5:
			myFile.open("5.txt", ios_base::in);
			break;
		case 6:
			myFile.open("6.txt", ios_base::in);
			break;
		case 7:
			myFile.open("7.txt", ios_base::in);
			break;
		case 8:
			myFile.open("8.txt", ios_base::in);
			break;
		case 9:
			myFile.open("9.txt", ios_base::in);
			break;
		case 10:
			myFile.open("10.txt", ios_base::in);
			break;
		case 11:
			myFile.open("11.txt", ios_base::in);
			break;
		case 12:
			myFile.open("12.txt", ios_base::in);
			break;
		default:
			cout << "what the hell is going on here?" << endl;
			break;
	}

	char* tempPath = new char[NumNodes + 1];
	char* CheapestPath = new char[NumNodes + 1];

	//get length of file
	myFile.seekg(0, ios::end);
	int lengthOfFile = myFile.tellg();
	int LowestCost = 99999;
	myFile.seekg(0, ios::beg);
	bool iseof = false;
	//allocate memory
	//char* buffer = new char[lengthOfFile];
	//myFile.read(buffer, lengthOfFile);

	//for(int i = 1; myFile.tellg() <= lengthOfFile; i++)
	for(int i = 1; iseof != true; i++)
	{		
		myFile.read(tempPath, NumNodes + 1);
		iseof = myFile.eof();
		if(iseof)
			break;
		//myFile.seekg((NumNodes + 1)*i );
		tempPath[NumNodes] = '\0';
		//cout << tempPath << endl;				
		int tempCost = CalculateCost(NumNodes, Cost, tempPath);
		if(tempCost == -1)
		{
			cout << "Invalid Path." << endl;
		}
		else
		if(tempCost < LowestCost)
		{
			LowestCost = tempCost;
			strcpy(CheapestPath, tempPath);
		}

	}
	myFile.close();

	if(LowestCost == 99999)
	{
		cout << endl << "No cheapest path found." << endl;
	}
	else
	{
		cout << endl << "Cheapest Path is: " << CheapestPath << endl;
		cout << "with a cost of: $" <<LowestCost << endl; 
	}
	
		
	delete [] tempPath;
	delete [] CheapestPath;	

}

int CalculateCost(int NumNodes, int Cost[MaxNodes][MaxNodes], char* tempPath)
{
	int tempCost = 0;
	int row;
	int column;

	for(int i = 0; i < NumNodes - 1; i++)
	{
		row = tempPath[i] - 'A';
		column = tempPath[i + 1] - 'A';
		
		if(Cost[row][column] == -1)
		{		
			return -1;
		}
		else
		{
			tempCost += Cost[row][column];
		}
	}
	
	return tempCost;
}

void ReadCostFile(int &NumNodes, int Cost[MaxNodes][MaxNodes])
{
	bool iseof = false;
	fstream myfile;
	cout << "Please enter the name of the file you would like to open.:";
	char* filename = ReadString();

	myfile.open(filename, ios_base::in);

	while(!myfile.is_open())
	{
		cout << "Could not open file. Please try again:";
		filename = ReadString();
		myfile.clear();
		myfile.open(filename, ios_base::in);
	}

	char cNumNodes[2];
	int fp = 0;
	//myfile.seekg(0, ios_base::end);
	//int lengthoffile = myfile.tellg();
	//char* buffer = new char[lengthoffile];
	
	//myfile.seekg(0, ios_base::beg);
	//myfile.read(buffer, lengthoffile);

	//cout.write(buffer, lengthoffile);

	//for(int i = 1; buffer[i] != '\n'; i++)
	//{
	//
	//}

	myfile.seekg(0);
	myfile.read(cNumNodes, 2);
	if(cNumNodes[0] >= '2' && cNumNodes[0] <= '9')
	{
		NumNodes = cNumNodes[0] - '0';
		fp = 3;
	}
	if(cNumNodes[1] == '0')
	{
		NumNodes = 10;
		fp = 4;
	}
	if(cNumNodes[1] == '1')
	{
		NumNodes = 11;
		fp= 4;
	}
	if(cNumNodes[1] == '2')
	{
		NumNodes = 12;
		fp= 4;
	}


	cout << "NumNodes: " << NumNodes << endl;

	int row;
	char cRow[2];
	int column;
	char cColumn[2];
	int costofjump;
	char ccostofjump[10] = {'\0'};
	int highestcost = 0;
	
	while(!iseof)
	{
		myfile.seekg(fp);
		myfile.read(cRow, 1);
		cRow[1] = '\0';
		fp+=2;
		myfile.seekg(fp);
		myfile.read(cColumn, 1);
		cColumn[1] = '\0';
		row = cRow[0] - 'A';
		column = cColumn[0] - 'A';
		fp+=2;
		myfile.seekg(fp);
		myfile.read(ccostofjump, 1);
		costofjump = ccostofjump[0] - '0';
		for(int i = 1; ccostofjump[i-1] != '\n'; i++)
		{
			myfile.read(&ccostofjump[i], 1);
			if(ccostofjump[i] != '\n')
			{
				costofjump *= 10;
				costofjump += (ccostofjump[i] - '0');	
				if(costofjump > highestcost)
				{
					highestcost = costofjump;
				}
			}

		}
		fp = myfile.tellg();

		//for testing
		//cout << endl;
		//cout << "Row " << cRow << " = " << row << endl;
		//cout << "Column " << cColumn << " = " << column << endl;
		//cout << "Cost of jump is: " << costofjump << endl;
		//cout << endl;

		Cost[row][column] = costofjump;

		iseof = myfile.eof();
	}
	//PrintCostGrid(NumNodes, Cost, highestcost);
	
}

void PrintCostGrid(int NumNodes, int Cost[MaxNodes][MaxNodes], int highestcost) // good enough for now damnit
{
	int places = 0;
	if(highestcost >= 0 && highestcost < 10)
	{
		places = 1;
	}
	if( (highestcost == -1) || ( highestcost > 10 && highestcost < 100 ) )
	{
		places = 2;
	}
	if(highestcost > 99 && highestcost < 1000)
	{
		places = 3;
	}

	for(int j = 0; j < NumNodes; j++)
	{
		for(int i = 0; i < NumNodes; i++)
		{
			if(places == 3)
				cout << Cost[j][i] << " " ;
			if(places == 2)
				cout << Cost[j][i] << "  " ;
			if(places == 1)
				cout << Cost[j][i] << "   " ;
		}
		cout << endl;
	}
}