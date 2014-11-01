
#include <iostream>
#include "MDP_Parser.h"
#include "MDP.h"

void main(int argc, char* argv[]){

	if(argc != 5){
		std::cout << "Error: incorrect number of arguments. Must insert 4 arguments." << std::endl;
		std::cout << "syntax is: " << argv[0] << " <num states> <num actions> <inputfile.dat> <discount factor>" << std::endl;
		exit(1);
	}
	
	MDP_Parser parser;

	MDP mdp = parser.getStuff(argv[3]);

	
}