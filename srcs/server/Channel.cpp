#include <Channel.hpp>
#include <Client.hpp>

Channel::Channel() : topicAllow_(false), mode_("nt"), maxMember_(-1) {}

Channel::~Channel(){}

const std::vector<Client> Channel::getMember() const { return members_; }
const std::string Channel::getTopic() const { return topic_; }
const std::string Channel::getName() const { return name_; }
const std::string Channel::getKey() const { return key_; }
const std::vector<std::string> &Channel::getOper() const { return opers_; }
void Channel::setMember(Client &member) {
	members_.push_back(member);
}
void Channel::setName(std::string name) { name_ = name; }
void Channel::setKey(std::string key) { key_ = key; }
void Channel::setTopic(std::string topic) { topic_ = topic; }
void Channel::addOper(std::string name) { opers_.push_back(name); }


bool Channel::is_inChannel(std::string const &nick_nme)  {

	std::vector<Client> const &members = this->getMember();
	for (std::vector<Client>::const_iterator  it = members.begin(); it !=members.end(); it++) {
		if (it->getNickname() == nick_nme) {
			return true;
		}
	}
	return false;
}

bool Channel::is_operator(const std::string &nick_name) {

	std::vector<std::string> const  &members = this->getOper();
	for (std::vector<std::string>::const_iterator  it = members.begin(); it != members.end(); it++) {
		if (*it== nick_name) {
			return true;
		}
	}
	return false;
}

void Channel::eraseMember(Client const &client) {
	std::cout << "\nthis is in erase member function" << std::endl;
	std::vector<Client>::iterator itr_begin = members_.begin();
	for (; itr_begin != members_.end(); itr_begin++) {
		if (client.getNickname() == itr_begin->getNickname()) {
			if (!members_.empty()) {
				members_.erase(itr_begin);
				return ;
			}
		}
	}
}

void Channel::delOper(std::string name) {
	std::vector<std::string>::iterator it = opers_.begin();
	for (; it != opers_.end(); ++it) {
		if ((*it) == name)
			opers_.erase(it);
		return;
	}
}

void Channel::addMode(const char mode)
{
	std::string::iterator it = mode_.begin();
	for (; it != mode_.end(); ++it) {
		if (*it == mode)
			return;
	}
	mode_.push_back(mode);
}

void Channel::delMode(const char mode)
{
	std::string::iterator it = mode_.begin();
	for (;it != mode_.end();++it) {
		if (*it == mode) {
			mode_.erase(it);
			return;
		}
	}
}
