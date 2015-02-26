#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "node.h"

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>


typedef struct Linked_List
{
	//vars
	struct node* m_first;
	struct node* m_last;
	
	int m_size;
			
}myList;

typedef struct node
{	
	char* m_key; 
	int m_value;
	struct node* m_next;	
}myNode;

#endif