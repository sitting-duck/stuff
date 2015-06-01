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
		float rewardForState = extractNumberFromToken(token);

		//make a state, we're going to grab some more values from the file to put in here,
		State state;
		state.reward = rewardForState;
		
		prev = next;

		while(next <= line.size() - 1){
			//next were going to grab the next bit of the file encapsulated in parens. 
			//It should look something like (a1 s1 0.5) or some variation of that
			//we're going to strip the parens and put that string in actionNode
			next = line.find_first_of("(", prev);
			if(next >= line.size() -1){break;}
			prev = next + 1;
			next = line.find_first_of(")", prev);
			std::string actionNode = line.substr(prev, next - prev);
			prev = next;

			//this will parse the data for this possibility and figure whether to add it to an existing ActionVar or a new ActionVar
			getAndSetNextActionVariablePossibility(state, actionNode);
		}
		
	return state;
}

void MDP_Parser::getAndSetNextActionVariablePossibility(State& state, std::string& actionNode)

{
	//delimiters include tab and space
		const char* delim = " \t";

	//get the first token of actionNode, it should be something like a1, indicating which action is being described
		size_t prev = 0; size_t next = 0;
		next = actionNode.find_first_of(delim, prev);
		std::string token = actionNode.substr(prev, next - prev);
		unsigned int actionNum = extractNumberFromToken(token);

		//inside each ActionVariable is a set of Possibilities.
		std::vector<Possibility>* possibilities;
		
		//do a check to see if this action has been described before for this state, or if a new action is being described		
		if(state.actions.size() < actionNum){
			//new action being defined
			ActionVariable action;
			state.actions.push_back(action);

			//the new possibility will be added to the new ActionVariable we just made
			possibilities = &state.actions.back().possibilities;
		}
		else{
			//we take the previously defined action of the same number and we're going to add this possibility
			possibilities = &state.actions[actionNum - 1].possibilities;
		}

		//get the next token.  This token will specify the state change for this possibility
		prev = next + 1;
		next = actionNode.find_first_of(delim, prev);
		token = actionNode.substr(prev, next - prev);
		int changeToState = extractNumberFromToken(token);

		//get the next token.  This token will specify the probability of the state change just described
		prev = next + 1;
		next = actionNode.find_first_of(delim, prev);
		token = actionNode.substr(prev, next - prev);
		float probability = extractNumberFromToken(token);

		//Make Possibility and populate it with state change and probability
		Possibility possibility;
		possibility.stateChangeTo = changeToState;
		possibility.probability = probability;

		//add it to the current state
		possibilities->push_back(possibility);
}

MDP MDP_Parser::getStuff(const char* filename)
{
	MDP mdp;
	
	std::ifstream file(filename);
	std::string line;

	while(getline(file, line)){
		mdp.states.push_back(getNextState(line));
		line.clear();
	}
	file.close();
	
	return mdp;
}

//utils
float MDP_Parser::extractNumberFromToken(std::string token){

	std::string num;

	for(int i = 0; i < token.length(); i++){
		
		if(isdigit(token[i]) || token[i] == '.' || token[i] == '-' ){
			//append one copy of the char at token[i]
			num.append(1, token[i]);
		}
	}

	return atof(num.c_str());
}