#ifndef UBARRAY_H
#define UBARRAY_H

//#include "WCS_Pointer.h"
#include "WCS_Pointer.h"	
#include <string>

#include "ANT_String.h"
#include "ReadString.h"


typedef unsigned int uint;

using namespace std;

enum Exceptions {ArrayEmpty = 1, GetFirstNotCalled, NoNextElement, NoPrevElement, ElementNotFound};

template <class DATA, class INDEX>
	class UBArray
		{
		private:
			struct Node: public RefCount
				{
				DATA				Data;
				INDEX				Index;
				WCS_Pointer <Node>	pNext;
				WCS_Pointer <Node>	pPrev;

					Node()
					{
						pNext.SetToNull();
						pPrev.SetToNull();
					}
				};

		public:

			

					UBArray		();
					~UBArray	();
			const	DATA&	GetFirst	() const;
					DATA&	GetFirst	() ;
			const	DATA&	GetLast		() const;
					DATA&	GetLast		() ;
			const	DATA&	GetNext		() const;
					DATA&	GetNext		();
			const	DATA&	GetPrev		() const;
					DATA&	GetPrev		() ;
					long	Size		() const;
					DATA&	operator []	(const INDEX & I);
			const	DATA&	operator [] (const INDEX & I) const;
			
			const DATA&		At(const INDEX & I) const throw (...);
			bool			Remove(const INDEX & I) throw (...);
			void	Delete				();
	
		private:


					UBArray		(const UBArray <DATA, INDEX> &);
			void	operator =	(const UBArray <DATA, INDEX> &);

					int			NumElements;
					WCS_Pointer <Node>	pHead;
					WCS_Pointer <Node>	pTail;
			mutable	WCS_Pointer <Node>	pCurrent;

		};

template <class DATA, class INDEX>
	inline UBArray <DATA, INDEX>::UBArray (): NumElements (0), pHead(NULL), pTail(NULL)
		{
		}

template <class DATA, class INDEX>
	inline UBArray <DATA, INDEX>::~UBArray ()
		{
			Delete ();
		}

template <class DATA, class INDEX>
	inline long UBArray <DATA, INDEX>::Size () const
		{
		return NumElements;
		}

template <class DATA, class INDEX>
	inline const DATA & UBArray <DATA, INDEX>::GetFirst () const
		{
			return GetFirst();
		}

template <class DATA, class INDEX>
	inline DATA & UBArray <DATA, INDEX>::GetFirst ()
		{
			if (pHead.DoesNotExist ())
					throw ArrayEmpty;
				else
					{
						pCurrent = pHead;
						return (*pCurrent).Data;
					}
		}

template <class DATA, class INDEX>
	inline const DATA & UBArray <DATA, INDEX>::GetLast () const
		{
			return GetLast();
		}

template <class DATA, class INDEX>
	inline DATA & UBArray <DATA, INDEX>::GetLast ()
		{
			if (pTail.DoesNotExist ())
					throw ArrayEmpty;
				else
					{
						pCurrent = pTail;
						return (*pCurrent).Data;
					}
		}

template <class DATA, class INDEX>
	inline const DATA & UBArray <DATA, INDEX>::GetNext () const
		{
			return GetNext();
		}

template <class DATA, class INDEX>
	inline DATA & UBArray <DATA, INDEX>::GetNext ()
		{
			if (pCurrent.DoesNotExist ())
					throw GetFirstNotCalled;
				else
					if ((*pCurrent).pNext.DoesNotExist ())
							throw NoNextElement;
					else
						{
						pCurrent = (*pCurrent).pNext;
						return (*pCurrent).Data;
						}
		}

template <class DATA, class INDEX>
	inline const DATA & UBArray <DATA, INDEX>::GetPrev () const
		{
			return GetPrev();
		}

template <class DATA, class INDEX>
	inline DATA & UBArray <DATA, INDEX>::GetPrev ()
		{
			if (pCurrent.DoesNotExist ())
					throw GetFirstNotCalled;
				else
					if ((*pCurrent).pPrev.DoesNotExist ())
							throw NoPrevElement;
					else
						{
						pCurrent = (*pCurrent).pPrev;
						return (*pCurrent).Data;
						}
		}

