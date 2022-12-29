#ifndef DEFINE_IRC_BOT
#define DEFINE_IRC_BOT

#include <string>
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <BotReply.hpp>

#define MSG_MAX 1024

class Bot {
public:
	Bot();
	Bot(int port, std::string password);
	~Bot();

	void start();
	void receive(int fd);
	void setupBotSocket();
	void authorize();

private:
	int bot_sd_;
	int port_;
	std::string password_;
	std::string nick_;
};

#endif
