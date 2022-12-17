#pragma once

#include <Client.hpp>
class Client;

class Channel
{
public:
	Channel();
	~Channel();
	const std::vector<Client> &getMember() const { return members_; }
	const std::string &getTopic() const { return topic_; }
	const std::string &getName() const { return name_; }
	void setMember(Client &member) { members_.push_back(member); }
	void setName(std::string name) { name_ = name; }
	void setTopic(std::string topic) { topic_ = topic; }
	void setOperator(Client *oper) { oper_ = oper; }

private:
	std::string name_;
	Client *oper_;
	std::string topic_;
	std::vector<Client> members_;
};
