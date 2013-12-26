//* Description *//
// Title: CPU
// Authors: Brian Quackenbush, Tyler Reed, Ashley Tharp
// Defines the Functions for the CPU Class

//* Libraries *//
#include "CPU.h"

//* Constructor *//
// Creates the CPU Object with an Input and Output Stream
CPU::CPU(int input, int output): timeToDie(false)
{
	this -> input_stream = input;
	this -> output_stream = output;

	this -> program_counter = 0;
	this -> stack_pointer = PROGRAM_MEMORY_SIZE - 1;
	this -> instruction_register = 0;
	this -> accumulator = 0;
	this -> x = 0;
	this -> y = 0;

	this -> mode = USER_MODE;

	srand(time(NULL));

	// Debug Variables
	this -> debug = 0;

	this -> debugHeader();

	if(this -> debug > 0)
		cout << " -> CPU | Object Initialized" << endl;
}

//* Destructor *//
// Destroys the CPU Object as cleanly as possible
CPU::~CPU()
{
	this -> debugHeader();

	if(this -> debug > 0)
		cout << " -> CPU | Object Destroyed" << endl;

	// Nothing to Delete
}

//* Register Accessors *//
// Returns the Program Counter
int CPU::getPC()
{
	return this -> program_counter;
}

// Returns the Stack Pointer
int CPU::getSP()
{
	return this -> stack_pointer;
}

// Returns the Instruction Register
int CPU::getIR()
{
	return this -> instruction_register;
}

// Returns the Accumulator Value
int CPU::getAC()
{
	return this -> accumulator;
}

// Returns the X Value
int CPU::getX()
{
	return this -> x;
}

// Returns the Y Value
int CPU::getY()
{
	return this -> y;
}

//* Mutator Methods *//
// Sets the Program Counter
int CPU::setPC(int program_counter)
{
	int old_PC = this -> program_counter;
	this -> program_counter = program_counter;

	if(this -> debug > 0)
		cout << "\t -> setPC(" << program_counter << ") | " <<
		"Old PC: " << old_PC << ", New PC: " << this -> program_counter << endl;

	return old_PC;
}

// Sets the Stack Pointer
int CPU::setSP(int stack_pointer)
{
	int old_SP = this -> stack_pointer;
	this -> stack_pointer = stack_pointer;

	if(this -> debug > 0)
		cout << "\t -> setSP(" << stack_pointer << ") | " <<
		"Old SP: " << old_SP << ", New SP: " << this -> stack_pointer << endl;

	return old_SP;
}

// Sets the Instruction Register
int CPU::setIR(int instruction_register)
{
	int old_IR = this -> instruction_register;
	this -> instruction_register = instruction_register;

	if(this -> debug > 0)
		cout << "\t -> setIR(" << instruction_register << ") | " <<
		"Old IR: " << old_IR << ", New IR: " << this -> instruction_register << endl;

	return old_IR;
}

// Sets the Accumulator Value
int CPU::setAC(int accumulator)
{
	int old_AC = this -> accumulator;
	this -> accumulator = accumulator;

	if(this -> debug > 0)
		cout << "\t -> setAC(" << accumulator << ") | " <<
		"Old AC: " << old_AC << ", New AC: " << this -> accumulator << endl;

	return old_AC;
}

// Sets the X Value
int CPU::setX(int x)
{
	int old_X = this -> x;
	this -> x = x;

	if(this -> debug > 0)
		cout << "\t -> setX(" << x << ") | " <<
		"Old X: " << old_X << ", New X: " << this -> x << endl;

	return old_X;
}

// Sets the Y Value
int CPU::setY(int y)
{
	int old_Y = this -> y;
	this -> y = y;

	if(this -> debug > 0)
		cout << "\t -> setY(" << y << ") | " <<
		"Old Y: " << old_Y << ", New Y: " << this -> y << endl;

	return old_Y;
}

//* Memory Functions *//
// Returns the Next Instruction from Memory
int CPU::getNextInstruction()
{
	if(this -> debug > 0)
		cout << "\t -> getNextInstruction() | " <<
		"PC: " << this -> program_counter << ", IR: " << this -> instruction_register << endl;

	this -> getValueAtAddress(this -> program_counter, true);
	this -> program_counter++;

	if(this -> debug > 1)
		cout << "\t\t -> [getNextInstruction] Getting Next Instruction [" << this -> program_counter - 1 << "]: " << this -> instruction_register << endl;

	return this -> instruction_register;
}

