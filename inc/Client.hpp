#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <Colors.hpp>
#include <Channel.hpp>

class Channel;
class Client
{
public:
	Client();
	Client(int fd, const std::string& nick);
	~Client();

	//parse
	void parse(const std::string &message);
	void parsePrefix(const std::string &, int &);
	void parseCommand(const std::string &, int &);
	void parseParams(const std::string &, int &);

	// setter getter
	void clearParsedMessage();

	const int &getFd() const { return fd_; }
	const std::string &getNickname() const { return nickname_; }
	const std::string &getUsername() const { return username_; }
	const std::string &getRealname() const { return realname_; }
	const std::string &getPrefix() const { return prefix_; }
	const std::string &getCommand() const { return command_; }
	const std::map<std::string, Channel> const &getChannels() { return channels_; }

	const std::vector<std::string> &getParams() const
	{
		return params_;
	}
	void setNickname(std::string nick) { nickname_ = nick; }
	void setUsername(std::string username) { username_ = username; }
	void setRealname(std::string realname) { realname_ = realname; }
	const bool &getIsAuth() const { return is_auth_; }
	void setIsAuth(bool is_auth) { is_auth_ = is_auth; }
	void setChannel(std::string name, Channel &channel) { channels_[name] = channel; }

private:
	int fd_;
	bool is_auth_;
	std::string nickname_; // max len 9
	std::string username_;
	std::string realname_;
	std::string prefix_;
	std::string command_;
	std::vector<std::string> params_;
	std::map<std::string, Channel> channels_; // channels This belong to
};
