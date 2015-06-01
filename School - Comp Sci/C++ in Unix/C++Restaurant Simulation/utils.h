#ifndef UTILS_H
#define UTILS_H

#include <cstring>
void copyList(int numItems, void* dest, void* source)
{
	memcpy(dest, source, sizeof(void*)*numItems);
}
#endif
