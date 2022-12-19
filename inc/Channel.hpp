#pragma once

#include <vector>
#include <string>
class Client;

class Channel
{
public:
	Channel();
	// Channel(const Channel&);
	~Channel();
	// Channel &operator=(const Channel &other);

	const std::vector<Client> &getMember() const ;
	const std::string &getTopic() const ;
	const std::string &getName() const ;
	const std::string &getKey() const ;
	Client *getOper() const;
	void setMember(Client &member);
	void setName(std::string name);
	void setKey(std::string key);
	void setTopic(std::string topic);
	void setOper(Client *oper);

private:
	std::string name_;
	std::string key_;
	Client *oper_;
	std::string topic_;
	std::vector<Client> members_;
};
