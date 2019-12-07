#include "node.h"
#include "Linked_List.h"

//default build
struct Linked_List* build_list()
{
	struct Linked_List* list = malloc(sizeof(struct Linked_List));
	assert(list != NULL);
	
	list->m_first = NULL;
	list->m_last = NULL;
	list->m_size = 0;
	
	return list;
}

//custom build
//struct Linked_List* build_list(struct node* first, struct node* last, int size)
//{
//	struct Linked_List* list = malloc(sizeof(struct Linked_List));
//	assert(list != NULL);
//	
//	list->m_first = first;
//	list->m_last = last;
//	list->m_size = size;
//	
//	return list;
//}

void destroy_list(struct Linked_List* list)
{
	assert(list != NULL);
	
	free(list->m_first);
	free(list->m_last);
	free(list);
}

struct node* create_dummy(struct Linked_List* list)
{	
	struct node* n = malloc(sizeof(struct node));
	assert(list != NULL);
	
	n->m_key = NULL;
	n->m_value = 0;
	n->m_next = NULL;
	
	list->m_first = n;
	list->m_last = n;
	
	return n;
}

struct node* get_node(struct Linked_List* ll, char* key)
{	
	
	struct node* current_node = ll->m_first;
	
	while(current_node != ll->m_last)	
	{
		if(strcmp(key, current_node->m_key) == 0)
		{
			return current_node;
		}
	}
	
	printf("Node %s not found", key);
	printf("Node %s not found", key);
	return NULL;
	
	//if we go through entire list 
		//and don't find anything,
		//print a msg: node not found
}

struct node* build_node(char* key, int value)
{
	struct node* n = malloc(sizeof(struct node));
	assert(n != NULL);
		
	n->m_key = strdup(key);
	n->m_value = value;
		
	return n;
}

int add_node(struct Linked_List* ll, char* key, int val)
{
//todo: before creating new node
//check for duplicates first
//can have duplicate value but not
//duplicate key
	if(get_node(ll, key) != NULL)
	{
		printf("Key already exists.");
		return -1;
	}

	ll->m_first = build_node(key, val);
	
	
	printf("Item added successfully");
	return 1;
}

int search(struct Linked_List* ll, char* key)
{
	struct node* n = get_node(ll, key);
	return n->m_value;
}

int delete_node(struct Linked_List ll, char* key)
{
	return 1;
}

int free_all(struct Linked_List ll)
{
	return 1;
}

