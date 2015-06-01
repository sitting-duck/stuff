#ifndef OPERATOR_H
#define OPERATOR_H

#include "Token.h"

class Operator
	{
	public:
		enum Precedence	{
						BinaryPlusMinusPrecedence,
						MultiplyDividePrecedence,
						UnaryPlusMinusPrecedence,

						ParenthesesPrecedence
						};
	private:
					Operator	();
					Operator	(const Operator &);
					~Operator	();
		Operator &	operator =	(const Operator &);
	};

#endif
