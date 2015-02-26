#include "MathTree.h"

MathTree::Node::Node (const Token & t)
	{
		Init(t.GetType(), t.GetValue());
		IsLeftSideDone = false;
		SetPrecedence(t.GetPrecedence());
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
	WCS_Pointer <Node>	pNode (new Node (T)); // the memory for node is allocated and then the node constructor is called

	//this will make sure based on precedence that the operator gets put on the correct level of the tree.
	while ((pLastOperator.Exists ()) && ((*pLastOperator).GetPrecedence () >= (*pNode).GetPrecedence ()))
		pLastOperator = (*pLastOperator).pParent;

	//if we just started move the root down and make pNode the new root.
	if (pLastOperator.DoesNotExist ())
			{
			(*pRoot).pParent	= pNode;
			(*pNode).pLeft		= pRoot;
			pRoot				= pNode;
			}
		else
			{
			(*pNode).pLeft				= (*pLastOperator).pRight;//set the left side of pNode
			(*(*pNode).pLeft).pParent	= pNode;				 //set the parent in the left side to pNode
			(*pLastOperator).pRight		= pNode;				 //Insert pNode into the tree to the right of the last oper
			(*pNode).pParent			= pLastOperator;		 //Set the parent in pLastOperator
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
					(*pNode).SetTokenValue ((*(*pNode).pLeft).GetValue ());
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
		//cout << "Nothing to do here." << endl;
		return;
	}

	while(pRoot.Exists())
	{		
		while(isDeleted != true )
		{		
			while(isDeleted == false)
				{
					//cout << "Beginning Delete: " << endl;
					pDelete = GetLeftMostOperator(FromWhere);
					DeleteNodes(pDelete);//left side
					isDeleted = true;
					//cout << "Nodes Deleted." << endl;												
				}
		}			
		pRoot.SetToNull();
		//cout << "Root has been deleted." << endl;
	}
	//cout << "Delete Successful." << endl;		
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
			//cout << "		Deleted leftmost node." << endl;
				//while( (*(*pDelete).pRight).pLeft.Exists() && (*pDelete).pRight.Exists() )
				while(pDelete->pRight.Exists() && pDelete->pRight->pLeft.Exists())
				{
					pDelete = (*(*pDelete).pRight).pLeft;									
				}
			if((*pDelete).pLeft.Exists())
			{
				(*pDelete).pLeft.SetToNull();
			}
			//cout << "		Deleted leftmost of next rightmost" << endl;			
			if((*pDelete).pRight.Exists())
			{
				(*pDelete).pRight.SetToNull();
			}			
			//cout << "		Deleted rightmost of next rightmost" << endl;
			if((*pDelete).pParent.Exists())
			{
				pDelete = (*pDelete).pParent;
			}		
			//cout << "Gone up a level. " << endl;
		}
}
	
	
