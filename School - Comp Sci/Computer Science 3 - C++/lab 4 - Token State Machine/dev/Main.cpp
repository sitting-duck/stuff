#include <iostream>

using namespace std;

#include "Token.h"
#include "WCS_String.h"

void main (int argc, char * argv [])

	{
	WCS_String Temp;
	Token Toke;

	if (argc < 2)
			{
				//Temp = "xxx.dat";
			cout << "Enter a file name" << endl;
			cin >> Temp;
			}
		else
			Temp = argv [1];
	Token::OpenFile (Temp);
	do	{
		Toke.Build ();
		switch (Toke.GetType ())
			{
			case Token::KeywordEvalToken:
				cout << "Found Keyword EVAL" << endl;
				break;
			case Token::VariableToken:
				cout << "Found Variable " << Toke.GetWhich () << endl;
				break;
			case Token::EndOfInputToken:
				cout << "End of Input" << endl;
				break;
			case Token::UnknownToken:
				cout << "Unknown Token." << endl;
				break;
			case Token::ConstantToken:
				cout << "Constant Token." << endl;
				break;
			case Token::KeywordExpToken:
				cout << "Found keyword EXP" << endl;
			case Token::SpaceToken:
				//ain't doin shit here cap'n.
				break;
			case Token::KeywordValueToken:
				cout << "Found keyword VALUE." << endl;
				break;
			case Token::OperatorPlusToken:
				cout << "Found a +" << endl;
				break;
			case Token::OperatorMinusToken:
				cout << "Found a -" << endl;
				break;
			case Token::OperatorAsteriskToken:
				cout << "Found a -" << endl;
				break;
			case Token::OperatorSlashToken:
				cout << "Found a /" << endl;
				break;
			case Token::SymbolOpenParenToken:
				cout << "Found a (" << endl;
				break;
			case Token::SymbolCloseParenToken:
				cout << "Found a )" << endl;
				break;
			case Token::SymbolSemiColonToken:
				cout << "Found a ;" << endl;
				break;

			default:
				cout << "u dun goofed." << endl;
			}
		} while (Toke.GetType () != Token::EndOfInputToken);
	Token::CloseFile ();
		
		}
