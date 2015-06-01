int ConvertCNum(char[4]);

int NumInt;
char Input[4] = {'\n'};
bool HasLetters = false;

int ConvertCNum(char cnum[4])
{
	bool HasLetters = false;
	int NumInt; 
	char cnum[4] = {'\n'};  //u may want to do this with 3, i dunno yet

	cin.get(cnum, 4, '\n');					
	cin.ignore ();	
	for(int i = 0; (cnum[i] != '\n'); i++)
	{
		HasLetters = isalpha(cnum[i]);	
		if(HasLetters == true)
			break;
	}
						
	if(HasLetters == false)
		NumInt = atoi(cnum);
	return NumInt;
}

//some more fuckery from inside the switch
do
	{
							
	NumInt = ConvertCNum(Input);

		while(NumInt > (999) || NumInt < -(999) || HasLetters == true)
		{
			cout << "Constant cannot be more than 3 digits long" << endl;
			cout << "(not including the minus sign as a digit)"  << endl;
			cout << "You may not enter letters, only numeric digits" << endl;
			cout << " and an optional negative sign. " << endl;
			cout << "Please enter another 3 digit number, "		 << endl;
			cout << "following this input pattern: <000> or <-000> " << endl;

			if(HasLetters == true)
			{
				cout << endl << endl;
				cout << "Stop putting letters where numbers should go." << endl;
				cout << "Herp derp. Now try again." << endl << endl;;
				HasLetters = false;
			}

			//cout << "Put your number here: " ;
			//cin >> i;								
			//cin.ignore ();
			//cout << endl;
		}

		cout << "You entered a constant of " << NumInt << endl;
		break;//move this shit
		Toke.SetType (Token::ConstantToken);	// move SetType from private to public in Token class
		Toke.SetValue (i);
		MT.InsertOperand (Toke);
	}while(