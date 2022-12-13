#pragma once

#include <string>

class Message
{
public:
	Message();
	~Message();

private:
	std::string prefix_;
	std::string command_;
	std::string params_;
};
