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
	const std::vector<Client> getMember() const ;
	const std::string getTopic() const ;
	const std::string getName() const ;
	const std::string getKey() const ;
	const std::vector<std::string> &getOper() const;
	bool getTopicAllow() const { return topicAllow_; }
	std::string getCreatedTime() const { return createdTime_; }
	void setMember(Client &member);
	void setName(std::string name);
	void setKey(std::string key);
	void setCreatedTime(std::string time) { createdTime_ = time; }
	void setTopic(std::string topic);
	void setTopicAllow(bool isAllow) { topicAllow_ = isAllow; }
	void addOper(std::string name);
	void delOper(std::string name);

private:
	std::string name_;
	std::string key_;
	std::vector<std::string> opers_;
	bool topicAllow_;
	std::string topic_;
	std::string createdTime_;
	std::vector<Client> members_;
};
