#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>
#include <new>

#include "MDP_Parser.h"


State MDP_Parser::getNextState(std::string& line)
{
	//delimiters include tab and space
		const char* delim = " \t";

		//placeholders for tokenizing the current line, these keep the tokenizer moving forward so we don't acknowledge the same space more than once
		size_t prev = 0;
		size_t next = 0;

		//grab the first token, it should e something like "s1" and number the current state
		next = line.find_first_of(delim, prev);

		//make the token using the two place holders prev and next
		std::string token = line.substr(prev, next - prev);

		//extract the number from the token
		unsigned int stateNum = extractNumberFromToken(token);

		//the next token will be a number indicating the reward for being in that state
		prev = next + 1;
		next = line.find_first_of(delim, prev);
		token = line.substr(prev, next - prev);
		int rewardForState = extractNumberFromToken(token);

		//make a state, we're going to grab some more values from the file to put in here,
		State state;

		//next were going to grab the next bit of the file encapsulated in parens. 
		//It should look something like (a1 s1 0.5) or some variation of that
		//we're going to strip the parens and put that string in actionNode
		prev = next;
		next = line.find_first_of("(", prev);
		prev = next + 1;
		next = line.find_first_of(")", prev);
		std::string actionNode = line.substr(prev, next - prev);

		//get the first token of actionNode, it should be something like a1, indicating which action is being described
		prev = 0; next = 0;
		next = actionNode.find_first_of(delim, prev);
		token = actionNode.substr(prev, next - prev);
		unsigned int actionNum = extractNumberFromToken(token);

		//do a check to see if this action has been described before for this state, or if a new action is being described

		unsigned int prevActionNum = 0;
		int stateChangeTo;
		float probability;

		while((next = line.find_first_of("a", prev)) != std::string::npos){
			
				//if the token we got is not an empty string, add it to _attrNames
				if(next - prev != 0){
					prev += 1;
					actionNum = atoi(&line[prev]);
					if(actionNum != prevActionNum){//then we have found a new action variable
						state.actions.push_back(*new ActionVariable());
					}
					else{//we found another possibility for the current variable
						
						//get the first token which has the state num
						next = line.find_first_of("s", prev);
						next +=1;
						stateChangeTo = atoi(&line[prev]);
						prev = next + 1;

						//get the second token which has the probability
						next = line.find_first_of(delim, prev);
						next += 1;
						probability = atof(line.substr(next, line.find_first_of(delim, next)).c_str());

						//make a new possibility and add it to the current action of the current state
						Possibility possibility;
						possibility.stateChangeTo = stateChangeTo;
						possibility.probability = probability;
						state.actions.back().possibilities.back() =   possibility;
					}
				}
				//update the placeholder
				prev = next + 1;
			}

			//reset some variables for the next loop around
			prev = 0; next = 0;
	return state;
}

ActionVariable MDP_Parser::getNextAction()
{
	return *new ActionVariable();
}

Possibility MDP_Parser::getNextActionVariablePossibility()
{
	return *new Possibility;
}

MDP MDP_Parser::getStuff(const char* filename)
{
	std::ifstream file(filename);
	std::string line;

	while(getline(file, line)){
		getNextState(line);
	}
	file.close();
	MDP mdp;
	return mdp;
}

//utils
int MDP_Parser::extractNumberFromToken(std::string token){

	std::string num;

	for(int i = 0; i < token.length(); i++){
		
		if(isdigit(token[i]) ){
			//append one copy of the char at token[i]
			num.append(1, token[i]);
		}
	}

	return atoi(num.c_str());
}