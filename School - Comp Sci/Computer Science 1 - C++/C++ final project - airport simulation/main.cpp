#include <iostream>

using namespace std;

#include <string.h>
#include "Party.h"
#include "PartyList.h"
#include "Plane.h"
#include "ReadFunctions.h"
#include "ReadString.h"
#include "TokenizedCommand.h"
//#include <cctype>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <cstring>

#define uint unsigned int
#define sint short int//look

//void MovePartiesToPlane (Plane &, Plane &);
void UpperCase(char*);
char* GetUserInput(void);
void Initialize(TokenizedCommand* myTCPtr);
bool Arrive(TokenizedCommand* myTCPtr);
bool AddToPartyList(TokenizedCommand* myTCPtr);
bool GetUnsignedInt(char*, unsigned int*);
void Initialize(Plane* myPlane, uint numOfSeats, char* name);
TokenizedCommand* Tokenize(char*);
void Fly(Plane* myPlanePtr);
PartyList* InitPartyList();
Plane* GetPlane(char* whichPlane);
void displayPlane(Plane* planePtr);
void displayPartylist(PartyList* partylistPtr);
void displayParty(Party* partyPtr);
void ResetParty(Party* partyPtr);
void ResetPartyList(PartyList* partyListPtr);
void ResetPlane(Plane* planePtr);
void ShowParty(Party* partyPtr);
void ShowPartylist(PartyList* partylistPtr);
void ShowPlane(Plane* planePtr);
void ShutDown();
void copyString(char** destination, char* source);

Plane	ALPHA;
Plane	BRAVO;
Plane	LOUNGE;

//#define PLANE_NAME_ARRAY_SIZE 7

void main ()
{
	char*	Command = NULL;
	int 	Number  = 0;
	uint myUint = 0;  
	uint* myUnsignedIntPtr = &myUint; 
	char PlaneName[7];
	Plane* myPlane = NULL;
	bool shutdown = false;

//	read in command
	do
	{
		myPlane = NULL;				// clear out the prev plane
		memset(PlaneName, '\0', (uint)7);

		cout << "Enter a command: ";

		// Function call to accept user input
		Command = GetUserInput();

		// if the user has entered a command of strlen 0, continue
		if(strlen(Command) == 0)
		{
			free(Command);
			Command = NULL;
			continue;
		}

		UpperCase(Command);

		TokenizedCommand* myTCPtr = Tokenize(Command);
		

		if( (strncmp(myTCPtr->first, "ALPHA",  5)) == 0 || 
			(strncmp(myTCPtr->first, "BRAVO",  5)) == 0 || 
			(strncmp(myTCPtr->first, "LOUNGE", 6)) == 0	  )
		{
			uint NumSeats = 0;
			strncpy(PlaneName, myTCPtr->first, 
				strlen(myTCPtr->first));
			GetUnsignedInt(myTCPtr->second, &NumSeats);
			if(myTCPtr->second == NULL || 
				(!GetUnsignedInt(myTCPtr->second, &NumSeats)))
			{
				cout << "Invalid Command. Syntax is " 
					 << "<plane|lounge> <numOfSeats>" << endl;	
			}
			else
			{			
				Plane* myPlane = GetPlane(myTCPtr->first);
				Initialize(myPlane, NumSeats, PlaneName);
			}
		}
		else if(strncmp(myTCPtr->first, "ARRIVE", 6) == 0)
		{
			if(myTCPtr->fourth == NULL||
			   myTCPtr->third == NULL || 
			   myTCPtr->second == NULL )
			{
				cout << "Invalid Command.  Syntax is: ARRIVE <plane> ";
				cout << "<party name> <num people>" << endl;
			}
			else
			{
				if(LOUNGE.Initialized)
				{
					if((strncmp(myTCPtr->second, "ALPHA", 5)||
					   strncmp(myTCPtr->second, "BRAVO", 5))&&
					   strlen(myTCPtr->second) == 5)
					   {
							cout << "Call Arrive here" << endl;
							if(Arrive(myTCPtr))
							{
								cout << "Arrive succesful." << endl;
							}
							else
							{
								cout << "Illegal Arrival." << endl;
							}
						}
						else
						{
							cout << "The plane name must be Alpha"
							     << " or Bravo." << endl;
						}
				}
				else
				{
					cout << "You don't have a lounge. Where will you"
						 << " move the people? Initialize lounge first."
						 << endl;
				}	
			}	
		}
		else if(strncmp(myTCPtr->first, "FLY", 3)  == 0)
		{
			if(myTCPtr->second == NULL)
			{
				cout << "Invalid Command.  Syntax is: FLY <plane>"
				     << endl;
			}
			else
			{
				if((strncmp(myTCPtr->second, "ALPHA", 5)||
					   strncmp(myTCPtr->second, "BRAVO", 5))&&
					   strlen(myTCPtr->second) == 5)
				{
					cout << "Call Fly here" << endl;
					if(GetPlane(myTCPtr->second)->Initialized)
					{
						Fly(GetPlane(myTCPtr->second));
						cout << "Fly succesful." << endl;
					}
					else
					{
						cout << "You can't fly an uninitialized plane!" << endl;
					}
				}
				else
				{
					cout << "The plane name must be Alpha"
						 << " or Bravo." << endl;
				}	
			}
		}
		else if(strncmp(myTCPtr->first, "SHUTDOWN", 8) == 0 )
		{
			cout << "Call Shutdown here" << endl;
			ShutDown();
			shutdown = true;
		}
		else
		{
			cout << "Invalid Command" << endl;
		}		

		//free TCPtr

		free(myTCPtr->first);
		myTCPtr->first = NULL;
		free(myTCPtr->second);
		myTCPtr->second = NULL;
		free(myTCPtr->third);
		myTCPtr->third = NULL;
		free(myTCPtr->fourth);
		myTCPtr->fourth = NULL;
		free(myTCPtr);
		myTCPtr = NULL;	

		free(Command);
		Command = NULL;
	
	} while(!shutdown);
}

