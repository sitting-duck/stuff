#ifndef STATEMENT_H
#define STATEMENT_H

#include "WCS_Pointer.h"
#include "WCS_String.h"
#include "MathTree.h"
#include <fstream>
#include <cstring>

class Statement : public RefCount
{
public:
//*************enums*****************
	enum Exception
	{
		StatementException,
		StatementFileNotOpen
	};

//*************typedefs**************
	typedef unsigned char uchar;

//***************functions************
	Statement();
	explicit Statement(const Statement&);
	//explicit Statement(const WCS_Pointer<Statement>&);
	~Statement();

	//friend Token::Token& Token::Build();
	Statement& Build();
	bool HasEOF();
	void SetEOF(bool);
	bool GetIsValueNeg();
	void SetIsValueNeg(bool);
	int GetNumOpenParens();
	void SetNumOpenParens(int);
	void IncrementNumOpenParens();
	void DecrementNumOpenParens();
	int GetLastValueID();
	void SetLastValueID(int);
	void SetValueArray(int, Token&);
	Token& GetValueArray(int);
	
	Statement& operator=(const Statement&);

private:
//****************enums************************
	enum InputType
	{
		InputUknown, 
		KeywordEVAL,
		KeywordEXP,
		KeywordVALUE,
		Constant, 
		Variable,
		Input0,
		Input1,
		Input2,
		Input3,
		Input4,
		Input5,
		Input6,
		Input7,
		Input8,
		Input9,
		InputPlus,
		InputMinus,
		InputAsterisk,
		InputSlash,
		InputOpenParen,
		InputCloseParen,
		InputSemiColon,
		InputSpace,
		EndOfFile,
		NumInputs
	};

	enum StatementState 
	{
	StartStatement,
	AfterEVAL,	
	AfterVALUE,
	AfterVALUEVariable,
	AfterEXP,
	AfterVALVarConst,
	AfterVALUEConstant,
	AfterEOF,
	NumStates
	};

	bool EOFReached;
	bool IsValueNeg;
	int NumOpenParens;
	static int LastValueID;
	static Token ValueArray[100];	

//************typedefs*******************
//	typedef int State;										//wtf is this shit?
	typedef StatementState (*StatementFunc) (Statement&);

//***********functions********************

	//Token::TokenType GetTokenType(); //wut am I gonna do withis?	
	Token::TokenType GetTokenType();
	//all our got functions go here.
	static StatementState BadStatement(Statement&);
	static StatementState GotEVAL(Statement&);
	static StatementState GotSemiColonAfterEVAL(Statement&);
	static StatementState GotEOF(Statement&);
	static StatementState GotSemiColon(Statement&);
	static StatementState GotVALUE(Statement&);
	static StatementState GotSpaceAfterVALUE(Statement&);
	static StatementState GotConstantAfterVALUEVAR(Statement&);
	static StatementState GotVariableAfterVALUE(Statement&);
	static StatementState GotSpaceAfterVALUEVAR(Statement&);
	static StatementState GotPlusAfterVALVar(Statement&);
	static StatementState GotMinusAfterVALVar(Statement&);
	static StatementState GotSemiColonAfterVALVarConst(Statement&);
	static StatementState GotEXP(Statement&);
	static StatementState GotSpaceAfterEXP(Statement&);
	static StatementState GotOpenParenAfterEXP(Statement&);
	static StatementState GotCloseParenAfterEXP(Statement&);
	static StatementState GotConstantAfterEXP(Statement&);
	static StatementState GotOperatorAfterEXP(Statement&);
	static StatementState GotSemiColonAfterEXP(Statement&);
	static StatementState GotVarAfterEXP(Statement&);

	static InputType InputTable[];
	static MathTree MT;
	static Token sToke;
	static StatementFunc StateFunction[];
	static uchar StateTable[NumInputs][NumStates];

};

inline Statement::Statement()
{
	EOFReached = false;
	IsValueNeg = false;
	LastValueID = 99999;
	NumOpenParens = 0;
}

inline Statement::Statement(const Statement& s)
{
	//worry about this later :/ not even sure I need to define this
}

inline Statement::~Statement()
{

}



inline Statement& Statement::operator=(const Statement& s)
{
	//Statement temp;
	//memcpy((void*)temp, (void*)this, sizeof(this));
	//return temp;
}

#endif
