#pragma once

#include <string>
#include <vector>

class Message
{
public:
	Message();
	~Message();

	void parsePrefix(const std::string&, int &);
	void parseCommand(const std::string &, int &);
	void parseParams(const std::string &, int &);


private:
	std::string prefix_;
	std::string command_;
	std::vector<std::string> params_;
};
