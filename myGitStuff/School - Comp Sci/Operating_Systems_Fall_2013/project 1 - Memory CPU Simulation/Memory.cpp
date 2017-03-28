//* Description *//
// Title: Memory
// Authors: Brian Quackenbush, Tyler Reed, Ashley Tharp
// Defines the Methods for the Memory Class

//* Libraries *//
#include "Memory.h"

//* Namespaces *//
using namespace std;

//* Constructors and Destructor *//
// Memory Constructor
Memory::Memory(int _input, int _output): input(_input), output(_output), verbose(true), num_commands(0), num_interrupt_commands(0), timeToDie(false)
{
	Initialize_Memory();
}	

// Copy Constructor
Memory::Memory(Memory& _memref)
{
}

// Destructor
Memory::~Memory()
{
	// Nothing to Delete
}

// Function Constructor
int Memory::Initialize_Memory()
{

	for(int i = 0; i < (PROGRAM_MEMORY_SIZE + INTERRUPT_MEMORY_SIZE); i++)
	{
		memory[i] = 0;
	}

	program_file.open("program.txt", ios::in | ios::binary);
	interrupt_file.open("interrupt.txt", ios::in | ios::binary);

	// Make sure the File has Opened
	if(!program_file.is_open())
	{
		cout << "[Memory | Error] File program.txt  could not be opened!" << endl;
		exit(1);
	}
	if(!interrupt_file.is_open())
	{
		cout << "[Memory | Error] File interrupt.txt could not be opened!" << endl;
	}
	
	// Read the entire File
	string line;
	while(getline(program_file, line))
		populate_memory(line, 0);  //populate program section
	while(getline(interrupt_file, line))
		populate_memory(line, 1); //populate interrupt section
	

	// Close the File
	program_file.close();
	interrupt_file.close();
}

//* Memory Functions *//
// Writes to the specified Address in Memory
int Memory::write_memory(int _input, int _address)
{
	// Make sure the Address is Valid
	if(_address < (PROGRAM_MEMORY_SIZE + INTERRUPT_MEMORY_SIZE))
	{
		memory[_address] = _input;
		return 1;
	}
	else
	{
		cout << "Error: Attempt to write to invalid address. Address '" << _address << "' is invalid." << endl;
		return 0;
	}
}

// Writes to the specified Address in Memory, returning -1 for an invalid Address
int Memory::write_memory(string& _input, string& _address)
{
	int input_num = atoi(_input.c_str());
	int address_num = atoi(_address.c_str());

	return write_memory(input_num, address_num);
}

// Returns the specified number of Characters from the Input Pipe
string Memory::read_from_pipe(int _how_many_characters)
{
	// Create the Buffer Character String
	char* buffer = new char[PIPE_STRING_SIZE];

	// Read into the Buffer from the Input Pipe
	read(input, buffer, PIPE_STRING_SIZE);

	// Create a String Buffer, and remove the Character String Buffer
	string string_buffer = buffer;
	delete [] buffer;

	return string_buffer;
}

// Sets the specified String to the specified Number of Characters from the Input Pipe
inline void Memory::read_from_pipe(int _how_many_characters, string& _string)
{
	_string = read_from_pipe(_how_many_characters);
}

// Writes the specified Character String to the Output Pipe
void Memory::write_to_pipe(char* _string)
{
	write(output, _string, strlen(_string));
}

// Writes the specified Number of Characters of the specified Character String to the Output Pipe
void Memory::write_to_pipe(char* _string, int _how_many_characters)
{
	write(output, _string, _how_many_characters);
}

// Writes the specified String to the Output Pipe
void Memory::write_to_pipe(string& _string)
{
	write(output, _string.c_str(), _string.length());
}

// Writes the specified Number to the Output Pipe
void Memory::write_to_pipe(int& _num)
{
	write(output, &_num, sizeof(int));
}

//* Utility Functions *//
// Returns the Process ID
int Memory::get_pid()
{
	return getpid();
}

// Takes next command from input file and puts it into specified section of memory
void Memory::populate_memory(string& _line, int _section)
{
	// Read the next Line in the Input File
	int length = _line.length();
	char* line_cstring = new char[length + 1];
	line_cstring[length] = '\0';
	strcpy(line_cstring, _line.c_str());

	char* token_cstring = strtok(line_cstring, " \n/");

	// Make sure the Input is a Number
	if(!strIsNumber(token_cstring)) 
	{
		cout << "Error: Invalid input on line: " << num_commands << endl;
		exit(1);
	}

	// Add the Command to Memory
	int num = atoi(token_cstring);
	switch(_section)
	{
		case 0: memory[num_commands] = num; 
			num_commands++;
			break;
		case 1: memory[PROGRAM_MEMORY_SIZE + num_interrupt_commands] = num;
			num_interrupt_commands++;
			break;
		default:
			cout << "Error: Invalid Section" << endl;
	}
	
	delete [] line_cstring;
}

