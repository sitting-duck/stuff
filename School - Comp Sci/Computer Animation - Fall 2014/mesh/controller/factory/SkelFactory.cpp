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

	//derive some matrices from the given file data
	generateLocalMatrices();
	generateWorldMatrices();
	generateTransformMatrices();

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
