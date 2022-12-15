#pragma once

#include <iostream>
#include <string>
#include <Message.hpp>
#include <Colors.hpp>

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
	const std::string &getNickname() const { return nickname_; }
	const std::string &getUsername() const { return username_; }
	const std::string &getRealname() const { return realname_; }
	void setNickname(std::string nick) { nickname_ = nick; }
	void setUsername(std::string username) { username_ = username; }
	void setRealname(std::string realname) { realname_ = realname; }

private:
	int fd_;
	std::string nickname_; // max len 9
	std::string username_;
	std::string realname_;
	std::string message_; // max len 512
	Message parsed_msg_;
};