// Returns the Value at the specified Address in Memory
int CPU::getValueAtAddress(int address, bool instruction)
{
	// Create the Character String
	char c_string[PIPE_STRING_SIZE] = {'\0'};

	// Initialize the String to be sent (Read Request Value is 0)
	string str = "0 ";

	// Create the Character Strings
	char mode_c_string[2] = {'\0'};
	char address_c_string[ADDRESS_C_STRING_SIZE] = {'\0'};

	// Convert the Mode and Address to Character Strings
	itoa(this -> mode, mode_c_string);
	itoa(address, address_c_string);

	// Append the String with the Mode and Address (Format: "0 M XXXX")
	str.append(mode_c_string);
	str.append(" ");
	str.append(address_c_string);

	// Covert the String into a Character String
	strcpy(c_string, str.c_str());

	// Send the Read Request to Memory through the Pipe
	write(this -> output_stream, &c_string, PIPE_STRING_SIZE);

	// Determine which Register to set the Value to
	if(instruction)
	{
		// Set Value to Instruction Register
		read(this -> input_stream, &this -> instruction_register, sizeof(int));
		return this -> instruction_register;
	}
	else
	{
		// Set Value to Accumulator
		read(this -> input_stream, &this -> accumulator, sizeof(int));
		return this -> accumulator;
	}
}

// Sets the Value at the specified Address in Memory
void CPU::setValueAtAddress(int address)
{
	// Create the Character String
	char c_string[PIPE_STRING_SIZE] = {'\0'};

	// Initialize the String to be sent (Write Request Value is 1)
	string str = "1 ";

	// Create the Character Strings
	char mode_c_string[2] = {'\0'};
	char address_c_string[ADDRESS_C_STRING_SIZE] = {'\0'};
	char accumulator_c_string[INT_C_STRING_SIZE] = {'\0'};

	// Convert the Addres and Accumulator to Character Strings
	itoa(this -> mode, mode_c_string);
	itoa(address, address_c_string);
	itoa(this -> accumulator, accumulator_c_string);

	// Append the String with the Mode, Address and Accumulator (Format: "1 M XXXX YYYY")
	str.append(mode_c_string);
	str.append(" ");
	str.append(address_c_string);
	str.append(" ");
	str.append(accumulator_c_string);

	// Convert the String into a Character String
	strcpy(c_string, str.c_str());

	// Send the Write Request to Memory through the Pipe
	write(this -> output_stream, &c_string, PIPE_STRING_SIZE);

	// Get confirmation
	int writeSucceeded = 0;
	read(this -> input_stream, &writeSucceeded, PIPE_STRING_SIZE);

	// Make sure the Write Succeeded
	if(!writeSucceeded)
	{
		cout << "Error: Address '" << address << "' is invalid! Terminating program." << endl;
		instruction_end();
	}
}

// Pushes the specified Value to the Stack
void CPU::pushToStack()
{
	//if(this -> debug > 1)
	//	cout << "\t -> pushToStack() | " <<
	//	"AC: " << this -> accumulator << ", SP: " << this -> stack_pointer << endl;

	this -> setValueAtAddress(this -> stack_pointer);
	this -> stack_pointer--;

	//if(this -> debug > 2)
	//	cout << "\t\t -> [Push To Stack] New SP: " << this -> stack_pointer << endl;
}

// Pops the next Value in the Stack and loads it into the Accumulator
int CPU::popFromStack()
{
	//if(this -> debug > 1)
	//	cout << "\t -> popFromStack() | " <<
	//	"AC: " << this -> accumulator << ", SP: " << this -> stack_pointer << endl;

	int value = this -> getValueAtAddress(this -> stack_pointer + 1, false);
	this -> stack_pointer++;

	//if(this -> debug > 2)
	//	cout << "\t\t -> [Pop From Stack] New AC: " << this -> accumulator << ", New SP: " << this -> stack_pointer << endl;

return value;
}

