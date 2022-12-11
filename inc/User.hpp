#pragma once

#include <string>

class User
{
public:
	User();
	User(int);
	~User();

private:
	int fd_;
	std::string nick_;
	std::string msg_buf_;
};
