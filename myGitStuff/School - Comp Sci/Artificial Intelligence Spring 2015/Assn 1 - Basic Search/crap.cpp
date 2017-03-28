#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>

void crapHolder()
{
	std::vector<int> numq = { 1, 1, 2, 2, 3, 3, 5 };

	auto lower = std::lower_bound(numq.begin(), numq.end(), 5);

	auto upper = std::upper_bound(numq.begin(), numq.end(), 3);

	std::cout << "lower was " << *lower << std::endl;

	std::cout << "upper was " << *upper << std::endl;

	//vector, insert the element we want in the next space after the iterator

	//lets insert a 4 in between the 3 and the five
	numq.insert(lower, 4);

	std::cout << "after inserting 4" << std::endl;
	for(unsigned int i = 0; i < numq.size(); i++){
		std::cout << numq[i] << " ";
	}
	std::cout << std::endl;
}