//* Instructions *//
// Performs the Next Instruction
void CPU::doNextInstruction()
{
	if(this -> debug > 0)
	{
		this -> debugHeader();
		cout << "\t -> doNextInstruction() | " <<
		"PC: " << this -> program_counter << ", IR: " << this -> instruction_register << endl;
	}

	// Load the Next Instruction into the Instruction Register
	this -> getNextInstruction();

	if(this -> debug > 0)
		cout << "\t\t -> [doNextInstruction] Next Instruction is: " << this -> instruction_register << endl;

	// Determine which Instruction to Run
	switch(this -> instruction_register)
	{
		case 1:
			this -> instruction_loadValue();
			break;

		case 2:
			this -> instruction_loadAddress();
			break;

		case 3:
			this -> instruction_storeAddress();
			break;

		case 4:
			this -> instruction_addX();
			break;

		case 5:
			this -> instruction_addY();
			break;

		case 6:
			this -> instruction_subtractX();
			break;

		case 7:
			this -> instruction_subtractY();
			break;

		case 8:
			this -> instruction_getRandomInt();
			break;

		case 9:
			this -> instruction_putPort();			
			break;

		case 10:
			this -> instruction_copyToX();
			break;

		case 11:
			this -> instruction_copyToY();
			break;

		case 12:
			this -> instruction_copyFromX();
			break;

		case 13:
			this -> instruction_copyFromY();
			break;

		case 14:
			this -> instruction_jumpToAddress();
			break;

		case 15:
			this -> instruction_jumpToAddressIfEqualToZero();
				break;

		case 16:
			this -> instruction_jumpToAddressIfNotEqualToZero();
			break;

		case 17:
			this -> instruction_callAddress();
			break;

		case 18:
			this -> instruction_return();
			break;

		case 19:
			this -> instruction_increaseX();
			break;

		case 20:
			this -> instruction_decreaseX();
			break;

		case 21:
			this -> instruction_loadFromAddressPlusX();
			break;

		case 22:
			this -> instruction_loadFromAddressPlusY();
			break;

		case 23:
			this -> instruction_push();
			break;

		case 24:
			this -> instruction_pop();
			break;

		case 25:
			this -> instruction_interrupt();
			break;

		case 26:
			this -> instruction_interruptReturn();
			break;

		case 50:
			this -> instruction_end();
			break;

		default:
			cout << "Error: " << instruction_register << " is not a valid command." << endl;
			this -> instruction_end();
			break;
	}
}

// Case: 1
// Loads the next Value into the Accumulator
void CPU::instruction_loadValue()
{
	if(this -> debug > 1)
		cout << "\t -> instruction_loadValue() | AC: " << this -> accumulator << endl;

	if(this -> debug > 2)
		cout << "\t\t -> [Load Value] Setting Accumulator to Next Instruction" << endl;

	this -> accumulator = this -> getNextInstruction();

	if(this -> debug > 2)
		cout << "\t\t -> [Load Value] New AC: " << this -> accumulator << endl;
}

// Case: 2
// Loads the Value found at the next Address into the Accumulator
void CPU::instruction_loadAddress()
{
	if(this -> debug > 1)
		cout << "\t -> instruction_loadAddress() | AC: " << this -> accumulator << endl;

	if(this -> debug > 2)
		cout << "\t\t -> [Load Address] Setting Accumulator to Next Address" << endl;

	this -> getValueAtAddress(this -> getNextInstruction(), false);

	if(this -> debug > 2)
		cout << "\t\t -> [Load Value] New AC: " << this -> accumulator << endl;
}

// Case: 3
// Stores the Value in the Accumulator to the next Address
void CPU::instruction_storeAddress()
{
	if(this -> debug > 1)
		cout << "\t -> instruction_storeAddress() | AC: " << this -> accumulator << endl;

	this -> setValueAtAddress(this -> getNextInstruction());

	if(this -> debug > 2)
		cout << "\t\t -> [Store Address] Storing AC at Address '" << this -> instruction_register << endl;
}

// Case: 4
// Adds the Value in X to the Accumulator
void CPU::instruction_addX()
{
	if(this -> debug > 1)
		cout << "\t -> instruction_addX() | " <<
		"AC: " << this -> accumulator << ", X: " << this -> x << endl;

	this -> accumulator += this -> x;

	if(this -> debug > 2)
		cout << "\t\t -> [Add X] New AC: " << this -> accumulator << endl;
}

// Case: 5
// Adds the Value in Y to the Accumulator
void CPU::instruction_addY()
{
	if(this -> debug > 1)
		cout << "\t -> instruction_addY() | " <<
		"AC: " << this -> accumulator << ", Y: " << this -> y << endl;

	this -> accumulator += this -> y;

	if(this -> debug > 2)
		cout << "\t\t -> [Add Y] New AC: " << this -> accumulator << endl;
}

// Case: 6
// Subtracts the Value in X from the Accumulator
void CPU::instruction_subtractX()
{
	if(this -> debug > 1)
		cout << "\t -> instruction_subtractX() | " <<
		"AC: " << this -> accumulator << ", X: " << this -> x << endl;

	this -> accumulator -= this -> x;

	if(this -> debug > 2)
		cout << "\t\t -> [Subtract X] New AC: " << this -> accumulator << endl;
}

