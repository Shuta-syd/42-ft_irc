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

#include <User.hpp>
#include <Reply.hpp>

#define MAX_SOCKET 10
#define MSG_MAX 1024
#define TIMEOUT 3 * 60 * 1000

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
	void createPoll(int);
	void allow();
	void chat(int);

	// send recv funcs
	void sendMessage(int, std::string, int);

private:
	int port_; // port number to connect to client
	int nfds_; // number of connected file  descriptor
	int master_sd_; // server socket file descriptor
	std::string password_;
	std::map<int, std::string> nicks_; // client nicknames map(fd, nick)
	std::map<std::string, User> users_; //client users info map(nick, client);
	std::vector<struct pollfd> pollfds_;
};
