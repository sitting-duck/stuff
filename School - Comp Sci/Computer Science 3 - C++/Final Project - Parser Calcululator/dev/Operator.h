#ifndef OPERATOR_H
#define OPERATOR_H

#include "Token.h"

class Operator
	{
	public:
		enum Precedence	{
						UnknownPrecedence,
						BinaryPlusMinusPrecedence = 1,
						MultiplyDividePrecedence,
						UnaryPlusMinusPrecedence,
						ParenthesesPrecedence, 
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
						twentyfive
						};
	private:
					Operator	();
					Operator	(const Operator &);
					~Operator	();
		Operator &	operator =	(const Operator &);
	};

#endif
