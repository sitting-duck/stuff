#ifndef SKEL_PARSER_H
#define SKEL_PARSER_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>
#include <map>

#include "Skeleton.h"
#include "BallJoint.h"
#include "Tokenizer.h"
#include "strIsNum.h"

class SkelFactory;

class SkelParser
{
	friend SkelFactory;

public:
	Skeleton skel;
	//Skeleton skeleton;

	enum TokenState {
		start,
		afterBallJoint,
		afterOffset,
		afterBoxmin,
		afterBoxMax,
		afterPoseToken,
		afterRotLimit,
		afterCloseCurly,
		end,
		numStates
	};
	
	enum TokenType{
		badToken,
		ballJointToken,
		offsetToken,
		boxminToken,
		boxMaxToken,
		poseToken,
		rotLimitToken,
		closeCurlyToken,
		numTokenTypes
	};

	typedef TokenState(SkelParser::*TokenFunc) (std::string&);

	std::vector<std::string> tokens;

	std::map<std::string, SkelParser::TokenType> keywords;

	std::map<std::string, SkelParser::TokenType>::iterator it;

	static TokenFunc StateFunction[];

	unsigned int numOpenCurlies;

	static unsigned char StateTable[numTokenTypes][numStates];

	unsigned int numJoints;

	BallJoint* currJoint;

	SkelParser();

	SkelParser(std::vector<std::string>& _tokens);

	TokenState gotBadToken(std::string& _str);

	TokenState gotJointAttrToken(std::string& _str);

	TokenState gotBallJointToken(std::string& _str);

	TokenState gotCloseCurly(std::string& _str);

	void parseTokens();

	TokenType getTokenType(std::string& _str);

	std::string getNextToken();

};
#endif