// Case: 7
// Subtracts the Value in Y from the Accumulator
void CPU::instruction_subtractY()
{
	if(this -> debug > 1)
		cout << "\t -> instruction_subtractY() | " <<
		"AC: " << this -> accumulator << ", Y:: " << this -> y << endl;

	this -> accumulator -= this -> y;

	if(this -> debug > 2)
		cout << "\t\t -> [Subtract Y] New AC: " << this -> accumulator << endl;
}

// Case: 8
// Loads a Random Integer between 1 and 100 (inclusive) into the Accumulator
void CPU::instruction_getRandomInt()
{
	if(this -> debug > 1)
		cout << "\t -> instruction_getRandomInt() | AC: " << this -> accumulator << endl;

	this -> accumulator = rand() % 100 + 1;

	if(this -> debug > 2)
		cout << "\t\t -> [Get Random Int] New AC: " << this -> accumulator << endl;
}

// Case: 9
// Prints the Value in the Accumulator to the Screen
void CPU::instruction_putPort()
{
	if(this -> debug > 1)
		cout << "\t -> instruction_putPort() | " <<
		"PC: " << this -> program_counter << ", AC: " << this -> accumulator <<  endl;

	if(this -> debug > 2)
		cout << "\t\t -> [Put Port] Determining Print Type" << endl;

	int type = this -> getNextInstruction();

	switch(type)
	{
		// Write as an Integer
		case 1:
			if(this -> debug > 2)
			{
				cout << "\t\t -> [Put Port] Type Determined as Integer: '" << (int) this -> accumulator << "'" << endl;
			}
			else
				cout << (int) this -> accumulator;

			break;

		// Write as a Character
		default:
			if(this -> debug > 2)
			{
				cout << "\t\t -> [Put Port] Type Determined as Character: '" << (char) this -> accumulator << "'" << endl;
			}
			else
				cout << (char) this -> accumulator;

			break;
	}		
}

// Case: 10
// Copies the Value in the Accumulator to X
void CPU::instruction_copyToX()
{
	if(this -> debug > 1)
		cout << "\t -> instruction_copyToX() | " <<
		"AC: " << this -> accumulator << ", X: " << this -> x << endl;

	this -> x = this -> accumulator;

	if(this -> debug > 2)
		cout << "\t\t -> [Copy To X] X changed to: " << this -> x << endl;
}

// Case: 11
// Copies the Value in the Accumulator to Y
void CPU::instruction_copyToY()
{
	if(this -> debug > 1)
		cout << "\t -> instruction_copyToY() | " <<
		"AC: " << this -> accumulator << ", Y: " << this -> y << endl;

	this -> y = this -> accumulator;

	if(this -> debug > 2)
		cout << "\t\t -> [Copy To Y] Y changed to: " << this -> y << endl;
}

// Case: 12
// Copies the Value in X to the Accumulator
void CPU::instruction_copyFromX()
{
	if(this -> debug > 1)
		cout << "\t -> instruction_copyFromX() | " <<
		"AC: " << this -> accumulator << ", X: " << this -> x << endl;

	this -> accumulator = this -> x;

	if(this -> debug > 2)
		cout << "\t\t -> [Copy From X] AC changed to: " << this -> accumulator << endl;
}

// Case: 13
// Copies the Value in Y to the Accumulator
void CPU::instruction_copyFromY()
{
	if(this -> debug > 1)
		cout << "\t -> instruction_copyFromY() | " <<
		"AC: " << this -> accumulator << ", Y: " << this -> y << endl;

	this -> accumulator = this -> y;

	if(this -> debug > 2)
		cout << "\t\t -> [Copy From Y] AC changed to: " << this -> accumulator << endl;
}

// Case: 14
// Jumps to the next Address
void CPU::instruction_jumpToAddress()
{
	//this -> program_counter = this -> getNextInstruction();

	if(this -> debug > 1)
		cout << "\t -> instruction_jumpToAddress() | PC: " << this -> program_counter << endl;

	int old_PC = setPC(this -> getNextInstruction());

	if(this -> debug > 2)
		cout << "\t\t -> [Jump To Address] Changed PC from '" << old_PC << "' to '" << this -> program_counter << "'" << endl;
}

