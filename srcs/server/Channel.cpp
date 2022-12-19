#include <Channel.hpp>

Channel::Channel(){}

Channel::~Channel(){}


Channel &operator=(Channel const &other)
{
	this->name_ = other.getName();
	this->key_ = other.getKey_();
	this->oper_ = other.
	Client *oper_;
	std::string topic_;
	std::vector<Client> members_;
}
