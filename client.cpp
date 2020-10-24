#include <iostream>
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <time.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <vector>

using namespace std;

#define PORT	 1027

//using command line args to control which client
int main(int args, char *argv[]) { 
	int sockfd;
	socklen_t len;
	char buffer[1024];
	char * message = argv[1];
	struct sockaddr_in servaddr, cliaddr; 
	string msg;
	
	// Create a UDP socket
	// Notice the use of SOCK_DGRAM for UDP packets
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	
	memset(&servaddr, 0, sizeof(servaddr)); 
	memset(&cliaddr, 0, sizeof(cliaddr)); 
	
	// Fill server information 
	servaddr.sin_family = AF_INET; // IPv4 
	servaddr.sin_addr.s_addr = INADDR_ANY; // localhost
	servaddr.sin_port = htons(PORT); // port number
  
		len = sizeof(servaddr);
		//Send message to server
		sendto(sockfd, (const char *) buffer, strlen(buffer), MSG_CONFIRM, (const struct sockaddr *) &servaddr, len);
		//Recieve message form server
		int n;
	        n = recvfrom(sockfd, (char *)buffer, sizeof(buffer), MSG_WAITALL, (struct sockaddr *) &servaddr, &len);
		buffer[n] = '\0';
	//get server message and print out
		msg = string(buffer);
		cout << message << "\n" << msg;
		
	return 0; 
} 
