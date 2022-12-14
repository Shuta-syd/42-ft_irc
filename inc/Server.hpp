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
#include <map>

#include <Client.hpp>
#include <Reply.hpp>

#define BACKLOG 10
#define MSG_MAX 1024
#define TIMEOUT 3 * 60 * 1000

class Server
{
public:
	// Constructor Destructor
	Server();
	Server(int, const std::string&);
	~Server();

	// start point
	void start();
	// send recv funcs
	void sendMessage(int, std::string, int);

private:
	int port_; // port number to connect to client
	int nfds_; // number of connected file  descriptor
	int master_sd_; // server socket file descriptor
	std::string password_;
	std::map<int, Client> users_; //client users info map(fd, client);
	std::vector<struct pollfd> pollfds_;

	void setupServerSocket();
	void createPoll(int);
	void allow();
	void chat(int);
	void setupClient(int sockfd);
};
