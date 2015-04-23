
#include "BackProp.h"
// NeuralNet.cpp : Defines the entry point for the console application.
//

#include "backprop.h"

int main(int argc, char* argv[])
{


	// prepare XOR traing data
	double data[][3]={
				0,	0,	0,
				0,	1,	1,
				1,	0,	1,
				1,	1,	0};

	// prepare test data	
	double testData[][2]={
								0,      0,      
                                0,      0,      
                                0,      1,      
                                0,      1,      
                                1,      0,      
                                1,      0,      
                                1,      1,      
                                1,      1     };

	
	// defining a net with 3 layers having 2,1, and 1 neuron respectively,
	// the first layer is input layer i.e. simply holder for the input parameters
	// and has to be the same size as the no of input parameters, in out example 3
	int numLayers = 3, lSz[3] = {2,1,1};

	
	// Learing rate - beta
	// momentum - alpha
	// Threshhold - thresh (value of target mse, training stops once it is achieved)
	double beta = 0.3, alpha = 0.1, Thresh =  0.00001;

	
	// maximum no of iterations during training
	long num_iter = 2000000;

	
	// Creating the net
	CBackProp *bp = new CBackProp(numLayers, lSz, beta, alpha);
	
	std::cout<< std::endl <<  "Now training the network...." << std::endl;	
	for (long i=0; i<num_iter ; i++)
	{
		
		bp->bpgt(data[i%8], &data[i%8][3]);

		if( bp->mse(&data[i%8][3]) < Thresh) {
			std::cout << std::endl << "Network Trained. Threshold value achieved in " << i << " iterations." << std::endl;
			std::cout << "MSE:  " << bp->mse(&data[i%8][3]) 
				 <<  std::endl <<  std::endl;
			break;
		}
		if ( i%(num_iter/10) == 0 )
			std::cout<<  std::endl <<  "MSE:  " << bp->mse(&data[i%8][3]) 
				<< "... Training..." << std::endl;

		if(i == num_iter)
			std::cout << std::endl << i << " iterations completed..." << "MSE: " << bp->mse(&data[(i - 1) % 8][3]) << std::endl;
	}
	
	

	std::cout<< "Now using the trained network to make predictions on test data...." << std::endl << std::endl;	
	for (int i = 0 ; i < 8 ; i++ )
	{
		bp->ffwd(testData[i]);
		//std::cout << testData[i][0]<< "  " << testData[i][1]<< "  "  << testData[i][2]<< "  " << bp->Out(0) << std::endl;
		std::cout << testData[i][0] << "  " << testData[i][1] << "  " << bp->Out(0) << std::endl;
	}

	return 0;
}



