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

char buffer_list[256][256];
int sockfd;
int list_index = 0;

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

void *ioThread(void *arg) { 
  char buffer[256];
	while(1){  
    printf("Please enter a name: ");
    bzero(buffer,256);
    fgets(buffer,255,stdin);
    strcat(buffer_list[list_index++], buffer);
  }
  return 0;
}

void *sendThread(void *arg) { 
  int count = 0;
  char* data;
  while(1) {
    if(count < list_index) {
      char *str = buffer_list[count];
      for (int i = 0; i < strlen(str)-1; i++ ) {
        sendChar(sockfd, str[i]);
        sleep(1);
        //printf("\rFrom server: %s", data);
        //fflush(stdout);
      }
      sendString(sockfd, "done");
      data = getData(sockfd);
      printf("\n%s --> %s\n", str, data);
      count++;
    }
  }
  return 0;
}

int main(int argc, char *argv[])
{
    int portno = 51717, n; //51717
    char serverIp[] = "10.53.27.120";
    struct sockaddr_in serv_addr;
    struct hostent *server;
    pthread_t t1, t2;

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

    pthread_create(&t1, NULL, ioThread, NULL); 
    pthread_create(&t2, NULL, sendThread, NULL);

    pthread_join(t1, NULL);  
    pthread_join(t2, NULL);
      
    close( sockfd );
    return 0;
}