// Case: 15
// Jumps to the next Address if the Value in the Accumulator is Zero
void CPU::instruction_jumpToAddressIfEqualToZero()
{
	if(this -> debug > 1)
		cout << "\t -> instruction_jumpToAddressIfEqualToZero() | " <<
		"AC: " << this -> accumulator << ", PC: " << this -> program_counter << endl;

	// Check if the AC is 0
	if(this -> accumulator == 0)
		this -> instruction_jumpToAddress();
	else // Read in the Parameter, but do nothing with it
	{
		this -> getNextInstruction();

		if(this -> debug > 2)
			cout << "\t\t -> [Jump If Zero] Ignoring Parameter: '" << this -> instruction_register << "'" << endl;
	}

	if(this -> debug > 2)
		cout << "\t\t -> [Jump If Zero] New PC: " << this -> program_counter << endl;
}

// Case: 16
// Jumps to the next Address if the Value in the Accumulator is not Zero
void CPU::instruction_jumpToAddressIfNotEqualToZero()
{
	if(this -> debug > 1)
		cout << "\t -> instruction_jumpToAddressIfNotEqualToZero() | " <<
		"AC : " << this -> accumulator << ", PC: " << this -> program_counter << endl;

	// Check if the AC is not 0
	if(this -> accumulator != 0)
		this -> instruction_jumpToAddress();
	else // Read in the Parameter, but do nothing with it
	{
		this -> getNextInstruction();

		if(this -> debug > 2)
			cout << "\t\t -> [Jump If Not Zero] Ignoring Parameter: '" << this -> instruction_register << "'" << endl;
	}

	if(this -> debug > 2)
		cout << "\t\t -> [Jump If Not Zero] New PC: " << this -> program_counter << endl;
}

// Case: 17
// Pushes the return Address onto the Stack, then Jumps to the next Address
void CPU::instruction_callAddress()
{
	if(debug > 1)
		cout << "\t -> instruction_callAddress() | " <<
		"PC: " << this -> program_counter << ", SP: " << this -> stack_pointer << endl;

	int old_AC = setAC(this -> program_counter + 1);
	this -> pushToStack();
	this -> accumulator = old_AC;

	if(debug > 2)
		cout << "\t\t -> [Call Address] Pushed '" << this -> program_counter + 1 << "' to Stack at Position '" << this -> stack_pointer << "'" << endl;

	this -> instruction_jumpToAddress();
}

// Case: 18
// Pops the return Address from the Stack, then Jumps to it
void CPU::instruction_return()
{
	this -> instruction_pop();
	this -> program_counter = this -> accumulator;
}

// Case: 19
// Increments the Value in X
void CPU::instruction_increaseX()
{
	if(this -> debug > 1)
		cout << "\t -> instruction_increaseX() | " <<
		"X: " << this -> x << endl;

	this -> x++;

	if(this -> debug > 2)
		cout << "\t\t -> [Increase X] New X Value: " << this -> x << endl;
}

// Case: 20
// Decrements the Value in X
void CPU::instruction_decreaseX()
{
	if(this -> debug > 1)
		cout << "\t -> instruction_decreaseY() | " <<
		"X: " << this -> x << endl;

	this -> x--;

	if(this -> debug > 2)
		cout << "\t\t -> [Decrease X] New X Value: " << this -> x << endl;
}

// Case: 21
// Loads the Value at the next Address incremented by X into the Accumulator
void CPU::instruction_loadFromAddressPlusX()
{
	if(this -> debug > 1)
		cout << "\t -> instruction_loadFromAddressPlusX() | " <<
		"AC: " << this -> accumulator << ", X: " << this -> x << endl;

	int address = this -> getNextInstruction() + this -> x;
	this -> getValueAtAddress(address, false);

	if(this -> debug > 2)
		cout << "\t\t -> [Load From Address Plus X] Returning Address " << address << ": " << this -> accumulator << endl;
}

// Case: 22
// Loads the Value at the next Address incremented by Y into the Accumulator
void CPU::instruction_loadFromAddressPlusY()
{
	if(this -> debug > 1)
		cout << "\t -> instruction_loadFromAddressPluxY() | " <<
		"AC: " << this -> accumulator << ", Y: " << this -> y << endl;

	int address = this -> getNextInstruction() + this -> y;
	this -> getValueAtAddress(address, false);

	if(this -> debug > 2)
		cout << "\t\t -> [Load From Address Plus Y] Returning Address " << address << ": " << this -> accumulator << endl;
}

