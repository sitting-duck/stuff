//* Description *//
// Title: Main
// Authors: Brian Quackenbush, Tyler Reed, Ashley Tharp
// Runs the Program and Forks the Process

//* Libraries *//
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include "CPU.h"
#include "Memory.h"

//* Namespaces *//
using namespace std;

//* Functions *//
void printProjectHeader();

//* Main Method *//
int main(int argc, char** argv)
{
	// Display the Project Information
	printProjectHeader();

	// Create the Child Process ID
	pid_t child_pid;

	// Create the Pipes for CPU and Memory
	int mem_to_cpu_fd[2];
	int cpu_to_mem_fd[2];

	int mem_to_cpu_id = pipe(mem_to_cpu_fd);
	int cpu_to_mem_id = pipe(cpu_to_mem_fd);

	// Fork the Process, creating a Child
	child_pid = fork();

	// Make sure the Fork Succeeded
	if(child_pid == -1)
	{
		cout << "Forking Process Failed." << endl;
		exit(0);
	}

	// Parent (CPU) Process
	if(child_pid != 0)
	{
		// Create the CPU Object
		CPU cpu(mem_to_cpu_fd[0], cpu_to_mem_fd[1]);

		// Perform Instructions until the CPU receives a Kill Command
		while(!cpu.isTimeToDie())
			cpu.doNextInstruction();
	}
	else // Child (Memory) Process
	{
		// Create the Memory Object
		Memory mem(cpu_to_mem_fd[0], mem_to_cpu_fd[1]);
		// Create the Pipe Variables
		string pipe_buffer;
		string code_token, mode_token, address_token, to_write_token;

		// Perform Memory Actions
		while(!mem.is_time_to_die())
		{
			// Read from the Input Pipe
			pipe_buffer = mem.read_from_pipe(mem.get_pipe_string_length());
			// Parse the Input
			mem.get_tokens(pipe_buffer, code_token, mode_token, address_token, to_write_token);

			// Do what the Input says
			mem.which_function_switch(code_token, mode_token, address_token, to_write_token);	
		}

		// Once Memory is finished, the Child can terminate
		return 0;
	}

	// Close the Pipes
	close(mem_to_cpu_fd[0]);
	close(mem_to_cpu_fd[1]);
	close(cpu_to_mem_fd[0]);
	close(cpu_to_mem_fd[1]);

	return 0;
} 

// Prints the Project Header to the Console
void printProjectHeader()
{
	cout << "Project #1: Exploring Multiple Processes and IPC" << endl;
	cout << "Brian Quackenbush, Tyler Reed, and Ashley Tharp" << endl;
	cout << "Operating Systems - CS 4348.501" << endl << endl;	
}
