#ifndef TRAINING_EXAMPLE
#define TRAINING_EXAMPLE

class TrainingExample{

public:
	int input1;
	int input2;
	float output;

	TrainingExample();
	TrainingExample(int, int, float);
	~TrainingExample();
};

inline TrainingExample::TrainingExample(){
}

inline TrainingExample::TrainingExample(int i1, int i2, float o){
	input1 = i1;
	input2 = i2;
	output = o;
}

inline TrainingExample::~TrainingExample(){

}


#endif