// Case: 23
// Pushes the Value in the Accumulator to the Stack
void CPU::instruction_push()
{
	if(this -> debug > 1)
		cout << "\t -> instruction_push() | " <<
		"SP: " << this -> stack_pointer << endl;

	this -> pushToStack();
}

// Case: 24
// Pops the next Value from the Stack
void CPU::instruction_pop()
{
	if(this -> debug > 1)
		cout << "\t -> instruction_pop() | " <<
		"SP: " << this -> stack_pointer << endl;

	int value = this -> popFromStack();

	if(this -> debug > 2)
		cout << "\t\t -> [Pop] Value Popped: " << value << endl;
}

// Case: 25
// Changes to System Mode and Pushes current State to the Stack
void CPU::instruction_interrupt()
{
	if(this -> debug > 1)
		cout << "\t -> instruction_interrupt() | " <<
		"AC: " << this -> accumulator << ", X: " << this -> x << ", Y: " << this -> y << ", PC: " << this -> program_counter << ", SP: " << this -> stack_pointer << endl;

	// Set the CPU Mode
	this -> mode = SYSTEM_MODE;

	// Push all Variables and PC to the Stack
	// 1: Accumulator
	this -> pushToStack();

	// 2: X
	this -> accumulator = this -> x;
	this -> pushToStack();

	// 3: Y
	this -> accumulator = this -> y;
	this -> pushToStack();

	// 4: Program Counter
	this -> accumulator = this -> program_counter;
	this -> pushToStack();

	this -> program_counter = PROGRAM_MEMORY_SIZE;

	if(this -> debug > 2)
		cout << "\t\t -> [Interrupt] New SP: " << this -> stack_pointer << endl;
}

// Case: 26
// Changes to User Mode and Pops previous State from the Stack
void CPU::instruction_interruptReturn()
{
	if(this -> debug > 1)
		cout << "\t -> instruction_interruptReturn() | " <<
		"AC: " << this -> accumulator << ", X: " << this -> x << ", Y: " << this -> y << ", PC: " << this -> program_counter << ", SP: " << this -> stack_pointer << endl;

	this -> mode = USER_MODE;

	// Pop all Variables and PC back from the Stack
	// 4: Program Counter
	this -> popFromStack();
	this -> program_counter = this -> accumulator;

	// 3: Y
	this -> popFromStack();
	this -> y = this -> accumulator;

	// 2: X
	this -> popFromStack();
	this -> x = this -> accumulator;

	// 1: Accumulator
	this -> popFromStack();

	// Set the CPU Mode
	//this -> mode = USER_MODE;

	if(this -> debug > 2)
		cout << "\t\t -> [Interrupt Return] New AC: " << this -> accumulator << ", New X: " << this -> x << ", New Y: " << this -> x << ", New PC: " << this -> program_counter << ", New SP: " << this -> stack_pointer << endl;
}

// Case: 50
// Ends the Program
void CPU::instruction_end()
{
	timeToDie = true;
	write(this -> output_stream, "-1", PIPE_STRING_SIZE);
}

//* Utilities *//
// Converts the specified Integer to ASCII
void CPU::itoa(int n, char s[])
{
	bool negative = n < 0;
	int digits;

	// Check if the Number is Negative
	if(negative)
		n = -n; // Make the Number Positive

	digits = 0;
	do
	{
		// Grab the Digits in Reverse Order
		s[digits++] = n % 10 + '0';
	}
	while((n /= 10) > 0); // Remove the Right-Most Digit

	// Add the Negative Sign back in
	if(negative)
		s[digits++] = '-';

	// Terminate the String with a Null Character
	s[digits] = '\0';

	// Reverse the String
	reverse(s);
}

// Reverses the specified String
void CPU::reverse(char s[])
{
	int start, end;
	char c;

	// Loop from the Ends of the String to the center
	for(start = 0, end = strlen(s) - 1; start < end; start++, end--) 
	{
		// Grab a Temp Char
		c = s[start];

		// Swap the Characters
		s[start] = s[end];
		s[end] = c;
	}
}

// * Debug Functions *//
// Debugs the CPU Variables to the Console
void CPU::debugHeader()
{
	if(this -> debug > 0)
	{
		cout << "[CPU | PC: " << this -> program_counter << ", " <<
			"IR: " << this -> instruction_register << ", " <<
			"SP: " << this -> stack_pointer << ", " <<
			"AC: " << this -> accumulator << ", " <<
			"X: " << this -> x << ", " <<
			"Y: " << this -> y << "]" << endl;
	}
}
