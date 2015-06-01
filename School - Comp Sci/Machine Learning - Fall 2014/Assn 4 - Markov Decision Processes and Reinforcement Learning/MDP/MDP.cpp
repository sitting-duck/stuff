#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>
#include <random>
#include <iomanip>

#include "MDP.h"

void MDP::init(){

	//set all the utilities to random values. 
	//http://channel9.msdn.com/Events/GoingNative/2013/rand-Considered-Harmful has some good information regarding why I chose to use this delicious random engine

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> dist(0.0F, 100.0F);

	for(int i = 0; i < states.size(); i++){
		//states[i].utility = dist(mt);
		states[i].utility = 0;
	}

}

float MDP::reward(State& state)
{
	return 0;
}

State MDP::transition(State& state, ActionVariable& actionVar)
{
	return *new State();
}

float MDP::utility(State& state)
{
	float max;

	float currentMax = 0;
	float currentUtil = 0;
	ActionVariable currentAction;
	
	//for every action we're going to sum up the probality times the utility of the state change
	//In the code for genererating the policy, you'll see we're going to "keep" the action with the highest utility
	//technically, we're just plugging that utillity into the formula for now so we can return the right number
	for(int i = 0; i < state.actions.size(); i++){
		currentAction = state.actions[i];
		for(int j = 0; j < currentAction.possibilities.size(); j++){
			Possibility currentPossibility = currentAction.possibilities[j];
			currentUtil += currentPossibility.probability * states[currentPossibility.stateChangeTo - 1].utility;
		}
		if(currentUtil > currentMax){
			currentMax = currentUtil;			
		}
		currentUtil = 0;
	}

	return state.reward + (gamma* (currentMax));
}

ActionVariable* MDP::determineOptimalPolicy(unsigned int numIter)
{
	return 0;
}

void MDP::makePolicy()
{
	float currentUtilFromSomeAction = 0 ;
	float currentMaxUtil = (-1) * FLT_MAX ;

	ActionVariable currentBestAction;
	int currentActionIndex = -1;
	int currentBestActionIndex = -1;

	for(int i = 0; i < states.size(); i++){
		
		for(int j = 0; j < states[i].actions.size(); j++){
			
			ActionVariable currentAction = states[i].actions[j];
			currentActionIndex = j;
			//std::cout << "a" << j+ 1 << " ";

			for(int k = 0; k < currentAction.possibilities.size(); k++){
				Possibility currentPossibility = currentAction.possibilities[k];
				currentUtilFromSomeAction += currentPossibility.probability * states[currentPossibility.stateChangeTo - 1].utility;
				//std::cout << currentUtilFromSomeAction << " ";
			}
			
			if(currentUtilFromSomeAction >= currentMaxUtil){
				currentMaxUtil = currentUtilFromSomeAction;
				currentBestAction = currentAction;
				currentBestActionIndex = currentActionIndex;
			}
		
		}

		//std::cout << std::endl;
		policy.push_back(currentBestActionIndex + 1);
	}

}

void MDP::updateUtilities(){
	for(int s = 0; s < states.size(); s++){
		states[s].utility = utility(states[s]);
	}
}

ActionVariable MDP::Bellman(State& state)
{
	return *new ActionVariable();
}

void MDP::printPolicy(){
	for(int i = 0; i < policy.size(); i++){
		std::cout << "(s" << i + 1 << " a" << policy[i] << " " << std::fixed << std::setprecision(3) << states[i].utility << ") ";
	}std::cout << std::endl;
}