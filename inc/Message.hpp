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

	const std::string &getPrefix() const { return prefix_; }
	const std::string &getCommand() const { return command_; }
	const std::vector<std::string> &getParams() const { return params_; }

private:
	std::string prefix_;
	std::string command_;
	std::vector<std::string> params_;
};
