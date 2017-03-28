#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <regex>
#include <assert.h>
#include "SkelParser.h"

SkelParser::TokenFunc SkelParser::StateFunction[] = {
	&SkelParser::gotBadToken,					//0
	&SkelParser::gotBallJointToken,				//1
	&SkelParser::gotCloseCurly,					//2
	&SkelParser::gotJointAttrToken				//3
};

unsigned char SkelParser::StateTable[SkelParser::numTokenTypes][SkelParser::numStates] = {
				//start   afterBallJoint   afterOffset   afterBoxmin   afterBoxMax    afterPose  afterRotLimit   afterCloseCurly   
/*badToken*/		{0,			0,				0,				0,			0,			0,				0,				0	},
/*ballJoint*/		{1,			0,				1,				1,			1,			1,				1,				1	},
/*offset*/			{0,			3,				0,				3,			3,			3,				3,				0	},
/*boxmin*/			{0,			3,				3,				0,			3,			3,				3,				0	},
/*boxMax*/			{0,			3,				3,				3,			0,			3,				3,				0	},
/*pose*/			{0,			3,				3,				3,			3,			0,				3,				0	},
/*rotLimit*/		{0,			3,				3,				3,			3,			3,				3,				0	},
/*closeCurly*/		{0,			2,				2,				2,			2,			2,				2,				2   }
};

SkelParser::SkelParser(std::vector<std::string>& _tokens)
{
	tokens = _tokens;
	numJoints = 0;
	currJoint = NULL;
	numOpenCurlies = 0;

	keywords["balljoint"] = SkelParser::ballJointToken;
	keywords["offset"] =    SkelParser::offsetToken;
	keywords["boxmin"] =    SkelParser::boxminToken;
	keywords["boxmax"] =    SkelParser::boxMaxToken;
	keywords["rotxlimit"] = SkelParser::rotLimitToken;
	keywords["rotylimit"] = SkelParser::rotLimitToken;
	keywords["rotzlimit"] = SkelParser::rotLimitToken;
	keywords["pose"] =      SkelParser::poseToken;
	keywords["}"] =			SkelParser::closeCurlyToken;
}

SkelParser::SkelParser(){}

SkelParser::TokenState SkelParser::gotBadToken(std::string& _str)
{
	std::cout << "got bad token " << _str <<  std::endl;
	return SkelParser::end;
}

SkelParser::TokenState SkelParser::gotJointAttrToken(std::string& _str){
	
	int tokenType;
	int axis;
	//find the token type for this string
	it = keywords.find(_str);
	
	//will hold the address of the attr we are going to update
	Vector3* v = NULL;
	Matrix3* m = NULL;

	//most attrs input 3 values with the exception of rotlimits which only input 2.
	int numValues;
	
	//switch will use token type to determine which type of joint attr
	switch(it->second){
	case offsetToken:
		v = &currJoint->offset;
		numValues = 3;
		break;
	case boxminToken:
		v = &currJoint->boxmin;
		numValues = 3;
		break;
	case boxMaxToken:
		v = &currJoint->boxmax;
		numValues = 3;
		break;
	case rotLimitToken:
		m = &currJoint->rotLimit;
		if(_str == "rotxlimit"){ axis = 0; }
		else if(_str == "rotylimit"){ axis = 1; }
		else if(_str == "rotzlimit"){ axis = 2; }
		numValues = 2;
		break;
	case poseToken:
		v = &currJoint->pose;
		numValues = 3;
		break;
	}

	//begin the loop for getting the values from the file
	float num;
	std::string strnum;
	for(int i = 0; i < numValues; i++){
		strnum = getNextToken();
		if(strIsNumber((char*)strnum.c_str())){
			num = atof(strnum.c_str());
		}
		else{
			std::cout << "Error: SkelParser::gotJointAttrToken:: " << _str << " value: " << strnum << " is not a valid joint attr value" << std::endl;
		}

		//if m != null, that means that we are setting a rotational limit on a joint
		//rotlimit is 2d so requires axis value
		if(m != NULL){
			m->setAt(axis, i, num);
			currJoint->rotLimitDefined = true;
		}
		else{//all other attrs are 1d so we can just use index value i
			v->operator[](i) = num;
		}
	}
	return (SkelParser::TokenState)it->second;
}

SkelParser::TokenState SkelParser::gotBallJointToken(std::string& _str)
{
	//std::cout << "got balljoint keyword token" << std::endl;
	
	//get balljoint name from file
	std::string jointName = getNextToken();

	//check that the string is a valid joint name
	std::regex var_name_regex(R"([a-zA-Z_][a-zA -Z_\d]*)");
	if(!regex_search(jointName, var_name_regex)){
		std::cout << "Error: invalid joint name " << jointName << "found." << std::endl;
		return end;
	}
	
	//if we got here, then joint name was valid
	//std::cout << "got joint name: " << jointName << std::endl;
	

	//create joint using proper name and index
	BallJoint joint = BallJoint(numJoints, jointName);
	
	//grab the next token. To be valid, the next token must be a curly brace
	std::string openCurly = getNextToken();

	if(openCurly != "{")
	{
		std::cout << "error: expected open curly brace" << std::endl;
		gotBadToken(openCurly);
	}
	else
	{
		numOpenCurlies++;
	}
	
	//if joint is not first, then set the parent node to proper index
	//joint.parent is -1 by default
	if(numJoints != 0){
		//set parent
		joint.parent = currJoint->index;
	}
	skel.push(joint);
	//the joint we just made is the new currJoint until we find a closing curly brace
	currJoint = &skel[numJoints];
	numJoints++;
	
	return SkelParser::afterBallJoint;
}

/*
* In a skel file a close curly essentially indicates that the current joint has been defined, and scope returns to the previous joint defined that is still not closed by
* a curly brace
*/
SkelParser::TokenState SkelParser::gotCloseCurly(std::string& _str)
{
	
	numOpenCurlies--;
	//if currJoint is root, currJoint remains currJoint, else currJoint becomes it's parent
	if(currJoint->index != 0){
		currJoint = &skel[currJoint->parent];
		//std::cout << "got close curly. currJoint now = " << currJoint->name << std::endl;
	}
	
	return SkelParser::afterCloseCurly;
}

void SkelParser::parseTokens()
{
	TokenState currentState = start;
	std::string currentToken;
	TokenType currentTokenType;
	
	while(currentState != end){

		//no more tokens means exit loop 
		if(tokens.size() == 0){ currentState = end; break; }
		
		//get next token
		currentToken = getNextToken();
		
		//detrmine token type
		currentTokenType = getTokenType(currentToken);
		
		//if we haven't reached end state call appropriate callback based on state and token type
		if(currentState != end){
			TokenState(SkelParser::*TokenFunc) (std::string&) = StateFunction[StateTable[currentTokenType][currentState]];
			currentState = (this->*TokenFunc)(currentToken);
		}
	}
}

SkelParser::TokenType SkelParser::getTokenType(std::string& _str)
{
	it = keywords.find(_str);

	if(it != keywords.end()){ //token is a keyword
		return it->second;	//return token type
	}
	else{
		return badToken;
	}
}

std::string SkelParser::getNextToken()
{
	std::string token = tokens.front();
	tokens.erase(tokens.begin());
	return token;
}
