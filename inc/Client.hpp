#pragma once

#include <Message.hpp>
#include <iostream>
#include <string>

class Client
{
public:
	Client();
	Client(int fd, const std::string& nick);
	~Client();

	void parse(const std::string &message);

	// setter getter
	void addMessage(std::string message);
	void clearMessage();
	void clearParsedMessage();
	const std::string &getMessage() const {return message_;}
	const Message &getParsed_msg() const {return parsed_msg_;}
	const int &getFd() const { return fd_; }
	const std::string &getNick() const { return nickname_; }
	void setNickname(std::string nick) { nickname_ = nick; }

private:
	int fd_;
	std::string nickname_; // max len 9
	std::string username_;
	std::string hostname_;
	std::string message_; //max len 512
	Message parsed_msg_;
};
