#ifndef BINARY_TREE_H
#define BINARY_TREE_H

template <typename Index, typename Data>
	class BinaryTree
		{
		private:
			enum ReturnCode {OK, DuplicateIndex, IndexNotFound};

			struct Node
				{
				Index	I;
				Data	D;
				Node *	pLeft;
				Node *	pRight;
				};
		public:
						BinaryTree();
						~BinaryTree();
			ReturnCode	Insert	(const Index &, const Data &);
			ReturnCode	Search	(const Index &, Data &);
			ReturnCode	Replace	(const Index &, const Data &);
		private:
			Node * Root;
		};

template <typename Index, typename Data>
	BinaryTree <Index, Data>::BinaryTree(): Root(NULL) {}
template <typename Index, typename Data>
	BinaryTree <Index, Data>::~BinaryTree(){}

template <typename Index, typename Data>
	typename BinaryTree <Index, Data>::ReturnCode BinaryTree <Index, Data>::Insert (const Index & I, const Data & D)
		{
		Node * pNode;
		if (!Root)//if root does not exist...
				{
				Root			= new Node;
				(*Root).I		= I;
				(*Root).D		= D;
				(*Root).pLeft	= 0;
				(*Root).pRight	= 0;
				return OK;
				}
			else
				{
				pNode = Root;
				for (;;)//infinite loop; pNode is going to travel down the binary tree until we fins a match
					    //this loop will not exit until we return ok. 
					if (I == (*pNode).I)
							return DuplicateIndex;//can we call replace here instead then?
						else
							if (I < (*pNode).I)
									if (!(*pNode).pLeft)
											{
											(*pNode).pLeft				= new Node;
											((*(*pNode).pLeft)).I		= I;
											((*(*pNode).pLeft)).D		= D;
											((*(*pNode).pLeft)).pLeft	= 0;
											((*(*pNode).pLeft)).pRight	= 0;
											return OK;
											}
										else
											pNode = (*pNode).pLeft;
								else
									if (!(*pNode).pRight)
											{
											(*pNode).pRight				= new Node;
											((*(*pNode).pRight)).I		= I;
											((*(*pNode).pRight)).D		= D;
											((*(*pNode).pRight)).pLeft	= 0;
											((*(*pNode).pRight)).pRight	= 0;
											return OK;
											}
										else
											pNode = (*pNode).pRight;
				}
		}

template <typename Index, typename Data>
	typename BinaryTree <Index, Data>::ReturnCode BinaryTree <Index, Data>::Search (const Index & I, Data & D)
		{
		Node * pNode;
		if (!Root)
				return IndexNotFound;
			else
				{
				pNode = Root;
				for (;;)
					if (I == (*pNode).I)
							{
							D = (*pNode).D;
							return OK;
							}
						else
							if (I < (*pNode).I)
									if (!(*pNode).pLeft)
											return IndexNotFound;
										else
											pNode = (*pNode).pLeft;
								else
									if (!(*pNode).pRight)
											return IndexNotFound;
										else
											pNode = (*pNode).pRight;
				}
		}

#endif
