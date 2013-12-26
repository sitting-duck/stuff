#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <string.h>

#define BUFSIZE 80

void write_option_to_server(int* sd, char* option, int* count);
void itoa(int n, char s[]);
void reverse(char s[]);

int main(int argc, char ** argv)
{

	char host_name[100];
	char buffer[BUFSIZE];
	
	int sd; /*socket descriptor*/
	int port;
	int count;

	char option[2];
	
	/*stores info about the machine we want to connect to*/
	/*sockaddr_in is the data structure used with IPV4 addresses*/
	struct sockaddr_in machine_we_want_to_connect_to;

	/*this data structure holds the symbolic name of the host and other data like what type of addressing scheme it uses, and what its address is*/
	struct hostent* hp;

	
	/*check for proper number of command line arguments*/
	if(argc != 3)
	{
		printf("Error: incorrect number of arguments. Correct format is client <machine name> <port number> Please try again.\n");
		exit(1);
	}

	/*get the host name and the port number from the main program args*/
	strcpy(host_name, argv[1]);
	port = atoi(argv[2]);

	/*now let's create an internet domain stream sockket*/
	sd = socket(AF_INET, SOCK_STREAM, 0);

	if(sd == -1)
	{
		perror("Error creating socket. Program exiting now. Please try again.\n");
		exit(1);
	}

	/*going to set the host we want by using the string specified in the args passed to the program*/
	hp = gethostbyname(host_name);

	if(hp == 0)
	{
		perror("Error find host.  Please enter a valid host.\n");
		exit(1);
	}

	/*zero the struct. This machine_we_want_to_connect_to is a data structure holding an address we want*/
	memset(&machine_we_want_to_connect_to, 0, sizeof(machine_we_want_to_connect_to));

	/*set the family*/
	machine_we_want_to_connect_to.sin_family = AF_INET;

	/*set the address, notice all this type casting and redirection going on here...*/
	machine_we_want_to_connect_to.sin_addr.s_addr = ((struct in_addr*)(hp->h_addr))->s_addr;

	/*set the port number. Note: htons converts the num we have into network byte order.*/
	machine_we_want_to_connect_to.sin_port = htons(port);

	printf("Connecting to %s: %d\n\n", host_name, port);

	/*connect to the port we want on the host we want*/
	if(connect(sd, (struct sockaddr*) &machine_we_want_to_connect_to, sizeof(machine_we_want_to_connect_to)) == -1)
	{
		perror("Error while trying to connect. Program exiting.\n");
		exit(1);
	}
	else
	{
		printf("Client connected successfully\n");
	}

	char dir[2];
	char dir_string[6];
	int i;
	for(i = 0; i < 6; i++)
	{
		dir[i] = '\0';	
	}
	char char_air_temp[3];
	
	FILE* picture_file;

	char file_size_buffer[10];

	char file_name[100];

	int picture_file_size;

	char file_name_buffer[10];

	char* picture_file_buffer;

	
	printf("MARS ROVER SIMULATION WOOHOO!\n");
	printf("Choose an option from the menu below:\n\n");
	printf("l - turn left 90 degrees\n");
	printf("r - turn right 90 degrees\n");
	printf("t - take a picture\n");
	printf("d - get direction\n");
	printf("a - get the air temperature\n");
	printf("e - exit program\n");

   	while(1)
   	{
	
		scanf("%s", option);
		
		switch(option[0])
		{
			case 'l':
				write_option_to_server(&sd, option, &count);
				break;
			case 'r':
				write_option_to_server(&sd, option, &count);
				break;
			case 't':
				write_option_to_server(&sd, option, &count);
				
				/*so we sent over our little 't', then the server sends us 10 chars that we will turn into a number.
				 * This number s going to be the size of the picture file we are going to get from the server*/
				if((count = read(sd, file_size_buffer, 10)) == -1)
				{
					perror("error when reading picture file size on the client side");
					exit(1);
				}
				printf("Client read %d bytes. Picture file size is %s\n", count, file_size_buffer);
				
				/*let's convert those chars to an actual number*/
				picture_file_size = atoi(file_size_buffer);

				/*the next thing the server is gonna send over the name of the file.  We basically want to recreate the file on this machine, 
				 * so we're going to make the same file with the same name over on this machine.*/
				if((count = read(sd, file_name_buffer, 10)) == -1)
				{
					perror("error when reading picture file name on the client side");
					exit(1);
				}
				printf("Client read %d bytes. Picture file name is %s\n", count, file_name_buffer);

				/*we're going to make a file to write to in binary mode byte for byte*/
				picture_file = fopen(file_name_buffer, "wb");
				if(!picture_file)
					perror("fopen failure on client side");
				printf("client created file %s\n", file_name_buffer);

				/*now we're going to make a huge buffer to hold the file in that we recieve from the server*/
				picture_file_buffer = malloc(picture_file_size);

				/*now we call read and it will grab the entire chunk of bytes sent over that is the picture
				 * it's going to put all these bytes it gets into picture_file_buffer*/
				
				if((count = read(sd, picture_file_buffer, picture_file_size)) == -1)
				{
					perror("error when reading picture file on the client side");
					exit(1);
				}
				printf("client read %d bytes from the socket into a buffer.\n", count);

				count = fwrite(picture_file_buffer, sizeof(char), picture_file_size, picture_file);
				printf("client wrote %d bytes to file %s", count, file_name_buffer);

				fclose(picture_file);

				/*memory leaks are bad mmkay?*/
				free(picture_file_buffer);

				break;
			case 'd':
				write_option_to_server(&sd, option, &count);
				
				if((count = read(sd, dir, 2)) == -1)
				{
					perror("error when reading direction on the client side");
					exit(1);
				}
				printf("got %s from socket for direction.\n", dir);
				switch(dir[0])
				{
					case '0':
						strcpy(dir_string, "north");
						break;
					case '1':
						strcpy(dir_string, "east");
						break;
					case '2':
						strcpy(dir_string, "south");
						break;
					case '3':
						strcpy(dir_string, "west");
						break;
				}

				printf("Client read %d bytes. Direction is %s\n", count, dir_string);

				for(i = 0; i < 6; i++)
				{
					dir_string[i] = '\0';	
				}
				dir[0] = '\0';
				dir[1] = '\0';

				break;
			case 'a':
				write_option_to_server(&sd, option, &count);
				if((count = read(sd, char_air_temp, 3)) == -1)
				{
					perror("error when reading air temperature on the client side");
					exit(1);
				}
				printf("Client read %d bytes. Air temp was %s.\n", count, char_air_temp);
				break;
			case 'e':
				exit(0);
			default: 
				printf("Invalid input. Please choose an option from the menu and try again.\n");
		}

		printf("\n");
	}//end infinite while loop

	return 0;

}//end main

void write_option_to_server(int* sd, char* option, int* count)	
{
	if((*count = write(*sd, option, 2)) == -1)
	{
		perror("error while client was writing to server");
		exit(1);
	}
	printf("client sent %d bytes \n", *count);
}

//* Utilities *//
// Converts the specified Integer to ASCII
void itoa(int n, char s[])
{
	int negative = n < 0;
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
void reverse(char s[])
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