/*void MovePartiesToPlane (Plane & To, Plane & From)
	{
	int	i;
	int	j;
	bool	DoneMoving;
//	to remove people from lounge
	DoneMoving = false;
	while (!DoneMoving)
		{
		DoneMoving = true;
		for (i = 0; i < From.NumParties; i++)
			if (From.PartyList [i].NumPeople <= To.AvailSeats)
					{
					To.PartyList [To.NumParties] = From.PartyList [i];
					To.NumParties++;
					To.AvailSeats	-= From.PartyList [i].NumPeople;
					From.AvailSeats	+= From.PartyList [i].NumPeople;
					for (j = i; j < From.NumParties; j++)
						From.PartyList [j] = From.PartyList [j + 1];
					From.NumParties--;
					i--;
					}
				else;
		}
	}
*/


void UpperCase(char* Command)
	{
	for(unsigned int i=0; i<(strlen(Command)); i++)
		{
		//putchar(toupper(Command[i]));
		Command[i] = toupper(Command[i]);
		}
	}



char* GetUserInput(void)
	{//basically, if it's not a tab or a space, and we don't need more memory, 
	 //put tmpChar the proper distance from the pointer
		char *myTempCharPtr = NULL;
		uint InitialSize = 5;
		uint Increment = 5;
		uint CurrentSize = InitialSize;
		char tmpChar = '\0';
		bool whitespaceEncountered = false;
		uint CurrentPos = 0;
		
		if( (myTempCharPtr = (char*) calloc(InitialSize,1)) == NULL)// == evaluates before =
			{
				cout << "Memory Allocation Error. Process Aborting." << endl;
				exit(0);
			}

		while ((tmpChar = cin.get()) != 10)//while cin.get != enter/line feed character
			{
				// Skip all the whitespaces at the beginning
				if(tmpChar == ' ' || tmpChar == '\t')
					{
						whitespaceEncountered = true;
						continue;
					}

				// Ensure we have room to write
				if (CurrentPos >= (CurrentSize-1))
					{
						// We need to allocate more space
						uint NewSize = CurrentSize + Increment;
						char* pStr = new char [NewSize];
						memset(pStr, '\0', NewSize);
						
						memcpy(pStr, myTempCharPtr, CurrentSize);
						delete [] myTempCharPtr;
						myTempCharPtr = pStr;
						CurrentSize = NewSize;
					}


				// Write a space for whitespaces encountered, except at the start
				if (whitespaceEncountered)
					{
						whitespaceEncountered = false;						
						if(CurrentPos != 0)
						{
							myTempCharPtr[CurrentPos] = ' ';
							CurrentPos++;//move to next space
						}
					}
				
				myTempCharPtr[CurrentPos] = tmpChar;//and put the next letter in
				CurrentPos++;
			}

		return myTempCharPtr;

	}
