#pragma once

#include <string>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

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
	void startPoll();

private:
	int port_;
	std::string password_;
};
