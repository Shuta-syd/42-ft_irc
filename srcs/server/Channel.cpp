#include <Channel.hpp>
#include <Client.hpp>

Channel::Channel() {}

Channel::~Channel(){}


const std::vector<Client> &Channel::getMember() const { return members_; }
const std::string &Channel::getTopic() const { return topic_; }
const std::string &Channel::getName() const { return name_; }
const std::string &Channel::getKey() const { return key_; }
const std::string &Channel::getOper() const { return operName_; }
void Channel::setMember(Client &member) { members_.push_back(member); }
void Channel::setName(std::string name) { name_ = name; }
void Channel::setKey(std::string key) { key_ = key; }
void Channel::setTopic(std::string topic) { topic_ = topic; }
void Channel::setOper(std::string name) { operName_ = name; }
