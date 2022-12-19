#pragma once

#include <Client.hpp>
class Client;

class Channel
{
public:
	Channel();
	Channel(const Channel&);
	~Channel();
	Channel &operator=(const Channel &other);

	const std::vector<Client> &getMember() const { return members_; }
	const std::string &getTopic() const { return topic_; }
	const std::string &getName() const { return name_; }
	const std::string &getKey() const { return key_; }
	Client *getOper() const { return oper_; }
	void setMember(Client &member) { members_.push_back(member); }
	void setName(std::string name) { name_ = name; }
	void setKey(std::string key) { key_ = key; }
	void setTopic(std::string topic) { topic_ = topic; }
	void setOper(Client *oper) { oper_ = oper; }


private:
	std::string name_;
	std::string key_;
	Client *oper_;
	std::string topic_;
	std::vector<Client> members_;
};
