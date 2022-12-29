#ifndef DEFINE_IRC_BOT
#define DEFINE_IRC_BOT

#include <string>
#include <iostream>
#include <sys/socket.h>
#include <sys/poll.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <BotReply.hpp>

#define MSG_MAX 1024
#define TIMEOUT 3 * 60 * 1000

class Bot
{
public:
	Bot();
	Bot(int port, std::string password);
	~Bot();

	void start();

private:
	int bot_sd_;
	int port_;
	std::string password_;
	std::string nick_;
	struct pollfd pollfd_;

	void receive();
	void setupBotSocket();
	void createPoll();
	void authorize();
};

#endif
