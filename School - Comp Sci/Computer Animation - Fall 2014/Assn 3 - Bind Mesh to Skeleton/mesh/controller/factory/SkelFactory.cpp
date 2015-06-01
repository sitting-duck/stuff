#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "SkelFactory.h"

SkelFactory::SkelFactory()
{
}

Skeleton* SkelFactory::getSkeleton()
{
	return skel;
}

Skeleton* SkelFactory::generateSkelFromFile(const char* _fileName){
	std::string strFileName(_fileName);
	return generateSkelFromFile(strFileName);
}

Skeleton* SkelFactory::generateSkelFromFile(std::string& _fileName)
{
	skelParser = SkelParser(tokenizeFile(_fileName));

	//the parseTokens function is going to analyze each word token individually and populate the elements of the skeleton accordingly
	skelParser.parseTokens();
	skel = &skelParser.skel;

	//if no boxmin and boxmax values are defined, in order to see the skeleton, these values will default to boxmin = -1 and boxmax = 1
	if(skel->skel[0].boxmin[0] == 0){
		skelParser.skel.setBoxesToDefault();
	}

	//derive some matrices from the given file data
	generateLocalMatrices();
	generateWorldMatrices();
	generateTransformMatrices();

	//skel->drawSkel();

	return skel;
}

std::vector<std::string>& SkelFactory::tokenizeFile(std::string& _fileName)
{
	tokenizer.OpenFile(_fileName);
	
	std::string token;
	while(tokenizer.GetToken(token)){
		tokens.push_back(token);
		token.clear();
	}
	return tokens;
}

unsigned int SkelFactory::getNumJoints(){
	return skel->skel.size();
}

void SkelFactory::adjustSkelForRotLimits()
{
}

void SkelFactory::generateLocalMatrices()
{
	for(int i = 0; i < skel->skel.size(); i++){
		skel->skel[i].calcLocalMatrix();
	
		std::cout << "joint " << i << " local matrix " << std::endl << skel->skel[i].local << std::endl;
	}
	
}

void SkelFactory::generateWorldMatrices()
{
	for(int i = 0; i < skel->skel.size(); i++){ 
		
		//parent of -1 indicates node is root
		if(skel->skel[i].parent == -1){
			skel->skel[i].calcWorldMatrix(skel->skel[0].world);
		}
		else
		{
			skel->skel[i].calcWorldMatrix(skel->skel[skel->skel[i].parent].world);
			std::cout << "joint " << i << " world matrix " << std::endl << skel->skel[i].world << std::endl;
		}
		
	}
}

void SkelFactory::generateTransformMatrices()
{
	for(int i = 0; i < skel->skel.size(); i++){
		//skel->skel[i].transform = (skel->skel[i].world) * (skel->skel[i].binding.invert());
		skel->skel[i].transform = (skel->skel[i].binding.invert()) * (skel->skel[i].world);
	}
}
