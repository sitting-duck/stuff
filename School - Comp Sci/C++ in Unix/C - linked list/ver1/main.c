#include "node.h"
#include "Linked_List.h"

int main()
{
	char* key;
	int value;
	
	struct Linked_List* ll = ll.build_list();
	struct node* n = create_dummy(ll);	
	
	scanf("Enter key: %s", &key);
	getchar();
	
	scanf("Enter val: %d", &value);
	getchar();
	
	n->m_value = value;
	n->m_key = key;
	
	//ll.add_node(ll, key, value);
	
	printf("If we got here, we added node and nothing broke.\n");
	printf("You just entered: %s", n->m_key);	
	printf("You just enetered: %d", n->m_value);
	
	return 0;
}

