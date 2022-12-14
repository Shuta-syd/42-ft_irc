#pragma once

#include <Message.hpp>
#include <string>

class User
{
public:
	User();
	User(int, const std::string&);
	~User();

	void parse();

	// setter getter
	void addMessage(std::string);
	const std::string &getMessage() const;

private:
	int fd_;
	std::string nickname_; // max len 9
	std::string username_;
	std::string hostname_;
	std::string message_; //max len 512
	Message parsed_msg_;
};
