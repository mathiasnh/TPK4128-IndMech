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
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 
#include <pthread.h>


void error(char *msg) {
    perror(msg);
    exit(0);
}

void sendString(int sockfd, char *str) {
  int n;
  char buffer[32];
  sprintf(buffer, "%s\n", str);
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

char* getData( int sockfd ) {
  int n;
  char buffer[256];
  bzero(buffer, 256);
  n = read(sockfd, buffer, 255);
  if(n < 0)
    error("ERROR reading from socket");
  char *ptr = buffer;
  return ptr;
}

int main(int argc, char *argv[])
{
    int sockfd, portno = 51717, n; //51717
    char serverIp[] = "10.53.25.12";
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[256];
    char* data;

    if (argc < 3) {
      // error( const_cast<char *>( "usage myClient2 hostname port\n" ) );
      printf("contacting %s on port %d\n", serverIp, portno);
      // exit(0);
    }
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        error("ERROR opening socket");

    if ((server = gethostbyname(serverIp)) == NULL) 
        error("ERROR, no such host\n");
    
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
    while(1){
      
      printf("Please enter a name: ");
      bzero(buffer,256);
      fgets(buffer,255,stdin);
      
      for (int i = 0; i < strlen(buffer)-1; i++ ) {
        sendChar(sockfd, buffer[i]);
        sleep(1);
        data = getData(sockfd);
        printf("From server: %s\n", data);
    }
      
      n = write(sockfd, "done", 4);
      if (n < 0)
        error("ERROR writing to socket");
      
    }
    close( sockfd );
    return 0;
}