void Initialize(Plane* myPlane, uint numOfSeats, char* name)
{

	if(myPlane->NumParties)
	{
		cout << "The parties need to be 0 to re-initialize." << endl;
	}
	else
	{
		myPlane->Initialized = true;
		myPlane->AvailSeats = numOfSeats;
		myPlane->NumSeats = numOfSeats;
		myPlane->NumParties = 0;
		myPlane->myPartyList = InitPartyList();
		uint NumSeats = 0;
		strncpy(&(myPlane->PlaneId), name, 1); //check this 
		strncpy(myPlane->PlaneName, name, 5);
		myPlane->PlaneName[5] = '\0';
		cout << "Initialized " << name << " with " 
			 << myPlane->NumSeats << endl;		
	}				
}



PartyList* InitPartyList()
{
	PartyList* myTempPL = new PartyList;
	uint InitialSize = 50;

	myTempPL->myParties = new Party[InitialSize];
	myTempPL->Size = InitialSize;
	myTempPL->Pos = 0;

	for(int i = 0; i<50;i++)
	{
		myTempPL->myParties[i].NumPeople = 0;
		myTempPL->myParties[i].DesiredPlane = 'X';
		myTempPL->myParties[i].pName = NULL;
	}

	return myTempPL;
}



bool Arrive(TokenizedCommand* myTCPtr)
{
	return AddToPartyList(myTCPtr);		
}



//void SendToLounge(TokenizedCommand* myTCPtr)
void SendToLounge(TokenizedCommand* myTCPtr)
{
	Plane* myLoungePtr = &LOUNGE;
	unsigned int numOfPeople;

	GetUnsignedInt(myTCPtr->fourth, &numOfPeople);

	if(numOfPeople > myLoungePtr->NumSeats)
		{
		cout<<"Party is too big to fit in the lounge.";
		cout<<" Send them home."<<endl;
		}
	else
	{
		uint myPos = myLoungePtr->myPartyList->Pos;

		if(myPos > myLoungePtr->myPartyList->Size)
		{
			cout << "The party list array cannot accomodate this." << endl ;
			exit(2);
		}

		// Test to see if the plane can accomodate the party size
		if(numOfPeople <= myLoungePtr->AvailSeats)
		{

			Party *myParty = &(myLoungePtr->myPartyList->myParties[myPos]);
			myLoungePtr->myPartyList->Pos++;
			
			// Assign the first char of the plane's name to party desired plane
			strncpy(&(myParty->DesiredPlane), myTCPtr->second, 1);

			// Assign the party name
			copyString(&(myParty->pName), myTCPtr->third);

			// Assign the number of people to the party
			myParty->NumPeople = numOfPeople;
			
			myLoungePtr->AvailSeats -= numOfPeople;
			myLoungePtr->NumParties++;

		}
		
	}		
}


bool GetUnsignedInt(char* strIn, unsigned int* myUnsignedInt)
{
	*myUnsignedInt = 0; //in case of failure nothing need be done
	bool ConversionWorkedSoFar = true; //assuming success until failure
	unsigned int lenOfStr = 0;
	unsigned int currentPos = 0;
	unsigned int multiplier = 1;

	if(strIn != NULL)
	{
		lenOfStr = strlen(strIn);
		currentPos = lenOfStr - 1;
		
		if(lenOfStr > 9)
		{
			cout << "The max acceptable number is 999999999" << endl;
			ConversionWorkedSoFar = false;
		}  
	}
	else 
	{
		ConversionWorkedSoFar = false;
	}
	
	if(!(strIn[currentPos] >= '0' && strIn[currentPos] <= '9'))
	{
		ConversionWorkedSoFar = false;
	}
		
	while(ConversionWorkedSoFar && currentPos> 0)
	{
		if(strIn[currentPos] >= '0' && strIn[currentPos] <= '9')
		{
			*myUnsignedInt += (multiplier *(strIn[currentPos] - '0')); //
			multiplier *= 10;
			currentPos--;
		}
		else 
		{
			*myUnsignedInt = 0;
			ConversionWorkedSoFar = false;
		}
	}//end og the while loop

	if(ConversionWorkedSoFar)
	{
		*myUnsignedInt += (multiplier *(strIn[currentPos] - '0')); //
	}
	else 
	{
		*myUnsignedInt = 0;
	}

	return ConversionWorkedSoFar;

}


/********************************************************************
* Function Name: InitializeTC										*
* This function sets all the pointers to null for					*
* the TokenizedCommand struct.										*
* This needs to be called after a new TokenizedCommand is			*
* instantiated, therefore, it is used as the initialization routine	*
********************************************************************/
void InitializeTC(TokenizedCommand* myTC)
{
	myTC->first		= NULL;
	myTC->second	= NULL;
	myTC->third		= NULL;
	myTC->fourth    = NULL;
	myTC->remaining = NULL;
}


