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
#include <Command.hpp>
#include <Utils.hpp>

#define MSG_MAX 1024
#define TIMEOUT 3 * 60 * 1000

class Server
{
public:
	// Constructor Destructor
	Server();
	Server(int, const std::string&);
	~Server();
	void setMp_nick_to_fd(std::string const &nick, int const fd) {
		mp_nick_to_fd[nick] = fd;
	}
	//may
	int getFd_from_nick(std::string const &nick) {
		return mp_nick_to_fd[nick];
	}

	void start();
	const std::map<int, Client>&getUsers() const { return this->users_; };

private:
	int port_; // port number to connect to client
	int nfds_; // number of connected file  descriptor
	int master_sd_; // server socket file descriptor
	std::string password_;
	std::map<int, Client> users_; //client users info map(fd, client);
	std::vector<struct pollfd> pollfds_;
	std::map<std::string, Channel> channels_; // every channel that exists
	std::map<std::string, int> mp_nick_to_fd;
	void setupServerSocket();
	void setupClient(int sockfd);
	void createPoll(int);
	void allow();

	void chat(int);

	void execute(Client & client);
};
