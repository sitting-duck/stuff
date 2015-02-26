#define STATEMENT_CPP

#include "Statement.h"

//****************Static vars from Statement class *******************

//ifstream Statement::SourceFile;
MathTree Statement::MT;
Token Statement::sToke;
int Statement::LastValueID;
Token Statement::ValueArray[100];

Statement::StatementFunc Statement::StateFunction[] = 
{
	BadStatement,				     // 0
	GotEVAL,					     // 1
	GotSemiColonAfterEVAL,		     // 2
	GotEOF,						     // 3
	GotSemiColon,				     // 4
	GotVALUE,					     // 5
	GotSpaceAfterVALUE,			     // 6
	GotConstantAfterVALUEVAR,	     // 7
	GotVariableAfterVALUE,		     // 8
	GotSpaceAfterVALUEVAR,		     // 9
	GotPlusAfterVALVar,			     //10
	GotMinusAfterVALVar,		     //11
	GotSemiColonAfterVALVarConst,    //12
	GotEXP,							 //13	
	GotSpaceAfterEXP,				 //14	
	GotOpenParenAfterEXP,			 //15
	GotCloseParenAfterEXP,			 //16
	GotConstantAfterEXP,			 //17
	GotOperatorAfterEXP,			 //18
	GotSemiColonAfterEXP,			 //19
	GotVarAfterEXP					 //20
};

Statement::uchar Statement::StateTable[NumInputs][NumStates] = 
{
					   //   			              
					   // Start  		       After  
		 			   // State  After	After	VAL	 After	    
					   // ment 	  EVAL	Value	Var	  EXP	    
/*EndOfInputToken*/	      { 3,     0,     0,	 0,	   0    },
/*UnknownToken*/		  { 0,     0,     0,	 0,	   0    },
/*VariableToken*/		  { 0,     0,     8,	 0,	   20    },
/*ConstantToken*/		  { 0,     0,     0,	 7,	   17   },
/*KeywordEvalToken*/	  { 1,     0,     0,	 0,	   1    },
/*KeywordExpToken*/		  { 13,    0,     0,	 0,	   0    },
/*KeywordValueToken*/	  { 5,     0,     0,	 0,	   0    },
/*OperatorPlusToken*/	  { 0,     0,     0,	 10,   18   },
/*OperatorMinusToken*/	  { 0,     0,     0,	 11,   18   },
/*OperatorAsteriskToken*/ { 0,     0,     0,	 0,	   18   },
/*OperatorSlashToken*/	  { 0,     0,     0,	 0,	   18   },
/*SymbolOpenParenToken*/  { 0,     0,     0,	 0,	   15   },
/*SymbolCloseParenToken*/ { 0,     0,     0,	 0,	   16   },
/*SymbolSemiColonToken*/  { 4,     2,     0,	 12,   19   },
/*SpaceToken*/			  { 0,     0,     6,	 9,	   14   }
};

Statement& Statement::Build()
{
	
		StatementState CurrentState (StartStatement);		

		do	
		{
			CurrentState = StateFunction[StateTable [ GetTokenType() ] [CurrentState] ](*this);
			
		} while (HasEOF() == false);
		
			return *this;
	
}

inline Token::TokenType Statement::GetTokenType()
{	
	sToke = sToke.Build();
	return sToke.GetType();
}

inline bool Statement::HasEOF()
{
	return (*this).EOFReached;
}

inline void Statement::SetEOF(bool b)
{
	EOFReached = b;
}

inline bool Statement::GetIsValueNeg()
{
	return (*this).IsValueNeg;
}

inline void Statement::SetIsValueNeg(bool b)
{
	IsValueNeg = b;
}

inline int Statement::GetNumOpenParens()
{
	return (*this).NumOpenParens;
}

inline void Statement::SetNumOpenParens(int i)
{
	(*this).NumOpenParens = i;
}

inline void Statement::IncrementNumOpenParens()
{
	(*this).NumOpenParens++;
}

inline void Statement::DecrementNumOpenParens()
{
	(*this).NumOpenParens--;
}

int Statement::GetLastValueID()
{
	return LastValueID;
}

void Statement::SetLastValueID(int i)
{
	LastValueID = i;
}

void Statement::SetValueArray(int index, Token& t)
{
	ValueArray[index] = t;
}

Token& Statement::GetValueArray(int index)
{
	return ValueArray[index];
}

//**************************************************************************************************

inline Statement::StatementState Statement::BadStatement(Statement& s)
{
	//for testing 
	//cout << "Unknown Char." << endl;
	return StartStatement;
}

inline Statement::StatementState Statement::GotEVAL(Statement& s)
{
	//cout << "Got EVAL" << endl;
	return AfterEVAL;
}

inline Statement::StatementState Statement::GotSemiColonAfterEVAL(Statement& s)
{
	//cout << "Got a semicolon after EVAL" << endl;
	cout << "Answer is " << MT.Evaluate() << endl;
//	cout << "Deleting Tree" << endl;
	MT.DeleteTree();
	return StartStatement;
}

inline Statement::StatementState Statement::GotEOF(Statement& s)
{
	s.SetEOF(true);
	//cout << "Got EOF" << endl;
	return AfterEOF;
}

inline Statement::StatementState Statement::GotSemiColon(Statement& s)
{
	//cout << "Got a semicolon" << endl;
	//cout << "Answer is: 0" << endl;
	return StartStatement;
}

inline Statement::StatementState Statement::GotVALUE(Statement& s)
{
	//cout << "Got VALUE" << endl;
	return AfterVALUE;
}