// Splits the specified String input a Code, Address, and Write Component
// if requested address is invalid, will terminate
void Memory::get_tokens(string& _pipe_string, string& _code, string& _mode, string& _address, string& _to_write)
{
	// Convert the String into a Character String
	char c_string[PIPE_STRING_SIZE] = {'\0'};
	strcpy(c_string, _pipe_string.c_str());

	// Create the Tokens
	char* code_token = strtok(c_string, " \0");
	char* mode_token = strtok(NULL, " \0");
	char* address_token = strtok(NULL, " \0");
      	char* to_write_token;

	// Determine whether or not there is a Write Token
	if(*code_token == '1')
	{
		to_write_token = strtok(NULL, " \0");
	}
	else if(*code_token == '-')
	{
		timeToDie = true;
	}
	else // Code Token == 0
	{
		char none_cstr[5] = "none";
		to_write_token = none_cstr;
	}

	// Set the Tokens to their respective Values
	_code = code_token;
	_mode = mode_token;
	_address = address_token;
	_to_write = to_write_token;
}

// Dumps the Memory to the Console
void Memory::print_memory()
{
	for(int i = 0; i < (PROGRAM_MEMORY_SIZE + INTERRUPT_MEMORY_SIZE); i++)
		cout << memory[i] << " ";

	cout << endl;
}

// Dumps the Program Portion of Memory to the Console
void Memory::print_program_memory()
{
	for(int i = 0; i < num_commands; i++)
		cout << memory[i] << " ";

	cout << endl;
}

//
//Dumps the Interrupt Portion of Memory to the Console
void Memory::print_interrupt_memory()
{
	for(int i = (PROGRAM_MEMORY_SIZE + INTERRUPT_MEMORY_SIZE); i < num_interrupt_commands; i++)
		cout << memory[i] << " ";
	
	cout << endl;
}


// Returns whether or not the specified String is a valid Address in Memory
bool Memory::is_valid_mem_address(string& _string)
{
	int num = atoi(_string.c_str());

	return is_valid_mem_address(num);
}

// Returns whether or not the specified String is a valid Write Address in Memory
bool Memory::is_valid_write_input(string& _string)
{
	// Input to write to memory must be an integer
	// that cannot have more than 10 digits (2^32).
	// However, it can be negative.

	// Make sure the Integer String is the correct Size
	if(_string.length() > 11)
		return false;

	// Covert the String into a Character String
	char c_string[12] = {'\0'};
	strcpy(c_string, _string.c_str());

	// Make sure the String is a Number
	if(c_string[0] == '-' || isdigit(c_string[0]) == true)
	{
		// Make sure each Character is a Digit
		for(int i = 1; c_string[i] != '\0'; i++)
			if(isdigit(c_string[i]) == false)
				return false;
	}
	else
		return false;	
}

// Performs Communication I/O with CPU
void Memory::which_function_switch(string& _code_token, string& _mode_token, string& _address_token, string& _to_write_token)
{
	int code_number = atoi(_code_token.c_str());
	int address_number = atoi(_address_token.c_str());
	int value_returned_from_mem;
	int writeSucceeded = 0;
	this -> mode = atoi(_mode_token.c_str());

	if(mode == USER_MODE && address_number >= PROGRAM_MEMORY_SIZE)
	{
		cout << "Error: Invalid permissions." << endl;
		exit(1);
	}

	// Make sure Memory has not been given the Kill Command
	if(_code_token != "-1")
	{
		// Determine the Operation being Performed
		switch(code_number)
		{
			// CPU is requesting Information
			case 0: 
				value_returned_from_mem = read_memory(_address_token);
				write_to_pipe(value_returned_from_mem);
				break;

			// CPU is writting Information
			case 1:
				writeSucceeded = write_memory(_to_write_token, _address_token);

				// Determine whether or not the Write Failed
				write_to_pipe(writeSucceeded);
				break;

			// CPU is misbehaving
			default: 
				cout << "Error: Invalid code number." << endl;
				write_to_pipe(writeSucceeded);
		}
	}
	else
	{
		// Alert the Main Program that the Memory needs to terminate
		timeToDie = true;
	}
}

// Returns whether or not it is time for the Memory to die
bool Memory::is_time_to_die()
{
	return timeToDie;
}

// Returns whether or not the specified Character String is a Number
bool Memory::strIsNumber(char* buff)
{
	int len = strlen(buff);
	int i = 0;

	if(buff[0] == '-')
		i = 1;

	for(; i < len; i++)
		if(!isdigit(buff[i]))
			return false;
	return true;
}
