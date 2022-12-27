#ifndef DEFINE_IRC_SERVER
#define DEFINE_IRC_SERVER
#include <cstring>
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
#include <signal.h>
#include <sys/select.h>
#include <stdexcept>
#include <Client.hpp>
#include <Reply.hpp>
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

  void start();

	void setMp_nick_to_fd(std::string const &nick, int const fd) {
		mp_nick_to_fd_[nick] = fd;
	}
	int getFd_from_nick(std::string const &nick) {
		std::map<std::string, int> dummy = mp_nick_to_fd_;
		return dummy[nick];
	}

	int getMstersd() { return master_sd_;}
	void signal_setup();
  std::map<int, Client>&getUsers()  { return this->users_; };
	std::map<std::string , Channel> &getChannels() { return channels_; }
	std::map<std::string, int> &getMp_nick_to_fd() { return mp_nick_to_fd_; }
	std::vector<struct pollfd> &get_polldfs(){return pollfds_;}


private:
	int port_;
	int nfds_;
	int master_sd_;
	std::string password_;
	std::map<int, Client> users_; //client users info map(fd, client);
	std::vector<struct pollfd> pollfds_;

	std::map<std::string, Channel> channels_; // every channel that exists
	std::map<std::string, int> mp_nick_to_fd_;

	void setupServerSocket();
	void setupClient(int sockfd);
	void createPoll(int);
	void allow();

	void chat(int);
	void execute(int fd);
	void debug_all_channels_situation();
	void debug_all_members();
};

void signal_handler(int signal);
#endif
