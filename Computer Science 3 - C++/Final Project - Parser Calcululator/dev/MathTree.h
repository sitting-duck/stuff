#ifndef MATH_TREE_H
#define MATH_TREE_H

#include "WCS_Pointer.h"
#include "Token.h"

class MathTree
{
private:
		class Node: public Token	// Token is derived from RefCount so Node will work with WCS_Pointer
			{
			public:
						Node	(const Token &);
						~Node	();
						Node	();
						Node	(const Node &);
				void	operator =	(const Node &);

				WCS_Pointer <Node>		pParent;
				WCS_Pointer <Node>		pLeft;
				WCS_Pointer <Node>		pRight;
				bool					IsLeftSideDone;	
			};

		bool	isDeleted;		

public:
		enum	Exceptions	{DivideByZero};
								MathTree				();
								~MathTree				();
		WCS_Pointer <Node> &	GetLeftMostOperator		(WCS_Pointer <Node> &);
		WCS_Pointer <Node> &	GetLeftMost				(WCS_Pointer <Node> &);
		Variable::ValueType		Evaluate				();
		void					InsertBinaryOperator	(const Token &);
		void					InsertOperand			(const Token &);
		void					InsertUnaryOperator		(const Token &);
		void					DeleteTree				();
		void					DeleteNodes				(WCS_Pointer <Node>);

private:
				MathTree	(const MathTree &);
		void	operator =	(const MathTree &);

		WCS_Pointer <Node>	pRoot;
		WCS_Pointer <Node>	pLastOperator;
};

#endif
