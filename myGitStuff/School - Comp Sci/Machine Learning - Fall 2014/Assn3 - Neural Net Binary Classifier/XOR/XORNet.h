#ifndef XOR_NET_H
#define XOR_NET_H

#include <vector>
#include "TestingExample.h"
#include "TrainingExample.h"

class XORNet{

	int input1;
	int input2;
	int output;

	//outputs
	float hiddenNode1_output;
	float hiddenNode2_output;
	float outputNode_output;

	//weights
	float weight_i1h1;
	float weight_i1h2;
	
	float weight_i2h1;
	float weight_i2h2;
	
	float weight_h1o;
	float weight_h2o;

	float weight_b1h1;
	float weight_b1h2;
	float weight_b2o;

	//weight updates
	float update_i1h1;
	float update_i1h2;
	
	float update_i2h1;
	float update_i2h2;
	
	float update_h1o;
	float update_h2o;
	
	float update_b1h1;
	float update_b1h2;
	float update_b2o;
	
	//previous weight updates
	float prev_update_i1h1;
	float prev_update_i1h2;

	float prev_update_i2h1;
	float prev_update_i2h2;

	float prev_update_h1o;
	float prev_update_h2o;

	float prev_update_b1h1;
	float prev_update_b1h2;
	float prev_update_b2o;

	//bias
	float bias;

	//sums
	float sum_h1;
	float sum_h2;
	float sum_o;

	// deltas
	float delta_o;
	float delta_h1;
	float delta_h2;

	//gradients
	float grad_i1h1;
	float grad_i1h2;
		
	float grad_i2h1;
	float grad_i2h2;
		
	float grad_h1o;
	float grad_h2o;
		
	float grad_b1h1;
	float grad_b1h2;
	float grad_b2o;

	//learning rate
	float learningRate;

	//momentum
	float momentum;


public:
	XORNet();
	void forwardPropogate(std::vector<TrainingExample>& trains, std::vector<TestingExample>& _tests);
	void backPropogate(std::vector<TrainingExample>& trains, std::vector<TestingExample>& _tests);

	float getOutput(int i1, int i2);
	void getOutput(TestingExample&);
	void getOutputs(std::vector<TrainingExample>& trains, std::vector<TestingExample>& _tests);
	bool isNetGood(std::vector<TrainingExample>& trains, std::vector<TestingExample>& tests);
	float sigmoid(float in);
	float delta(float error, float sum);
	float deriv(float sum);
	void printWeights();

};



#endif