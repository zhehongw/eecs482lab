#include <stdio.h>		// printf()
#include <stdlib.h>		// atoi()
#include <string.h>		// strlen()
#include <sys/socket.h>	// socket(), connect()
#include <unistd.h>		// close()
#include <iostream>
#include <string>

#include "helpers.h"	// make_client_sockaddr()

static const int MAX_MESSAGE_SIZE = 512;

/**
 * Sends a string message to the server and waits for an integer response.
 *
 * Parameters:
 *		hostname: Remote hostname of the server.
 *		port: Remote port of the server.
 * 		message: The message to send.
 * Returns:
 *		The server's response code on success, -1 on failure.
 */
int send_message(const char *hostname, int port, const char *message) {
	if (strlen(message) > MAX_MESSAGE_SIZE) {
		printf("Error: Message exceeds maximum length\n");
		return -1;
	}

	// TODO: Implement the rest of this function

	// (1) Create a socket
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	// (2) Create a sockaddr_in to specify remote host and port
	struct sockaddr_in addr;
	if(make_client_sockaddr(&addr, hostname, port) == -1) {
        std::cerr << "error making client" << std::endl;
		return -1;
	}

	// (3) Connect to remote server
	if(connect(sockfd, (const sockaddr *)&addr, sizeof(addr))){
        std::cerr << "error connecting socket" << std::endl;
        return -1;
    }
	// (4) Send message to remote server
    if(send(sockfd, message, strlen(message)+1, 0)==-1){
        std::cerr << "error sending message" << std::endl;
        return -1;
    }
	// (5) Wait for integer response
    char recv_data[512];
    memset(recv_data, 0, sizeof(recv_data));
    int recv_len = recv(sockfd, recv_data, sizeof(recv_data), 0);
    if (recv_len == -1) {
        std::cerr << "error receiving message" << std::endl;
        return -1;
    }
    std::cout << "Incoming message: " << std::string(recv_data) << std::endl;
	// (6) Close connection
	close(sockfd);
	return 0;
}

int main(int argc, const char **argv) {
	// Parse command line arguments
	if (argc != 3) {
		printf("Usage: ./test_non_standard_client hostname port_num \n");
		return 1;
	}
	const char *hostname = argv[1];
	int port = atoi(argv[2]);
	const char *message = "HAHAHAHA, Let's crash the file system!!!!!";
	printf("Sending message %s to %s:%d\n", message, hostname, port);

	int response = send_message(hostname, port, message);
	if (response == -1) {
		printf("Refused by the server, attach failed, sad\n");
		return 1;
	}
	printf("Server responds with status code %d\n", response);
	return 0;
}
