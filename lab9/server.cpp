#include <stdio.h>		// printf()
#include <stdlib.h>		// atoi()
#include <sys/socket.h>	// socket(), bind(), listen(), accept()
#include <unistd.h>		// close()

#include "helpers.h"	// make_server_sockaddr()

static const int MAX_MESSAGE_SIZE = 256;

/**
 * Receives a string message from the client, prints it to stdout, then
 * sends the integer 42 back to the client as a success code.
 *
 * Parameters:
 * 		connectionfd: File descriptor for a socket connection (e.g. the one
 *			returned by accept())
 * Returns:
 *		0 on success, -1 on failure.
 */
int handle_connection(int connectionfd) {
	// TODO: Implement this function

	// (1) Receive message from client.
	char message[MAX_MESSAGE_SIZE];
	for(int i = 0; i < MAX_MESSAGE_SIZE; i++){
		recv(connectionfd, message + i, 1, MSG_WAITALL);
		if(message[i] == '\0'){
			break;
		}
	}

	// (2) Print out the message
	printf("Client %d says '%s'\n", connectionfd, message);

	// (3) Send response code to client
	int response = 42;
	send(connectionfd, &response, sizeof(response), 0);
	// (4) Close connection
	close(connectionfd);

	return -1;
}

/**
 * Endlessly runs a server that listens for connections and serves
 * them _synchronously_.
 *
 * Parameters:
 *		port: The port on which to listen for incoming connections.
 *		queue_size: Size of the listen() queue
 * Returns:
 *		-1 on failure, does not return on success.
 */
int run_server(int port, int queue_size) {
	// TODO: Implement the rest of this function
	
	// (1) Create socket
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	// (2) Set the "reuse port" socket option
	int yesval = 1;
	setsocketopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yesval, sizeof(yesval));
	// (3) Create a sockaddr_in struct for the proper port and bind() to it.
	struct sockaddr_in addr;
	if (make_server_sockaddr(&addr, port) == -1) {
		return -1;
	}
	bind(sockfd, (const sockaddr *) &addr, sizeof(addr));
	// (4) Begin listening for incoming connections.
	listen(sockfd, queue_size);
	// (5) Serve incoming connections one by one forever.
	while (true) {
		int connectionfd = accept(sockfd, 0, 0);
		handle_connection(connectionfd);
	}
}

int main(int argc, const char **argv) {
	// Parse command line arguments
	if (argc != 2) {
		printf("Usage: ./server port_num\n");
		return 1;
	}
	int port = atoi(argv[1]);
	printf("Starting server on port %d\n", port);

	if (run_server(port, 10) == -1) {
		return 1;
	}
	return 0;
}
