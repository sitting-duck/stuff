#include "MathTree.h"

MathTree::Node::Node (const Token & T): Token (T)
	{
	}
MathTree::Node::Node ()//this shouldn't mess anything up
	{
		pParent.SetToNull();
		pLeft.SetToNull();
		pRight.SetToNull();
		IsLeftSideDone = false;
	}

MathTree::Node::~Node ()
	{
	}

MathTree::MathTree ()
	{
		//WCS_Pointer is goign to set root and pLastOperator to NULL so there is 
		//no reason to put anything here.
	}

MathTree::~MathTree ()
	{
		// alot of crap is going to go here
	}

void MathTree::InsertBinaryOperator (const Token & T)
	{
	WCS_Pointer <Node>	pNode (new Node (T));

	while ((pLastOperator.Exists ()) && ((*pLastOperator).GetPrecedence () >= (*pNode).GetPrecedence ()))
		pLastOperator = (*pLastOperator).pParent;

	if (pLastOperator.DoesNotExist ())
			{
			(*pRoot).pParent	= pNode;
			(*pNode).pLeft		= pRoot;
			pRoot				= pNode;
			}
		else
			{
			(*pNode).pLeft				= (*pLastOperator).pRight;
			(*(*pNode).pLeft).pParent	= pNode;
			(*pLastOperator).pRight		= pNode;
			(*pNode).pParent			= pLastOperator;
			}
	pLastOperator = pNode;
	}

void MathTree::InsertOperand (const Token & T)
	{
	WCS_Pointer <Node>	pNode (new Node (T));

	if (pRoot.DoesNotExist ())
			pRoot = pNode;
		else
			{
			(*pLastOperator).pRight = pNode;
			(*pNode).pParent		= pLastOperator;
			}
	}

void MathTree::InsertUnaryOperator (const Token & T)
	{
	Token Temp (Token::ConstantToken, 0);

	InsertOperand (Temp);
	InsertBinaryOperator (T);
	}

WCS_Pointer <MathTree::Node> & MathTree::GetLeftMostOperator (WCS_Pointer <Node> & pNode)
{
	WCS_Pointer <Node> pTemp;
	if (pNode.Exists ())
	{
		pTemp = GetLeftMost(pNode);
		//pNode = (*pNode).pParent;
		return (*pTemp).pParent;
	}
	return pNode;
}

WCS_Pointer <MathTree::Node> & MathTree::SetLeftMostOperator (WCS_Pointer <Node> & pNode)
{
	WCS_Pointer <MathTree::Node> umWHAT;
	cout << "write this function or something. " << endl;
	return umWHAT;

}

WCS_Pointer <MathTree::Node> & MathTree::GetLeftMost (WCS_Pointer <Node> & pNode)
{
	if((*pNode).pLeft.Exists ())
	{
		(*pNode).IsLeftSideDone = false;
		return GetLeftMost((*pNode).pLeft);
	}
	else
		return pNode;
}

Variable::ValueType MathTree::Evaluate ()
	{
	if (pRoot.Exists ())
			{
			WCS_Pointer <Node> pNode;

			pNode = GetLeftMostOperator (pRoot);
			while (pNode.Exists ())
			{
				if (!(*pNode).IsLeftSideDone)//while left side is not done...
						{
						(*pNode).SetValue ((*(*pNode).pLeft).GetValue ());
						(*pNode).IsLeftSideDone	= true;
						pNode = GetLeftMostOperator ((*pNode).pRight);
						}
					else
						{
						switch ((*pNode).GetType ())
							{
							case Token::OperatorPlusToken:
								(*pNode).SetValue ((*pNode).GetValue () + (*(*pNode).pRight).GetValue ());
								break;
							case Token::OperatorMinusToken:
								(*pNode).SetValue ((*pNode).GetValue () - (*(*pNode).pRight).GetValue ());
								break;
							case Token::OperatorSlashToken:
								if ((*(*pNode).pRight).GetValue () == 0)
									throw DivideByZero;
								(*pNode).SetValue (((*pNode).GetValue ()) / ((*(*pNode).pRight).GetValue ()));
								break;
							case Token::OperatorAsteriskToken:
								(*pNode).SetValue (((*pNode).GetValue ()) * ((*(*pNode).pRight).GetValue ()));								
								break;
							}
						pNode = (*pNode).pParent;
						}
			}	
			return (*pRoot).GetValue ();
			}
		else
			return 0;
	}

void MathTree::DeleteTree()
{
	WCS_Pointer<Node> FromWhere = pRoot;
	WCS_Pointer<Node> pDelete   = pRoot;
	isDeleted = false;	

	if(pRoot.DoesNotExist())
	{
		cout << "Nothing to do here." << endl;
		return;
	}

	while(pRoot.Exists())
	{		
		while(isDeleted != true )
		{		
			while(isDeleted == false)
				{
					cout << "Beginning Delete: " << endl;
					pDelete = GetLeftMostOperator(FromWhere);
					DeleteNodes(pDelete);//left side
					isDeleted = true;
					cout << "Nodes Deleted." << endl;												
				}
		}			
		pRoot.SetToNull();
		cout << "Root has been deleted." << endl;
	}
	cout << "Delete Successful." << endl;		
}

void MathTree::DeleteNodes(WCS_Pointer<Node> pDelete)
{
	while(pDelete != pRoot)
		{
			//(*(*pDelete).pLeft).pParent.SetToNull();
			if((*pDelete).pLeft.Exists())
			{
				(*pDelete).pLeft.SetToNull();
			}
			cout << "		Deleted leftmost node." << endl;
				while( (*(*pDelete).pRight).pLeft.Exists() && (*pDelete).pRight.Exists() )
				{
					pDelete = (*(*pDelete).pRight).pLeft;									
				}
			if((*pDelete).pLeft.Exists())
			{
				(*pDelete).pLeft.SetToNull();
			}
			cout << "		Deleted leftmost of next rightmost" << endl;			
			if((*pDelete).pRight.Exists())
			{
				(*pDelete).pRight.SetToNull();
			}			
			cout << "		Deleted rightmost of next rightmost" << endl;
			if((*pDelete).pParent.Exists())
			{
				pDelete = (*pDelete).pParent;
			}		
			cout << "Gone up a level. " << endl;
		}
}
	
void MathTree::Draw()
{
	WCS_Pointer<Node> pDDraw   = pRoot;
	
	if( (*pRoot).GetType() == Token::OperatorAsteriskToken	||
		(*pRoot).GetType() == Token::OperatorSlashToken		||
		(*pRoot).GetType() == Token::OperatorPlusToken		||
		(*pRoot).GetType() == Token::OperatorMinusToken		)

		if((*pRoot).GetType() == Token::OperatorAsteriskToken)
		{
			cout << "   (*)   " << endl;   
		}
		if((*pRoot).GetType() == Token::OperatorSlashToken)
		{
			cout << "   (/)   " << endl;   
		}
		if((*pRoot).GetType() == Token::OperatorPlusToken)
		{
			cout << "   (+)   " << endl;   
		}
		if((*pRoot).GetType() == Token::OperatorMinusToken)
		{
			cout << "   (-)   " << endl;   
		}


	cout << "   (" << (*pRoot).G << ")   " << endl;
	cout << "(" <<(*(*pRoot).pLeft).GetValue() << ")   (" << (*(*pRoot).pRight).GetValue() << ")"<<endl;
}
