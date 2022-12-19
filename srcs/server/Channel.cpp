#include <Channel.hpp>

Channel::Channel(){}

Channel::~Channel(){}


Channel &Channel::operator=(Channel const &other)
{
	this->name_ = other.getName();
	this->key_ = other.getKey_();
	this->oper_ = other.getOper();
	this->topic_ = other.getTopic();
	this->members_ = other.getMember();
	return (*this);
}
