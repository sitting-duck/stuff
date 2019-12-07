//* Description *//
// Title: CPU
// Authors: Brian Quackenbush, Tyler Reed, Ashley Tharp
// Defines the CPU Class

//* Header Definition *//
#ifndef CPU_H
#define CPU_H

//* Definitions *//
#define PIPE_STRING_SIZE 20
#define INT_C_STRING_SIZE 11
#define ADDRESS_C_STRING_SIZE 5
#define PROGRAM_MEMORY_SIZE 1000
#define INTERRUPT_MEMORY_SIZE 1000

//* Libraries *//
#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <cstdlib>
#include <cstring>

//* Namespaces *//
using namespace std;

//* CPU Class *//
class CPU
{
	//* Class Variables *//
	// Private Variables
	private:
		// Enumerations
		enum modes {USER_MODE, SYSTEM_MODE};

		// Register Variables
		int program_counter;
		int stack_pointer;
		int instruction_register;
		int accumulator;
		int x;
		int y;

		// Pipe Variables
		int input_stream;
		int output_stream;

		// Mode Variable
		int mode;

		// Debug Variables
		bool timeToDie;
		int debug;

	//* Class Methods *//
	// Public Methods
	public:
		// Constructor and Destructor
		CPU(int, int);
		~CPU();

		// Register Accessors
		int getPC();
		int getSP();
		int getIR();
		int getAC();
		int getX();
		int getY();

		// Register Mutators
		int setPC(int program_counter);
		int setSP(int stack_pointer);
		int setIR(int instruction_register);
		int setAC(int accumulator);
		int setX(int x);
		int setY(int y);

		// Memory Functions
		int getNextInstruction();
		int getValueAtAddress(int address, bool instruction);
		void setValueAtAddress(int address);
		void pushToStack();
		int popFromStack();

		// Instruction Functions
		void doNextInstruction();
		void instruction_loadValue(); 				// Case 1
		void instruction_loadAddress(); 			// Case 2
		void instruction_storeAddress();			// Case 3
		void instruction_addX();				// Case 4
		void instruction_addY();				// Case 5
		void instruction_subtractX();				// Case 6
		void instruction_subtractY();				// Case 7
		void instruction_getRandomInt();			// Case 8
		void instruction_putPort();				// Case 9
		void instruction_copyToX();				// Case 10
		void instruction_copyToY();				// Case 11
		void instruction_copyFromX();				// Case 12
		void instruction_copyFromY();				// Case 13
		void instruction_jumpToAddress();			// Case 14
		void instruction_jumpToAddressIfEqualToZero();		// Case 15
		void instruction_jumpToAddressIfNotEqualToZero();	// Case 16
		void instruction_callAddress();				// Case 17
		void instruction_return();				// Case 18
		void instruction_increaseX();				// Case 19
		void instruction_decreaseX();				// Case 20
		void instruction_loadFromAddressPlusX();		// Case 21
		void instruction_loadFromAddressPlusY();		// Case 22
		void instruction_push();				// Case 23
		void instruction_pop();					// Case 24
		void instruction_interrupt();				// Case 25
		void instruction_interruptReturn();			// Case 26
		void instruction_end();					// Case 50

		// Utilities
		void itoa(int n, char s[]);
		void reverse(char s[]);
		bool isTimeToDie();

		//* Private Methods *//
		// Debug Functions
		void debugHeader();
};

// Returns whether or not it is time for the CPU to be terminiated
inline bool CPU::isTimeToDie()
{
	return timeToDie;
}

//* End Header Definition *//
#endif
