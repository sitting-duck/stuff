#ifndef OPERATOR_H
#define OPERATOR_H

#include "Token.h"

class Operator
	{
	public:
		enum Precedence	{
						FAILURE = -1,
						BinaryPlusMinusPrecedence,
						MultiplyDividePrecedence,
						UnaryPlusMinusPrecedence,
						ParenthesesPrecedence,
						four,
						five,
						six,
						seven,
						eight,
						nine,
						ten,
						eleven, 
						twelve,
						thirteen,
						fourteen,
						fifteen,
						sixteen,
						seventeen,
						eighteen,
						nineteen,
						twenty,
						twentyone,
						twentytwo,
						twentythree,
						twentyfour,
						twentfive
						};

	int OperType;
	enum OperTypeEnum {	Plus,Minus,Slash,Star,OpenParen,CloseParen,lilNeg};
	int GetOperType(const Operator& o);
	void SetOperType();

	//void SetOperType(int ot);

	private:
					Operator	();
					Operator	(const Operator &);
					~Operator	();
		Operator &	operator =	(const Operator &);
	};

int GetOperType(const Operator& o)
{
	switch(o.OperType)
	{


	}
}
void SetOperType();	
	

#endif
