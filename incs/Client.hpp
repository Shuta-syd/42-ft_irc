#ifndef DEFINE_IRC_CLIENT
#define DEFINE_IRC_CLIENT

#include <map>
#include <iostream>
#include <string>
#include <vector>
#include <Utils.hpp>
#include <Colors.hpp>

class Channel;
class Client
{
public:
	Client();
	Client(int fd, const std::string &nick);
	~Client();

	// parse
	void parse(const std::string &message);
	void parsePrefix(const std::string &, int &);
	void parseCommand(const std::string &, int &);
	void parseParams(const std::string &, int &);

	// setter getter
	void clearParsedMessage();

	const int &getFd() const { return fd_; }
	const std::string &getNickname() const { return nickname_; }
	const std::string &getUsername() const { return username_; }
	const std::string &getHostname() const { return hostname_; }
	const std::string &getRealname() const { return realname_; }
	const std::string &getPrefix() const { return prefix_; }
	const std::string &getCommand() const { return command_; }
	std::map<std::string, Channel*> &getChannels();
	const std::vector<std::string> &getParams() const { return params_; }
	void setNickname(std::string nick) { nickname_ = nick; }
	void setUsername(std::string username) { username_ = username; }
	void setHostname(std::string hostname) { hostname_ = hostname; }
	void setRealname(std::string realname) { realname_ = realname; }
	void setChannel(const std::string &name, Channel &channel);
	void addInvited(std::string channelName) {isInvited_[channelName] = true;}
	void delInvited(std::string channelName) { isInvited_.erase(channelName); }
	bool isInvited(std::string mode, std::string channelName);
	bool getIsAuth() { return isAuth_; }
	void setIsAuth() { isAuth_ = true; }
	bool getIsNick() { return isNick_; }
	void setIsNick() { isNick_ = true; }
	bool getIsWelcome() { return isWelcome_; }
	void setIsWelcome(bool isWelcome) { isWelcome_ = isWelcome; }
	bool getIsConnected() { return isConnected_; }
	void setIsConnected(bool isConnected) { isConnected_ = isConnected; }

private:
	int fd_;
	bool isAuth_;
	bool isNick_;
	bool isWelcome_;
	bool isConnected_;
	std::string nickname_; // max len 9
	std::string username_;
	std::string hostname_;
	std::string realname_;
	std::string prefix_;
	std::string command_;
	std::vector<std::string> params_;
	std::map<std::string, bool> isInvited_; // <channelName, isInvited>?
	std::map<std::string, Channel*> channels_; // channels This belong to

	void debug_parser();
};

#endif
