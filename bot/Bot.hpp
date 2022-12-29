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

class Bot {
public:
	Bot();
	Bot(int port, std::string password, std::string ch);
	~Bot();

	void start();

private:
	bool isAuth_;
	int bot_sd_;
	int port_;
	std::string password_;
	std::string nick_;
	std::string channelName_;
	struct pollfd pollfd_;
	std::string message_;
	std::string parsedMessage_;
	int auth_counter_;
	bool isVoted_;

	void receive();
	void execute();

	void setupBotSocket();
	void createPoll();
	void authorize();

	void parseMessage();
	void vote(std::string);
	void addNG_Keyword(std::string);
};

int find(const std::string &str, const std::string &target);

#endif
