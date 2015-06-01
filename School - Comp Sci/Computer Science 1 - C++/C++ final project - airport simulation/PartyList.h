#ifndef PARTYLIST_H
#define PARTYLIST_H

#include "Party.h"

struct PartyList
{
	unsigned int Size;
	unsigned int Pos;
	Party* myParties;
};


#endif