#include "Statement.h"

using namespace std;

void main(int argc, char * argv [])
{
	Statement st;
	WCS_String Temp;
	

	if (argc < 2)
			{
				//Temp = "lul.txt";
			cout << "Enter a file name" << endl;
			cin >> Temp;
			}
		else
		{
			Temp = argv [1]; //possible wtf here...
		}
		
	Token Toke;
	Toke.OpenFile(Temp);

	do
	{
		try
		{
		st.Build();
		}
		catch(...)
		{
			cout << "Cannot divide by zero. Exiting Program." << endl;
			exit(0);
		}
	}
	while (st.HasEOF() == false); 
	
	Toke.CloseFile ();

}