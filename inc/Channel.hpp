#pragma once

#include <Client.hpp>

class Channel
{
public:
	Channel();
	~Channel();
	const std::vector<Client> &getMember() const { return members_; }
	const std::string &getTopic() const { return topic_; }
	const std::string &getName() const { return name_; }
	void setName(std::string name) { name_ = name; }
	void setTopic(std::string topic) { topic_ = topic; }
	void setOperator(Client operator) { operator_ = operator; }

private:
	std::string name_;
	Client operator_;
	std::string topic_;
	std::vector<Client> members_;
};
