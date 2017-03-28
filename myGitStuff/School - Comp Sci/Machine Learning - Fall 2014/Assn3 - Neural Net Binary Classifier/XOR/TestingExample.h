#ifndef TESTING_EXAMPLE
#define TESTING_EXAMPLE

class TestingExample{

public:
	int input1;
	int input2;
	float output;

	TestingExample();
	TestingExample(int, int);
	~TestingExample();
};

inline TestingExample::TestingExample(){
}

inline TestingExample::TestingExample(int i1, int i2){
	input1 = i1;
	input2 = i2;
}

inline TestingExample::~TestingExample(){

}


#endif