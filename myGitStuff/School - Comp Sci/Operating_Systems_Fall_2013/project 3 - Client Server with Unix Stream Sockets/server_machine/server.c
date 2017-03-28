#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUFSIZE 80

void* handleClient(void*);
int random_in_range(int min, int max);
void itoa(int n, char s[]);
void reverse(char s[]);

int main(int argc, char *argv[])
{
   char     host[80];

   int      sd, sd_current;
   
   int      port;
   
   int      *sd_client;
   
   int      addrlen;
   
   struct   sockaddr_in sin;
   
   struct   sockaddr_in pin;
   
   pthread_t tid;
   
   pthread_attr_t attr;

   /* check for command line arguments */
   //we're going to enter program name and then the port number we want
   if (argc != 2)  
   {
      printf("Usage: server port\n");
      exit(1);
   }

   /* get port from argv */
   port = atoi(argv[1]);
 
 
   /* create an internet domain stream socket */
   if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
      perror("Error creating socket");
      exit(1);
   }

   /* complete the socket structure */
   memset(&sin, 0, sizeof(sin));
   sin.sin_family = AF_INET;
   sin.sin_addr.s_addr = INADDR_ANY;  /* any address on this host */
   sin.sin_port = htons(port);        /* convert to network byte order */

   /* bind the socket to the address and port number */
   //bind function prototype
   //int bind(int sockfd, const struct sockaddr * addr, socklent_t addrlen);
   if (bind(sd, (struct sockaddr *) &sin, sizeof(sin)) == -1) {
      perror("Error on bind call");
      exit(1);
   }

   /* set queuesize of pending connections */ 
   //listen funciton prototype
   //int listen(int sockfd, int backlog);
   if (listen(sd, 5) == -1) {				//listen marks the socket referred to by sockfd as a passive socket that will be used to accept incoming 
      perror("Error on listen call");			//connection requests using accept. Backlog defines the maximum queue length for pending connections for sockfd to
      exit(1);						//accept. 
   }

   /* announce server is running */
   gethostname(host, 80); 
   //host is the server then...ok derp
   printf("Server is running on %s:%d\n", host, port);


   /* wait for a client to connect */
   pthread_attr_init(&attr);
   //initializes the thread attributes object to default values
   //note: attr is of type pthread_attr_t.
   //You would basically reuse this attr when calling pthread_create multiple times to create threads of a certain type.
   
   pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED); /* use detached threads */
   //this is so that we don't have to join them later.

   addrlen = sizeof(pin);
   while (1)
   {
	   //sd_current is basically an int
	   //remember sd was set as our passive socket with the listen command
      if ((sd_current = accept(sd, (struct sockaddr *)  &pin, (socklen_t*)&addrlen)) == -1) 
      {
	 perror("Error on accept call");
	 exit(1);
	 //this appears to be the only way to break out of this infinite loop
      }

      sd_client = (int*)(malloc(sizeof(sd_current)));
      *sd_client = sd_current;
      //I guess this is for updating the socket descriptor (sd) each time.

      pthread_create(&tid, &attr, handleClient, sd_client); //a thread is created to handle the requests of each client.
   }

} //end main


