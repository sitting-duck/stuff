
#include <iostream>
#include "XORNet.h"

XORNet::XORNet(){

	weight_i1h1 = 5;
	weight_i1h2 = -6;

	weight_i2h1 = -6;
	weight_i2h2 = 6;

	weight_h1o = 10;
	weight_h2o = 10;

	weight_b1h1 = -3;
	weight_b1h2 = -3;
	weight_b2o = -5;

	//init bias
	bias = 1;

	//init sums
	sum_h1 = 0;
	sum_h2 = 0;
	sum_o  = 0;
	
	//init learning rate
	learningRate = 0.7;

	//init momentum
	momentum = 0.3;

	//init previous weight updates
	prev_update_i1h1 = 0;
	prev_update_i1h2 = 0;

	prev_update_i2h1 = 0;
	prev_update_i2h2 = 0;

	prev_update_h1o  = 0;
	prev_update_h2o  = 0;

	prev_update_b1h1 = 0;
	prev_update_b1h2 = 0;
	prev_update_b2o  = 0;
}

void XORNet::forwardPropogate(std::vector<TrainingExample>& trains, std::vector<TestingExample>& tests){
	getOutputs(trains, tests);
}
void  XORNet::backPropogate(std::vector<TrainingExample>& trains, std::vector<TestingExample>& tests){

	for(int i = 0; i < tests.size(); i++){
		//get delta for output node
		float error_o = trains[i].output - tests[i].output;
		delta_o = delta(error_o, sum_o);

		//get delta for hidden node 1
		delta_h1 = deriv(sum_h1) * weight_h1o * delta_o;

		//get delta for hidden node 2
		delta_h2 = deriv(sum_h2) * weight_h2o * delta_o;

		//calculate all the gradients of all the weights
		grad_i1h1 = input1 * delta_o;
		grad_i1h2 = input1 * delta_o;

		grad_i2h1 = input2 * delta_o;
		grad_i2h2 = input2 * delta_o;

		grad_h1o = hiddenNode1_output * delta_o;
		grad_h2o = hiddenNode2_output * delta_o;

		grad_b1h1 = bias * delta_o;
		grad_b1h2 = bias * delta_o;
		grad_b2o  = bias * delta_o;

		//calc weight updates
		update_i1h1 = ((-1) * learningRate * grad_i1h1) + (momentum * prev_update_i1h1);
		update_i1h2 = ((-1) * learningRate * grad_i1h2) + (momentum * prev_update_i1h2);
				    								
		update_i2h1 = ((-1) * learningRate * grad_i2h1) + (momentum * prev_update_i2h1);
		update_i2h2 = ((-1) * learningRate * grad_i2h2) + (momentum * prev_update_i2h2);
				  								
		update_h1o = ((-1) *  learningRate * grad_h1o) +  (momentum * prev_update_h1o);
		update_h2o = ((-1) *  learningRate * grad_h2o) +  (momentum * prev_update_h2o);
													
		update_b1h1 = ((-1) * learningRate * grad_b1h1) + (momentum * prev_update_b1h1);
		update_b1h2 = ((-1) * learningRate * grad_b1h2) + (momentum * prev_update_b1h2);
		update_b2o  = ((-1) * learningRate * grad_b2o)  + (momentum * prev_update_b2o);

		//update all the weights
		weight_i1h1 += update_i1h1;
		weight_i1h2 += update_i1h2;

		weight_i2h1 += update_i2h1;
		weight_i2h2 += update_i2h2;

		weight_h1o += update_h1o;
		weight_h2o += update_h2o;

		weight_b1h1 += update_b1h1;
		weight_b1h2 += update_b1h2;
		weight_b2o += update_b2o;

		//set the weight updates to prev weight updates
		prev_update_i1h1 = update_i1h1;
		prev_update_i1h2 = update_i1h2;

		prev_update_i2h1 = update_i2h1;
		prev_update_i2h2 = update_i2h2;

		prev_update_h1o = update_h1o;
		prev_update_h2o = update_h2o;

		prev_update_b1h1 = update_b1h1;
		prev_update_b1h2 = update_b1h2;
		prev_update_b2o = update_b2o;

	}

	
}

float XORNet::getOutput(int i1, int i2){

	input1 = i1;
	input2 = i2;

	//generate output of hidden node 1
	float fromInput1 = input1 * weight_i1h1;
	float fromInput2 = input2 * weight_i2h1;
	float fromBias1h1 = bias * weight_b1h1;

	hiddenNode1_output = sigmoid(fromInput1 + fromInput2 + fromBias1h1);

	//sum for hidden node 1
	sum_h1 = fromInput1 + fromInput2 + fromBias1h1;
	
	//generate output of hidden node 2
	fromInput1 = input1 * weight_i1h2;
	fromInput2 = input2 * weight_i2h2;
	float fromBias1h2 = bias * weight_b1h2;

	hiddenNode2_output = sigmoid(fromInput1 + fromInput2 + fromBias1h2);

	//sum for hidden node 2
	sum_h2 = fromInput1 + fromInput2 + fromBias1h2;

	//generate output of output node
	float from_h1 = hiddenNode1_output * weight_h1o;
	float from_h2 = hiddenNode2_output * weight_h2o;
	float fromBias2o = bias * weight_b2o;

	outputNode_output = sigmoid(from_h1 + from_h2 + fromBias2o);
	return outputNode_output;

	//sum for output node
	sum_o = from_h1 + from_h2 + fromBias2o;
}


void XORNet::getOutput(TestingExample& t){
	t.output = getOutput(t.input1, t.input2);
}

void XORNet::getOutputs(std::vector<TrainingExample>& trains, std::vector<TestingExample>& tests){
	
	float error;

	std::cout << "tests" << std::endl;
	for(int i = 0; i < tests.size(); i++){
		getOutput(tests[i]);
		std::cout << tests[i].input1 << " " << tests[i].input2 << " " << tests[i].output << std::endl;
	}
}

bool XORNet::isNetGood(std::vector<TrainingExample>& trains, std::vector<TestingExample>& tests){
	for(int i = 0; i < trains.size(); i++){
		if(trains[i].output != tests[i].output){
			std::cout << "net is not good yet" << std::endl;
			return false;
		}
	}
	
	std::cout << "net is good" << std::endl;
	return true;
}

float XORNet::sigmoid(float in)
{
	//std::cout << "sm: " << (float)(1 / (1 + exp((-1)*in))) << std::endl;
	return (float)(1 / (1 + exp((-1)*in)));
}

float XORNet::delta(float error, float sum){
	return error * deriv(sum);
}
float XORNet::deriv(float sum){
	return (sigmoid(sum))*(1 - sigmoid(sum));
}

void XORNet::printWeights(){
	std::cout << "i1h1 " << weight_i1h1 << std::endl;
	std::cout << "i1h2 " << weight_i1h2 << std::endl;
	std::cout << "i2h1 " << weight_i2h1 << std::endl;
	std::cout << "i2h2 " << weight_i2h2 << std::endl;
	std::cout << "h1o "  << weight_h1o  << std::endl;
	std::cout << "h2o "  << weight_h2o  << std::endl;
	std::cout << "b1h1 " << weight_b1h1 << std::endl;
	std::cout << "b1h2 " << weight_b1h2 << std::endl;
	std::cout << "b2o "  << weight_b2o  << std::endl;
}

