
#include <iostream>
#include "NetTeach.h"

void main(int argc, char* argv[]){

	if(argc != 5){
		std::cout << "Error: incorrect number of arguments. Must insert 4 arguments." << std::endl;
		std::cout << "syntax is: " << argv[0] << " <trainingfile.dat> <testingfile.dat> <learning rate> <num iterations>" << std::endl;
		exit(1);
	}

	std::cout << "training file is: " << argv[1] << std::endl;
	std::string trainingFile = argv[1];
	std::string lastfour = trainingFile.substr(trainingFile.size() -4, trainingFile.size());
	if( lastfour.compare(".dat") != 0){
		trainingFile.append(".dat");
	}

	std::cout << "testing file is: " << argv[2] << std::endl;
	std::string testingFile = argv[2];
	lastfour = testingFile.substr(testingFile.size() -4, testingFile.size());
	if( lastfour.compare(".dat") != 0){
		testingFile.append(".dat");
	}

	std::cout << "learning rate is: " << argv[3] << std::endl;
	float learningRate = atof(argv[3]);

	std::cout << "num iterations to teach network is: " << argv[4] << std::endl;
	unsigned int numIter = atoi(argv[4]);

	std::cout << "if the above are not correct please exit the program and re-enter the params in the order <trainingfile.dat> <testingfile.dat> <learning rate> <num iterations>" << std::endl;

	//input has been taken, now make an instance of NetTeach with the input
	NetTeach teacher = NetTeach(learningRate, numIter);

	//get training examples from file and store them
	teacher.setTrainingExamples(teacher.getExamplesFromFile(trainingFile));

	//get testing examples from file and store them
	teacher.setTestingExamples(teacher.getExamplesFromFile(testingFile));
}