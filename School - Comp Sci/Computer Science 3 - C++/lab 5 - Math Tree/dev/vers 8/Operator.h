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

	//void SetOperType(int ot);

	private:
					Operator	();
					Operator	(const Operator &);
					~Operator	();
		Operator &	operator =	(const Operator &);
	};

//OHLOOKSOMECRAP*enum OperTypeEnum {	Plus,Minus,Slash,Star,OpenParen,CloseParen,lilNeg};*/
	

#endif
