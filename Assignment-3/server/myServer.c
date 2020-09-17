/**
 * Sources:
 * http://www.cs.rpi.edu/~moorthy/Courses/os98/Pgms/socket.html
 * http://www.science.smith.edu/dftwiki/index.php/Tutorial:_Client/Server_on_the_Raspberry_Pi#Server_code
*/

#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>


void error( char *msg ) {
  perror(msg);
  exit(1);
}

void sendString(int sockfd, char *str) {
  int n;
  char buffer[32];
  sprintf(buffer, "%s", str);
  n = write(sockfd, buffer, strlen(buffer));
  if (n < 0)
      error("ERROR writing to socket");
}

void sendChar(int sockfd, char c) {
  int n;
  char buffer[2];
  sprintf(buffer, "%c\n", c);
  n = write( sockfd, buffer, strlen(buffer));
  if (n < 0)
      error("ERROR writing to socket");
}

int getData(int sockfd) {
  char buffer[32];
  int n;

  if ( (n = read(sockfd,buffer,31) ) < 0 )
    error("ERROR reading from socket");
  buffer[n] = '\0';
  printf("buffer = %s\n", buffer);
  return atoi( buffer );
}

int main(int argc, char *argv[]) {
     int sockfd, newsockfd, portno = 51717, clilen;
     char buffer[256];
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     int data;
     char name[256];
     int name_index = 0;

     printf( "using port #%d\n", portno );

     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
	 error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));

     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons( portno );
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
	      sizeof(serv_addr)) < 0) 
       error("ERROR on binding");
     listen(sockfd,5);
     clilen = sizeof(cli_addr);

     //--- infinite wait on a connection ---
     while ( 1 ) {
	printf( "waiting for new client...\n" );
	if ( ( newsockfd = accept( sockfd, (struct sockaddr *) &cli_addr, (socklen_t*) &clilen) ) < 0 )
	    error("ERROR on accept");
	printf( "opened new communication with client\n" );
	
	// 2a
	while ( 1 ) {
	     //---- wait for a letter from client ---
	     bzero(buffer,256);
	     n = read(newsockfd,buffer,255);
	     buffer[strcspn(buffer, "\n")] = 0;
	       
	     if (n <= 0) 
	       break;
	     
	     printf("Received %s\n", buffer);
	     
	     //---- if new name ----
	     if (strcmp(buffer, "done") == 0){
	       bzero(name, 256);
	       name_index = 0;
	     } else {
	       name[name_index] = buffer[0];
	       char* subname = malloc(strlen(name));
	       strncpy(subname, name, name_index+1);
	       printf("%s\n", subname);
	       name_index++;
	       sendChar(newsockfd, buffer[0]+1);
	     }
	}
	
	/*
	// 2b
	bzero(buffer,256);
	n = read(newsockfd,buffer,255);
	buffer[strcspn(buffer, "\n")] = 0;
	if (n <= 0) 
	  break;
	printf("Received %s\n", buffer);
	
	for (int i = 0; i < strlen(buffer); i++ ) {
	  sendChar(newsockfd, buffer[i]+1);
	  sleep(1);
	}
	//sendString(newsockfd, "done");
	*/
	close( newsockfd );
	break;
     }
     return 0; 
}
