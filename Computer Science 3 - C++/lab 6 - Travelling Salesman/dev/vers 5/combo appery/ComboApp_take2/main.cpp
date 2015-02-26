#include <iostream> 
#include <fstream>
#include<string>

using namespace std;



void main()
{
	fstream myFile;
	myFile.open("12.txt", ios::out );

	int numNodes;
	cout << "How many nodes? : " ;
	cin >> numNodes;

	char* tempList = new char[numNodes + 1];
	
	tempList[numNodes] = '\0';

	for(int i = 0; i < numNodes; i++)
	{
		tempList[i] = 'A' + i;
	}

	cout << "Original temp List: " << tempList << endl << endl;
	myFile.write(tempList, numNodes);
	myFile.write("\n", 1);
	
	//scramble temp list.
		//first move over one until original pattern is back
	//myFile.write(tempList, numNodes + 1);

	char tempChar;
	
	char* originalTempList = new char[numNodes + 1];
	
	strcpy(originalTempList, tempList);
	

	do
	{
		for(int i = 0; tempList[i] != '\0'; i++)
		{
			tempChar = tempList[i+1];
			if(tempChar == '\0')
			{
				//tempList[0] = tempList[i+1];
				break;
			}		
			tempList[i+1] = tempList[i];
			tempList[i] = tempChar;
			
			if(strcmp(originalTempList, tempList) != 0)
			{
				cout << tempList << endl;	
				myFile.write(tempList, numNodes);
				myFile.write("\n", 1);
			}		
		}
		
	}
	while(( strcmp(originalTempList, tempList) != 0 ));

	myFile.close();

}