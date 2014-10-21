#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "WeightController.h"


WeightController::WeightController()
{
}

float WeightController::calcGradient(float incoming, float outputNeuronDelta)
{
	return 0;
}

float WeightController::calcNewWeight(float learningRate, float gradient, float momentum, float prevWeight)
{
	return 0;
}
