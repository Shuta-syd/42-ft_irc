#include <Channel.hpp>
#include <Client.hpp>

Channel::Channel() {}

Channel::~Channel(){}


const std::vector<Client> &Channel::getMember() const { return members_; }
const std::string &Channel::getTopic() const { return topic_; }
const std::string &Channel::getName() const { return name_; }
const std::string &Channel::getKey() const { return key_; }
const std::vector<std::string> &Channel::getOper() const { return opers_; }
void Channel::setMember(Client &member) { members_.push_back(member); }
void Channel::setName(std::string name) { name_ = name; }
void Channel::setKey(std::string key) { key_ = key; }
void Channel::setTopic(std::string topic) { topic_ = topic; }
void Channel::addOper(std::string name) { opers_.push_back(name); }

void Channel::eraseMember(Client const &client) {
	std::vector<Client>::iterator itr_begin = members_.begin();
	std::vector<Client>::iterator itr_end = members_.begin();

	for (; itr_begin != itr_end; itr_begin++) {
		if (client.getNickname() == itr_begin->getNickname()) {
			members_.erase(itr_begin);
		}
	}
}