template <class DATA, class INDEX>
	DATA & UBArray <DATA, INDEX>::operator [] (const INDEX & I) //setAt
		{
		WCS_Pointer <Node>	pNode;

		if (pHead.DoesNotExist ())
				{
				pNode			= WCS_Pointer <Node> (new Node);
				pHead			= pNode;
				pTail			= pHead;
				(*pHead).Index	= I;
				NumElements++;
				}
			else
				if (I < (*pHead).Index)
						{
						pNode			= WCS_Pointer <Node> (new Node);
						(*pNode).Index	= I;
						(*pHead).pPrev	= pNode;
						(*pNode).pNext	= pHead;
						pHead			= pNode;
						NumElements++;
						}
					else
						if (I > (*pTail).Index)
								{
								pNode			= WCS_Pointer <Node> (new Node);
								(*pNode).Index	= I;
								(*pTail).pNext	= pNode;
								(*pNode).pPrev	= pTail;
								pTail			= pNode;
								NumElements++;
								}
							else
								if (I == (*pTail).Index)
										pNode = pTail;
									else
										if (I == (*pHead).Index)
												pNode = pHead;
											else
												{
												for (pNode = (*pHead).pNext; I > (*pNode).Index; pNode = (*pNode).pNext);
												if (I < (*pNode).Index)
														{
														WCS_Pointer <Node>	pTemp (new Node);
														(*pTemp).pNext			= pNode;
														(*pTemp).pPrev			= (*pNode).pPrev;
														(*pNode).pPrev			= pTemp;
														(*(*pTemp).pPrev).pNext	= pTemp;
														pNode					= pTemp;
														NumElements++;
														}
													else;	// found the node I'm looking for so just fall out and return
												}
		return (*pNode).Data;
		}

template <class DATA, class INDEX>
	const DATA&	UBArray <DATA, INDEX>::operator [] (const INDEX & I) const //getAt operator
{
		return At(I);
}

template <class DATA, class INDEX>
	const DATA&	UBArray <DATA, INDEX>::At(const INDEX & I) const  
{
	WCS_Pointer <Node>	pNode;
			
		if (pHead.DoesNotExist ())
				{
					throw ElementNotFound;
				}
			else
				if (I < ((*pHead).Index))
						{
							throw ElementNotFound;
						}
					else 
						if (I > (*pTail).Index)
								{
									throw ElementNotFound;
								}				
								if (I == (*pTail).Index)//from this point on, we've found a match
										pNode = pTail;
									else
										if (I == (*pHead).Index)
												pNode = pHead;
											else
												{
												for (pNode = (*pHead).pNext; I > (*pNode).Index; pNode = (*pNode).pNext);
												//for walking doen the ll and setting pNode.Index to the match
												}
			return (*pNode).Data;
		
}

template <class DATA, class INDEX>
	bool UBArray <DATA, INDEX>::Remove(const INDEX & I)
	{
		bool ElementRemoved = false;

		WCS_Pointer <Node>	pNode;

		if (pHead.DoesNotExist ())
			{
				throw ElementNotFound;
			}
			if(NumElements == 1)
				{
					(*pHead).pNext.SetToNull();
					(*pHead).pPrev.SetToNull();
					(*pTail).pNext.SetToNull();
					(*pTail).pPrev.SetToNull();
					pHead.SetToNull();
					pTail.SetToNull();
					NumElements--;
					ElementRemoved = true;
				}				
				else
				{
					if (I < (*pHead).Index)
							{
								throw ElementNotFound;
							}
						else 
							if (I > (*pTail).Index)
									{
										throw ElementNotFound;
									}						
									if (I == (*pTail).Index)
									{																
										((*(*pTail).pPrev).pNext).SetToNull();
										//((*pTail).pNext).SetToNull();
										//((*pTail).pPrev).SetToNull();
										pTail = ((*pTail).pPrev);
										NumElements--;
										ElementRemoved = true;
									}
									else
										if (I == (*pHead).Index)
										{	
											((*(*pHead).pNext).pPrev).SetToNull();
										//	((*pHead).pPrev).SetToNull();
										//	((*pHead).pNext).SetToNull();
											pHead = ((*pHead).pNext);
											NumElements--;
											ElementRemoved = true;
										}
										else
											{
											for (pNode = (*pHead).pNext; I > (*pNode).Index; pNode = (*pNode).pNext);
											if (I < (*pNode).Index)
													{
														((*(*pNode).pNext).pPrev) = (*pNode).pPrev;
														((*(*pNode).pPrev).pNext) = (*pNode).pNext;
														//((*pNode).pPrev).SetToNull();
														//((*pNode).pNext).SetToNull();													
														NumElements--;	
														ElementRemoved = true;
													}
												else;	// found the node I'm looking for so just fall out and return
											}
				}
			return ElementRemoved;
	}

template <class DATA, class INDEX>
	void UBArray <DATA, INDEX>::Delete ()
		{
		if (pHead.Exists ())
				{
				pTail.SetToNull ();
				pCurrent.SetToNull ();
				pHead = (*pHead).pNext;
				while (pHead.Exists ())
					{
					(*pHead).pPrev.SetToNull ();
					pHead = (*pHead).pNext;
					}
				}
			else;
		NumElements = 0;
		}


#endif