TokenizedCommand* Tokenize(char* Command)
{
	TokenizedCommand* myTC = new TokenizedCommand; //we will return this l8r
	InitializeTC(myTC);

	char* token = NULL;
	char* context = NULL;	
	
	//basically putting all the little tokens into the struct, 
	//kind of using the struct as if it were an array
	token = strtok_s(Command, " \n\t", &context);
	copyString(&(myTC->first), token);
	
	token = strtok_s(NULL, " \n\t", &context); //after the first token, starting point is null
	copyString(&(myTC->second), token);
		
	token = strtok_s(NULL, " \n\t", &context);
	copyString(&(myTC->third), token);
		
	token = strtok_s(NULL, " \n\t", &context);
	copyString(&(myTC->fourth), token);

	token = strtok_s(NULL, " \n\t", &context);
	copyString(&(myTC->remaining), token);

	return myTC;
	
}

void copyString(char** destination, char* source)
{
	*destination = NULL;
	
	if(source != NULL)
	{
		if((*destination = (char*) calloc(strlen(source)+1,1)) == NULL)
		{
			cout << "Out of memory in CopyString" << endl;
			exit(3);
		}
		strncpy(*destination,source,strlen(source));
	}
}



bool AddToPartyList(TokenizedCommand* myTCPtr)
{
	Plane* myPlanePtr = NULL;
	unsigned int numOfPeople = 0;
	bool isValid = true;

	//assigning which plane
	myPlanePtr = GetPlane(&(myTCPtr->second[0]));
	if(!myPlanePtr->Initialized)
	{
		cout << "This plane has not been initialized." 
		     << " Cannot accept arrivals for it."
		     << endl;
		isValid = false;
	}
	else if(!GetUnsignedInt(myTCPtr->fourth, &numOfPeople))
	{
		cout << "The fourth parameter to ARRIVE needs to be an integer."
			 << endl;
		isValid = false;
	}
	else if(numOfPeople > myPlanePtr->NumSeats)
		{
		cout << "Party is too big to fit on the plane."
		     << " Send them home." << endl;
		}
	else
	{
		uint myPos = myPlanePtr->myPartyList->Pos;

		if(myPos > myPlanePtr->myPartyList->Size)
		{
			cout << "The party list array cannot accomodate this." << endl ;
			exit(2);
		}


		// Test to see if the plane can accomodate the party size
		if(numOfPeople <= myPlanePtr->AvailSeats)
		{
			Party *myParty = &(myPlanePtr->myPartyList->myParties[myPos]);
			myPlanePtr->myPartyList->Pos++;
			
			// Assign the first char of the plane's name to party desired plane
			strncpy(&(myParty->DesiredPlane), myTCPtr->second, 1);

			// Assign the party name
			char* myName;
/*			int i = 0;
			while(myTCPtr->third[i] != '\0')
			{
			i++;
			}
			myName = (char*)calloc((i+1), 1);
			memcpy(myName, myTCPtr->third, i); //this right here is the problem
			myParty->pName = myName;
*/			
			copyString(&(myParty->pName), myTCPtr->third);
			

			// Assign the number of people to the party
			myParty->NumPeople = numOfPeople;

			myPlanePtr->AvailSeats -= numOfPeople;
			myPlanePtr->NumParties++;

			if(myPlanePtr->AvailSeats == 0)
				{
				Fly(myPlanePtr);
				}
		}
		else
		{
			if(numOfPeople <= LOUNGE.AvailSeats)
			{
				SendToLounge(myTCPtr);
				cout << "Party moved to the lounge." << endl;
			}
			else
			{
			cout<<"There is not enough room in the lounge, send party home."<<endl;
			}

		}
	}

	return isValid;
}