void* handleClient(void *arg)
{
   int count=0;
   char     buf[BUFSIZE];  /* used for incoming string, and outgoing data */
   char     temp[BUFSIZE]; 
   char char_dir;

   typedef enum {NORTH, EAST, SOUTH, WEST, NUMDIR} direction;
   direction dir = 0;

   int air_temp;
   char char_air_temp[3];

   int i;
   for(i = 0; i < 3; i++)
   {
   	char_air_temp[i] = '\0';
   }

   int file_size_in_bytes;
   char file_size_buffer[10]; /*let's just go ahead and assume that the file size won't have more than 10 digits*/				
   struct stat file_stats;
   FILE* picture_file;
   char dir_string[6];
   int dir_name_length;
   int file_name_length;
   static const int max_file_name_length = 10;


   for(i = 0; i < 6; i++)
   {
   	dir_string[i] = '\0';
   }

   char* picture_file_buffer;

   int sd = *((int*)arg);  /* get sd from arg */
   free(arg);              /* free malloced arg */

   while(1)
   {
	   /* read a message from the client */
	   if ( (count = read(sd, buf, sizeof(buf)) ) == -1)
	   {
	      perror("error on server side when reading from client");
	      exit(1);
	   }
	   printf("Server read %d bytes\n", count);

	   switch(buf[0])
	   {
		case 'l':
			dir = (dir+3)%NUMDIR;
			break;
		case 'r':
			dir = (dir+1)%NUMDIR;
			break;
		case 't':

			/*the file's going to be called north.jpg if we're facing north, east.jpg if we're facing east and so on.*/
			/*so we're gonna build the file name based on which direction our little robot is currently facing*/
			switch(dir)
			{
				case NORTH:
					strcpy(dir_string, "north");
					break;
				case EAST:
					strcpy(dir_string, "east");
					break;
				case SOUTH:
					strcpy(dir_string, "south");
					break;
				case WEST:
					strcpy(dir_string, "west");
					break;
			}
			dir_name_length = strlen(dir_string);
			file_name_length = dir_name_length + 4;
			char* file_name = calloc(max_file_name_length, sizeof(char));
			strcpy(file_name, dir_string);
			
			/*append .jpg to the end of the file name*/
			file_name[file_name_length - 4] = '.';
			file_name[file_name_length - 3] = 'j';
			file_name[file_name_length - 2] = 'p';
			file_name[file_name_length - 1] = 'g';

			/*open the file to read in binary mode*/
			picture_file = fopen(file_name, "rb");
			if(!picture_file)
				perror("fopen failure on server side");


			/*now we're gonna figure how big this file is and send that number to the client.*/
			stat(file_name, &file_stats);
			file_size_in_bytes = file_stats.st_size;
			itoa(file_size_in_bytes, file_size_buffer);

			/*the client knows it's gonna get 10 bytes for the file size, and we are always gonna send 10 bytes. period.*/
			   if ( (count = write(sd, file_size_buffer, 10) ) == -1) 
			   {
			      perror("write fail on server side when trying to send picture file size");
			      exit(1);
			   }
			   printf("server sent %d bytes to client indicating picture file size %d\n", 10, file_size_in_bytes);

			   /*now let's send the client the name of the file. Let's assume the file name is no longer than 10 characters.*/
			   if((count = write(sd, file_name, max_file_name_length)) == -1)
			   {
			   	perror("write fail on server side when trying to send file name");
				exit(1);
			   }
			   printf("server sent %d bytes to client indicating file name %s\n", count, file_name);

			/*now we're going to create a huge buffer that we're going to read the picture file into*/
			  picture_file_buffer = malloc(file_size_in_bytes);
			  printf("server created buffer for holding picture data\n");

			   printf("before reading image file into internal buffer\n");					
			   if((count = fread(picture_file_buffer, sizeof(char), file_size_in_bytes, picture_file)) == 0)
			   {
			   	perror("read fail on server side when trying to read picture file into an internal buffer");
				exit(1);
			   }
			   printf("server read %d bytes from the picture file.\n", count);

			   /*now we're going to write the entire picture file byte by byte from that buffer over the socket to the client*/			   
			   printf("before server sends picture image over the socket\n");
			   if((count = write(sd, picture_file_buffer, file_size_in_bytes)) == -1)
			   {
			   	perror("write fail on server when trying to write picture file from buffer to the client");
				exit(1);
			   }
			   printf("server sent %d bytes to client. Sent the picture file.\n", count);

			   /*let's free this huge buffer. Memory leaks are bad mmkay?*/
			   free(picture_file_buffer);

			/*get rid of this. memory leaks are bad mmkay?*/
			free(file_name);

			/*we should should probably flush the socket to make sure nobody else get garbage*/
			
			break;
		case 'd':
			   printf("current dir is : %d\n", dir);
			   char_dir = dir + 48; /*ascii hack*/
			   temp[0] = char_dir;
			   temp[1] = '\0'; /*null char*/

			   if ( (count = write(sd, temp, 2) ) == -1) 
			   {
			      perror("write fail on server side when writing direction to socket");
			      exit(1);
			   }
			   printf("server sent %d bytes. Dir sent was %s\n", count, temp);
			break;
		case 'a':
			air_temp = random_in_range(-50, 50);

			itoa(air_temp, char_air_temp);
				
			   if ( (count = write(sd, char_air_temp, 3) ) == -1) 
			   {
			      perror("write");
			      exit(1);
			   }
			   printf("server sent %d bytes. Air temp was %s\n", count, char_air_temp);
			break;
		case 'e':
			   /* close socket */
			   close(sd); 
			exit(0);			
		default: 
			printf("invalid input was entered on client side\n");
	   }
   }

}

int random_in_range(int min, int max)
{
	int base_random = rand();
	if(RAND_MAX == base_random) return random_in_range(min, max);

	int range = max - min;
	int remainder = RAND_MAX % range;
	int bucket = RAND_MAX / range;

	if(base_random < RAND_MAX - remainder)
	{
		return min + base_random/bucket;
	}
	else
	{
		return random_in_range(min, max);
	}
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


