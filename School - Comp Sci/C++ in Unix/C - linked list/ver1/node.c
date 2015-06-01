#include "Linked_List.h"
#include "node.h"
#include "utils.h"


void destroy_node(struct node* n)
{
	assert(n != NULL);
		
	free(n->m_key);
	free(n->m_next);
	free(n);	
}

void print_node(struct node *n)
{
	printf("Key: %s\n", n->m_key);
	printf("Value: %d\n", n->m_value);
}