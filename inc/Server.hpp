#pragma once

#include <string>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/poll.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <vector>

#define BACKLOG 10

class Server
{
public:
	// Constructor Destructor
	Server();
	Server(int, std::string);
	~Server();

	// start point
	void start();
	void setupSocket();

private:
	int port_; // port number to connect to client
	int nfds_; // number of connected file  descriptor
	int master_sd_; // server socket file descriptor
	std::string password_;
	std::vector<struct pollfd> pollfds_;
};
