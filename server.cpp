// UDP Pinger

// Must have this server running before you can run the UDP Pinger Client code

#include <iostream>
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <time.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

#define PORT	 1027

using namespace std;

int main() { 
	int sockfd, n, count;
	socklen_t len;
	char buffer[1024];
	char msg[1024];
	struct sockaddr_in servaddr, cliaddr; 
	string temp;
	
	// Create a UDP socket
	// Notice the use of SOCK_DGRAM for UDP packets
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	
	memset(&servaddr, 0, sizeof(servaddr)); 
	memset(&cliaddr, 0, sizeof(cliaddr)); 
	
	// Fill server information 
	servaddr.sin_family = AF_INET; // IPv4 
	servaddr.sin_addr.s_addr = INADDR_ANY; // localhost
	servaddr.sin_port = htons(PORT); // port number
	
	// Bind the socket with the server address 
	bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr));
	count = 0;
	//count is equal to number of clients messages recieved
        while (count < 2) {
		//Receive the client packet along with the address it is coming from
		n = recvfrom(sockfd, (char *)buffer, sizeof(buffer), 
			MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len);
		buffer[n] = '\0';
		//check contents of buffer to determine client x or y
		if(buffer[7] == 'X') {
			//first client recieved
			if(count==0) {
				temp = "X:Alice recieved before Y:Bob";
			}
			// not first client recieved
			else {
				temp = "Y:Bob recieved before X:Alice";
			}
			count++;
		}
		else if(buffer[7] == 'Y') {
			//first client recieved
			if(count==0) {
				temp = "Y:Bob recieved before X:Alice";
			}
			//not first client recieved
			else {
				temp = "X:Alice recieved before Y:Bob";
			}
			count++;
		}
		//transfer contents of msg to message
		for(int i = 0; i<temp.length(); i++){
			msg[i] = temp[i];
		}
		msg[message.length()] = '\0';
		//send message to clients containing which client came first
		sendto(sockfd, (const char *)msg, strlen(buffer), 
			MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len);
		
	}
	cout<< "Sent acknowledgment to both X and Y";
	return 0; 
}