inline Statement::StatementState Statement::GotSpaceAfterVALUE(Statement& s)
{
	//cout << "Got a Space" << endl;
	return AfterVALUE;
}

inline Statement::StatementState Statement::GotVariableAfterVALUE(Statement& s)
{
	//cout << "Got Variable Number " << sToke.GetWhich() << endl;
	LastValueID = sToke.GetWhich();
	ValueArray[LastValueID].SetType(Token::VariableToken);
	ValueArray[LastValueID].SetWhich(sToke.GetWhich());
	return AfterVALUEVariable;
}

inline Statement::StatementState Statement::GotSpaceAfterVALUEVAR(Statement& s)
{
	sToke.SetType(Token::SpaceToken);
	sToke.SetValue(0);
	//cout << "Got a Space" << endl;
	return AfterVALUEVariable;
}

inline Statement::StatementState Statement::GotPlusAfterVALVar(Statement& s)
{
	//cout << "Got a Plus for the sign" << endl;
	s.SetIsValueNeg(false);
	return AfterVALUEVariable;
}

inline Statement::StatementState Statement::GotMinusAfterVALVar(Statement& s)
{
	//cout << "Got a Minus for the sign" << endl;
	s.SetIsValueNeg(true);
	return AfterVALUEVariable;
}

Statement::StatementState Statement::GotConstantAfterVALUEVAR(Statement& s)
{
	if(!s.GetIsValueNeg())
	{
		//cout << "Got a value of value " << sToke.GetValue() << endl;
		//cout << "Assigning it to V" << s.GetLastValueID() << endl;
	}	

	else
	{
		sToke.SetValue(sToke.GetValue() - (2* sToke.GetValue()));
		s.SetIsValueNeg(false);
		//cout << "Got a value of value " << sToke.GetValue()<< endl;
		//cout << "Assigning it to V" << s.GetLastValueID() << endl; 
	}
	
	//ValueArray[LastValueID].SetValue(sToke.GetValue());
	Token::VariableArray[LastValueID].SetValue(sToke.GetValue());
	//s.SetValueArray(s.GetLastValueID(), sToke.GetValue());

	return StartStatement;
}

inline Statement::StatementState Statement::GotSemiColonAfterVALVarConst(Statement& s)
{
	//cout << "Got a semicolon; end of value statement" << endl;
	s.SetIsValueNeg(false);
	return StartStatement;
}

inline Statement::StatementState Statement::GotEXP(Statement& s)
{
	//cout << "Got EXP" << endl;
	return AfterEXP;
}

inline Statement::StatementState Statement::GotSpaceAfterEXP(Statement& s)
{
	return AfterEXP;
}

inline Statement::StatementState Statement::GotOpenParenAfterEXP(Statement& s)
{
	s.IncrementNumOpenParens();
	return AfterEXP;
}

inline Statement::StatementState Statement::GotCloseParenAfterEXP(Statement& s)
{
	if(s.GetNumOpenParens() > 0)
	{
		s.DecrementNumOpenParens();
	}
	else
	{
		cout << "Cannot have a closing paren without an opening paren." << endl;
		cout << "Deleting tree." << endl;
		MT.DeleteTree();
	}

	return AfterEXP;
}

inline Statement::StatementState Statement::GotConstantAfterEXP(Statement& s)
{
	//cout << "Inserting constant " << s.sToke.GetValue() << endl;
	MT.InsertOperand(s.sToke);
	s.sToke.SetValue(0);
	//s.sToke.PutBackLastChar();
	return AfterEXP;
}

inline Statement::StatementState Statement::GotOperatorAfterEXP(Statement& s)
{
	//cout << "Inserting operator " << endl;
	switch(s.sToke.GetType())
	{
		case Token::OperatorPlusToken:
		case Token::OperatorMinusToken:
			s.sToke.SetPrecedence(Operator::BinaryPlusMinusPrecedence);
			break;
		case Token::OperatorAsteriskToken:
		case Token::OperatorSlashToken:
			s.sToke.SetPrecedence(Operator::MultiplyDividePrecedence);
			break;
	}
	if(s.GetNumOpenParens() != 0)
	{
		//s.sToke.SetPrecedence((Operator::Precedence )(s.sToke.GetPrecedence() + (s.sToke.GetPrecedence()*(s.GetNumOpenParens()*Operator::ParenthesesPrecedence)))); //very possible wtf here...
		s.sToke.SetPrecedence((Operator::Precedence )(s.sToke.GetPrecedence() + (s.GetNumOpenParens()*Operator::ParenthesesPrecedence))); //very possible wtf here...
	}

	MT.InsertBinaryOperator(s.sToke);
	return AfterEXP;
}

inline Statement::StatementState Statement::GotSemiColonAfterEXP(Statement& s)
{
	//cout << "End of Statement " << endl;
	return StartStatement;
}

inline Statement::StatementState Statement::GotVarAfterEXP(Statement& s)
{
	//cout << "Inserting Value " << s.sToke.GetWhich() << endl;
	//MT.InsertOperand(ValueArray[s.sToke.GetWhich()]);
	Token temp;
	temp.SetType(Token::VariableToken);
	temp.SetWhich(s.sToke.GetWhich());
	int v = Token::VariableArray[s.sToke.GetWhich()].GetValue();
	temp.SetTokenValue(v);	
	MT.InsertOperand(temp);
	//MT.InsertOperand(Token::VariableArray[s.sToke.GetWhich()]);
	return AfterEXP;
}