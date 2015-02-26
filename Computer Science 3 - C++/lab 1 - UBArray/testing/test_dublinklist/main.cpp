#include <iostream>
#include "double_linked.h"
     
int main()
{
int arr[] = { 4, 6, 8, 32, 19 } ;
double_linked<int> dlist ( arr );
dlist.push_back( 11 );
dlist.push_front( 100 );
while( dlist )
std::cout << dlist.pop_back() << " ";
}