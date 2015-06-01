#ifndef QUEUE_H
#define QUEUE_H

#include "WCS_String.h"
#include "UBArray.h"
#include "ReadString.h"
	
typedef unsigned long ULONG;

class Queue: private UBArray <WCS_String, ULONG>
{
public:

	enum qExceptions {};
	Queue		();
	~Queue	();
	bool	QueueFunc			(WCS_String &);
	bool	DeQueueFunc			();
	bool Print();

	const WCS_String& operator [](const ULONG index) const;
	bool AcceptCommand();
	bool QCommand(WCS_String);
	bool DCommand();

private:
	Queue		(const Queue&);
	void	operator =	(const Queue&);

	ULONG	Head;
	ULONG	Tail;
};

Queue::Queue (): Head (0), Tail(0)
{

}


Queue::~Queue ()
{

}

bool Queue::QueueFunc(WCS_String & D)
{
	(*this).UBArray<WCS_String, ULONG>::operator[](++Tail) = D;//wha?
	
	if(Size() == 1)
	{
		Head = Tail;
	}

	return true;
}

bool Queue::DeQueueFunc()
{
	// if there's nothing in the queue then
	// nothing is removed...
	if (Size() == 0)
		return false;

	// if there's only one item then we'll kill it and
	// reset everything
	if (Size() == 1) {
		// kill the item
		Remove(Head);
		// since there's nothing left we'll reset head and tail
		Head = 0;
		Tail = 0;
		// true = something was removed
		return true;
	}

	// if there was stuff then kill head and bump it up the q
	Remove(Head++);
	return true;
}

const WCS_String& Queue::operator [](const ULONG index) const
{
	if ((index >= Head) && (index <= Tail))
		return UBArray<WCS_String, ULONG>::operator[](index);
	else
		throw ElementNotFound;
}

bool Queue::Print()
{
	cout << endl;

	if(Head == 0)
	{
		cout << "Queue is empty, you can't remove anything, try putting" << endl;
		cout << "some stuff in the queue using <q string>." << endl;
		return true;
	}
	

	for(long i = Head; i != (Tail + 1); i++)
	{
		cout << (*this)[i] << endl;
	}
	cout << endl;

	return true;
}

bool Queue::AcceptCommand()
{
	WCS_String command;
	command.Copy( (const char*)ReadString() );

	char c;
	command.GetAt(c, 0);

	switch(c)
	{
		case 'q':
		case 'Q':
			QCommand(command);
			break;
		case 'd':
		case 'D':
			DCommand();
			break;
		case 'x':
		case 'X':
			exit(0);
			break;
		default:
			cout << "Invalid Input. Enter <q string> <d> or <x>. (Note: do not enter carrots)" << endl;
			AcceptCommand();
			break;
	}

	return true;
}

bool Queue::QCommand(WCS_String s)
{
	char* p;
	p= s.getPtr();
	
	const char* first;
	const char* second;

	first = strtok(p, " ");
	second = strtok(NULL, "\n");

	WCS_String ws(second);
	QueueFunc(ws);

	cout << second << " was added." << endl;
	return true;
}

bool Queue::DCommand()
{
	if(Head == 0)
	{
		return true;
	}
	

	cout << (*this)[Head] << " was removed." << endl;
	DeQueueFunc();
	return true;
}

#endif
