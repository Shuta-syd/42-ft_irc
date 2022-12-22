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
	int getMaxMember() const { return maxMember_; }
	std::string getCreatedTime() const { return createdTime_; }
	std::string getMode() const { return mode_; }
	void setMember(Client &member);
	void addMode(const char mode);
	void setName(std::string name);
	void setKey(std::string key);
	void setMaxMember(int max) { maxMember_ = max; }
	void setCreatedTime(std::string time) { createdTime_ = time; }
	void setTopic(std::string topic);
	void setTopicAllow(bool isAllow) { topicAllow_ = isAllow; }
	void addOper(std::string name);
	bool is_inChannel(std::string const &nick_name);
	bool is_operator(std::string const &nick_name);
	void eraseMember(Client const &name);
	void delOper(std::string name);
	void delMode(const char mode);

private:
	std::string name_;
	std::string key_;
	std::vector<std::string> opers_;
	bool topicAllow_;
	std::string topic_;
	std::string mode_; // 本当はabc順に並べ直すのがベター
	int maxMember_;
	std::string createdTime_;
	std::vector<Client> members_;
};
