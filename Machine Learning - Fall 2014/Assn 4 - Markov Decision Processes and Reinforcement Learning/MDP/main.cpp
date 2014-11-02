
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

	//set the gamma with the discount factor given from the terminal args passed to main
	mdp.gamma = atof(argv[4]);

	//this mainly sets the utilities of all the states to random nums 0.0-100.0. 
	mdp.init();

	for(int n = 0; n < 5; n++){
		mdp.makePolicy();
		
		mdp.updateUtilities();

		std::cout << "after iter " << n << " " ; mdp.printPolicy();

		mdp.policy.clear();
	}
}