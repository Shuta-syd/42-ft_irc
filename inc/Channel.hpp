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
	const std::vector<Client> &getMember() const ;
	const std::string &getTopic() const ;
	const std::string &getName() const ;
	const std::string &getKey() const ;
	const std::string &getOper() const;
	void setMember(Client &member);
	void setName(std::string name);
	void setKey(std::string key);
	void setTopic(std::string topic);
	void setOper(std::string name);

private:
	std::string name_;
	std::string key_;
	std::string operName_;
	std::string topic_;
	std::vector<Client> members_;
};
