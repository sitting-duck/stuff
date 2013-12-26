//* Description *//
// Title: Memory Header
// Authors: Brian Quackenbush, Tyler Reed, Ashley Tharp
// Defines the structure of the Memory Class

//* Header Definition *//
#ifndef MEMORY_H
#define MEMORY_H

//* Libraries *//
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <unistd.h>

//* Definitions *//
#define PROGRAM_MEMORY_SIZE 1000
#define INTERRUPT_MEMORY_SIZE 1000
#define PIPE_STRING_SIZE 20

//* Namespaces *//
using namespace std;

//* Memory Class *//
class Memory
{
	//* Private Variables *//
	private:
		// Memory Variables
		int memory[PROGRAM_MEMORY_SIZE + INTERRUPT_MEMORY_SIZE];
		int num_commands;
		int num_interrupt_commands;
		int input;
		int output;
		bool timeToDie;
		ifstream program_file;
		ifstream interrupt_file;
		int mode;
		enum modes {USER_MODE, SYSTEM_MODE};

		// Debugging Variables
		int verbose;

	//* Public Methods *//
	public:
		// Constructors and Destructor	
		Memory(int _input, int _output); 
		~Memory();
		Memory(Memory& _memref);
		int Initialize_Memory();
	
		// Memory Functions
 		int read_memory(int _address);
		int read_memory(string& _address);
		int write_memory(int _input, int _address);
		int write_memory(string& _input, string& _address); 

		// Pipe Functions
		string read_from_pipe(int _how_many_characters);
		void read_from_pipe(int _how_many_characters, string& _string);
		void write_to_pipe(char* _string);
		void write_to_pipe(char* _string, int _how_many_characters);
		void write_to_pipe(string& _string);
		void write_to_pipe(int& _num);

		void which_function_switch(string& _code_token, string& _mode_token, string& _address_token, string& _to_write_token);

		// Utilities
		int get_pid();
		int get_num_commands();
		int get_pipe_string_length();
		void populate_memory(string& _line, int _section);
		void get_tokens(string& _pipe_string, string& _code, string& _mode, string& _address, string& to_write);
		bool is_valid_mem_address(int _address);
		bool is_valid_mem_address(string& _string);
		bool is_valid_write_input(string& _string);
		bool is_time_to_die();
		void print_memory();
		void print_program_memory();
		void print_interrupt_memory();
		void print_program();
		bool strIsNumber(char* buff);
};

// Returns whether or not the specified Address is valid
inline bool Memory::is_valid_mem_address(int _address)
{
	return  _address < (PROGRAM_MEMORY_SIZE + INTERRUPT_MEMORY_SIZE) && _address > -1;
}

// Returns the Number of Commands in Memory
inline int Memory::get_num_commands()
{
	return num_commands;
}

// Returns the Memory at the specified Address
inline int Memory::read_memory(int _address)		
{
	return memory[_address];
}

// Returns the Memory at the specified Address
inline int Memory::read_memory(string& _address)
{
	int address = atoi(_address.c_str());
	return read_memory(address);
}

// Returns the Pipe String Length
inline int Memory::get_pipe_string_length()
{
	return PIPE_STRING_SIZE;
}

//* End Header Definition *//
#endif

