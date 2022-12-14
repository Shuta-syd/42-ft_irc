#pragma once

#include <Message.hpp>
#include <iostream>
#include <string>

class Client
{
public:
	Client();
	Client(int, const std::string&);
	~Client();

	void parse();

	// setter getter
	void addMessage(std::string);
	void clearMessage();
	const std::string &getMessage() const;

private:
	int fd_;
	std::string nickname_; // max len 9
	std::string username_;
	std::string hostname_;
	std::string message_; //max len 512
	Message parsed_msg_;
};
