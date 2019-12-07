//#include "MathTree.h"
//
//
//using namespace std;
//
//void main(int argc, char * argv [])
//{
//	MathTree m1;
//
//	WCS_String Temp;
//	Token Toke;
//
//	if (argc < 2)
//			{
//				Temp = "xxx.dat";
//			//cout << "Enter a file name" << endl;
//			//cin >> Temp;
//			}
//		else
//			Temp = argv [1];
//	Token::OpenFile (Temp);
//	do	{
//		Toke.Build ();
//		switch (Toke.GetType ())
//			{
//			case Token::KeywordEvalToken:
//				m1.Evaluate();
//				break;
//			case Token::VariableToken:	
//				cout << "Found variable " << Toke.GetWhich () << endl;
//				m1.InsertOperand(Toke);
//				break;
//			case Token::EndOfInputToken:
//				cout << "End of Input" << endl;
//				break;
//			case Token::UnknownToken:
//				cout << "Unknown Token." << endl;
//				break;
//			case Token::ConstantToken:
//				cout << "Found a constant." << endl;
//				//in here we will compensate for negative sign
//				m1.InsertOperand(Toke);			
//				break;
//			case Token::KeywordExpToken:
//				cout << "Found keyword EXP" << endl;
//				cout << "What the fuck am I gonna do with this shit?" << endl;
//			case Token::SpaceToken:
//				//ain't doin shit here cap'n.
//				break;
//			case Token::KeywordValueToken:
//				cout << "Found keyword VALUE." << endl;
//				cout << "What the fuck am I gonna do with this shit?" << endl;
//				cout << "ur gonna write a your own Replace() function for this." << endl;
//				break;
//			case Token::OperatorPlusToken:
//				m1.InsertBinaryOperator(Toke);
//				break;
//			case Token::OperatorMinusToken:
//				m1.InsertBinaryOperator(Toke);
//				break;
//			case Token::OperatorAsteriskToken:
//				m1.InsertBinaryOperator(Toke);
//				break;
//			case Token::OperatorSlashToken:
//				m1.InsertBinaryOperator(Toke);
//				break;
//			case Token::SymbolOpenParenToken:
//				cout << "Found a (" << endl;
//				cout << "I don't think we are going to be using these." << endl;
//				break;
//			case Token::SymbolCloseParenToken:
//				cout << "Found a )" << endl;
//				cout << "I don't think we are going to be using these." << endl;
//				break;
//			case Token::SymbolSemiColonToken:
//				cout << "Found a ;" << endl;
//				cout << "What the fuck am I gonna do with this shit?" << endl;
//				break;
//			case Token::OperatorWithPrecedenceToken:
//				cout << "Got an operator with a precedence of: something. " << endl;
//				break;
//
//			default:
//				cout << "u dun goofed." << endl;
//			}
//		} while (Toke.GetType () != Token::EndOfInputToken);
//	Token::CloseFile ();
//		
//		
//
//}
