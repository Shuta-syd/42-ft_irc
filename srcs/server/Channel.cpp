#include <Channel.hpp>
#include <Client.hpp>

Channel::Channel(): topicAllow_(false), maxMember_(-1) {}

Channel::~Channel(){}


const std::vector<Client> Channel::getMember() const { return members_; }
const std::string Channel::getTopic() const { return topic_; }
const std::string Channel::getName() const { return name_; }
const std::string Channel::getKey() const { return key_; }
const std::vector<std::string> &Channel::getOper() const { return opers_; }
void Channel::setMember(Client &member) { members_.push_back(member); }
void Channel::setName(std::string name) { name_ = name; }
void Channel::setKey(std::string key) { key_ = key; }
void Channel::setTopic(std::string topic) { topic_ = topic; }
void Channel::addOper(std::string name) { opers_.push_back(name); }
void Channel::delOper(std::string name) {
	for (
			std::vector<std::string>::iterator it = opers_.begin();
			it != opers_.end();
			++it)
			{
				if ((*it) == name)
					opers_.erase(it);
					return;
			}
}
