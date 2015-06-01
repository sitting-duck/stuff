#include <iostream>
#include "MathTree.h"
#include "Token.h"



using namespace std;



void main ()
	{
	char		c;
	int			i;
	int			numParen;
	char		op;
	long		Value;
	MathTree	MT;
	Token		Toke;
	bool cfail = true;

	Token::TokenType DetermineTokenType(char);
	Operator::Precedence DetermineLePrecedence(char, int);
	void Halp();

	Halp();
	for (;;)
		{
			c = cin.get (); //get the first char
			//cin.ignore();

			//while(cfail)
			//{
			//	c = cin.get (); //get the first char
			//	//cin.ignore();
			//	switch(c)
			//	{
			//		case 'c':
			//		case 'C':
			//		case 'o':
			//		case 'O':
			//		case 'v':
			//		case 'V':
			//		case 'e':
			//		case 'E':
			//		case 'x':
			//		case 'X':
			//		case 's':
			//		case 'S':
			//		case 'h':
			//		case 'H':
			//			cfail = false;
			//			break;
			//		default:
			//			cout << "Invalid Input. Try again." << endl;
			//			cfail = true;
			//			break;
			//	}
			//}

		switch (c)
			{
			case 'c':
			case 'C':
				cin >> i; // we are just going to ASSume this input is perrrrfect.
				Toke.SetType (Token::ConstantToken);	
				Toke.SetValue (i);
				MT.InsertOperand (Toke);
				break;
			case 'o':
			case 'O':
				cin >> op;
				cin >> numParen;
				Toke.SetType(	DetermineTokenType(op)	);
				Toke.SetPrecedence(  DetermineLePrecedence(op, numParen)  );
				MT.InsertBinaryOperator(Toke);
				break;
			case 'V':
				cin >> i;
				cin.ignore ();
				Toke.SetType (Token::VariableToken);
				Toke.SetWhich (i);
				MT.InsertOperand (Toke);
				break;
			case 'e':
			case 'E':
				 try{
						cout << "Answer is " << MT.Evaluate () << endl;
					}
				 catch(...)
					{
						cout << "Diving by zero is bad. mmmkay?." << endl;
						cout << "Deleting tree" << endl;
						MT.DeleteTree();
						cout << "Tree deleted, try again." << endl;
					}
				break;
			case 'v':
				cin >> i;
				cin >> Value;
				cin.ignore ();
				Toke.SetType (Token::VariableToken);
				Toke.SetWhich (i);
				Toke.SetValue (Value);
				break;
			case 'd':
			case 'D':
				MT.DeleteTree();
				break;
			case 'x':
			case 'X':
				exit(0);
				break;
			case 's':
			case 'S':
				MT.Draw();
				break;
			case 'h':
			case 'H':
				Halp();
				break;
			}	
		}
	}

Token::TokenType DetermineTokenType(char op)
{
	switch(op)
	{
		case '+':
			return Token::OperatorPlusToken;
		case '-':
			return Token::OperatorMinusToken;
		case '/':
			return Token::OperatorSlashToken;
		case '*':
			return Token::OperatorAsteriskToken;
		default:
			return Token::UnknownToken;

	}
}

Operator::Precedence DetermineLePrecedence(char op, int numParen)
{
	switch(op)
	{
		int temp;
		case '+':
		case '-':
			temp = Operator::BinaryPlusMinusPrecedence + (numParen*(Operator::ParenthesesPrecedence));
			return (Operator::Precedence)temp;
			
		case '/':
		case '*':
			temp = Operator::MultiplyDividePrecedence + (numParen*(Operator::ParenthesesPrecedence));
			return (Operator::Precedence)temp;
		default:
			cout << "WTF is going on here? You're a programmer, fix me!" << endl;
			return Operator::FAILURE;
	}

	/*switch(op)
	{
	case '+':
	case '-':
		return Operator::BinaryPlusMinusPrecedence;
	case '/':
	case '*':
		return Operator::MultiplyDividePrecedence;
	default:
		cout << "Unknown Operator" << endl;
		cout << "Delete the tree and start over." << endl;
		cout << "Or all the rest of your calculations are going to be wrong." << endl;
		return Operator::FAILURE;
	}*/

}

void Halp()
{
	cout << "*******************************************" << endl;
	cout << "c to enter a constant." << endl;
	cout << "o to enter and operator with precedence" << endl;
	cout << "Big V to create a variable."  << endl;
	cout << "Little v to set it's value." << endl;
	cout << "d to delete tree." << endl;
	cout << "s to show tree." << endl;
	cout << "x to exit" << endl;
	cout << "h for help." << endl;
	cout << "*******************************************" << endl;
}

																							




	