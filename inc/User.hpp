#pragma once

#include <Message.hpp>
#include <string>

class User
{
public:
	User();
	User(int, std::string);
	~User();

	void parse();

	// setter getter
	void setMessage(std::string);

private:
	int fd_;
	std::string nickname_;
	std::string username_;
	std::string hostname_;
	std::string message_;
	Message parsed_msg_;
};