void Fly(Plane* myPlanePtr) 
{	
	cout << "Plane Status: " << endl << endl;
	displayPlane(myPlanePtr);
	
	//after plane returns, get waiting parties from lounge
	Plane* loungePtr = &LOUNGE;
	PartyList* myPLPtr = loungePtr->myPartyList;

	for(unsigned int i = 0; i<50; i++)
	{
		Party* loungeParty = &(myPLPtr->myParties[i]);
		if(loungeParty->NumPeople > 0 &&
			loungeParty->DesiredPlane == myPlanePtr->PlaneId)
		{
			// Attempt to add this party to the plane that flew
			uint myPos = myPlanePtr->myPartyList->Pos;

			if(myPos > myPlanePtr->myPartyList->Size)
			{
				cout << "The party list array cannot accomodate this." << endl ;
				exit(2);
			}

			// Test to see if the plane can accomodate the party size
			if(loungeParty->NumPeople <= myPlanePtr->AvailSeats)
			{
				Party *myParty = &(myPlanePtr->myPartyList->myParties[myPos]);
				myPlanePtr->myPartyList->Pos++;
				
				// Assign the first char of the plane's name to party desired plane
				strncpy(&(myParty->DesiredPlane), &(loungeParty->DesiredPlane), 1);
				loungeParty->DesiredPlane = 'X';

				// Assign the party name
				copyString(&(myParty->pName), loungeParty->pName);
				loungeParty->pName = NULL;

				// Assign the number of people to the party
				myParty->NumPeople = loungeParty->NumPeople;
				loungeParty->NumPeople = 0;
			
				cout << "Moving: " << endl;
				cout << "\t\tParty Name: " << myParty->pName << "\t";
				cout << "Num People in Party:\t" << myParty->NumPeople << "\t";
				cout << "Desired Plane:\t" << myParty->DesiredPlane << endl;
				cout << "From the lounge to " << myPlanePtr->PlaneName << endl;

				myPlanePtr->AvailSeats -= myParty->NumPeople;
				myPlanePtr->NumParties++;

				if(myPlanePtr->AvailSeats == 0)
				{
					Fly(myPlanePtr);
				}
			}		
		}
	}


}


void displayParty(Party* partyPtr)
{
	ShowParty(partyPtr);
	ResetParty(partyPtr);
}


void ShowParty(Party* partyPtr)
{
	if(partyPtr->NumPeople != 0)
	{
		cout << "\t\tParty Name: " << partyPtr->pName << "\t";
		cout << "Num People in Party:\t" << partyPtr->NumPeople << "\t";
		cout << "Desired Plane:\t" << partyPtr->DesiredPlane << endl;
	}
}



void ResetParty(Party* partyPtr)
{
	partyPtr->DesiredPlane = 'X';
	partyPtr->NumPeople = 0;
	free(partyPtr->pName);
	partyPtr->pName = NULL;
}



void displayPartylist(PartyList* partylistPtr)
{
	ShowPartylist(partylistPtr);
	ResetPartyList(partylistPtr);
}


void ShowPartylist(PartyList* partylistPtr)
{	
	cout << "\tNum Parties:\t"<< (partylistPtr->Pos)  << "\t";
	cout << "Size of Party List:\t" <<(partylistPtr->Size) << endl;
	cout << "\tParties: " << endl;
	for(unsigned int i = 0; i<partylistPtr->Pos; i++)
	{
		displayParty(&(partylistPtr->myParties[i]));	
	}
	cout<<endl;
}


void ResetPartyList(PartyList* partyListPtr)
{
	partyListPtr->Pos = 0;
}


void displayPlane(Plane* planePtr)
{
	ShowPlane(planePtr);
	ResetPlane(planePtr);
}


void ShowPlane(Plane* planePtr)
{
	cout << "Plane Initialized: " << planePtr->Initialized << "\t";
	cout << "Total Seats: " << planePtr->NumSeats << "\t";
	cout << "Avail Seats: " << planePtr->AvailSeats << "\t";
	cout << "Num Parties: " << planePtr->NumParties << "\t";
	cout << endl << "\tPartyList" << endl;
	displayPartylist(planePtr->myPartyList);
	cout << endl << endl;	
}


void ResetPlane(Plane* planePtr)
{
	planePtr->NumParties = 0;
	planePtr->AvailSeats = planePtr->NumSeats;
}


Plane* GetPlane(char* whichPlane)
{
	Plane* myPlanePtr = NULL;
	switch(*whichPlane)
	{
		case 'A':
			myPlanePtr = &ALPHA;
			break;
		case 'B':
			myPlanePtr = &BRAVO;
			break;
		case 'L':
			myPlanePtr = &LOUNGE;
			break;
	}

	return myPlanePtr;
}


void ShutDown()
{
	while(ALPHA.NumParties > 0 && ALPHA.Initialized)
	{
			Fly(&ALPHA);
	}

	while(BRAVO.NumParties > 0 && BRAVO.Initialized)
	{
			Fly(&BRAVO);
	}
	cout << "Shutdown Complete."; 
}
