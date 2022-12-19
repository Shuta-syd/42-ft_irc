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
#include <Client.hpp>

#define MSG_MAX 1024
#define TIMEOUT 3 * 60 * 1000

class Server
{
public:
	// Constructor Destructor
	Server();
	Server(int port, const std::string &password);
	~Server();
	void setMp_nick_to_fd(std::string const &nick, int const fd) {
		mp_nick_to_fd[nick] = fd;
	}
	//may
	int getFd_from_nick(std::string const &nick) {
		return mp_nick_to_fd[nick];
	}
	std::map<std::string , int > &getMp_nick_to_fd() {
		return mp_nick_to_fd;
	}

	std::vector<struct pollfd> &get_polldfs(){return pollfds_;}

  void start();

  std::map<int, Client>&getUsers()  { return this->users_; };
	void setMp_nick_to_fd(std::string const &nick, int const fd) {
		mp_nick_to_fd[nick] = fd;
	}
	int getFd_from_nick(std::string const &nick) {
		return mp_nick_to_fd[nick];
	}

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
