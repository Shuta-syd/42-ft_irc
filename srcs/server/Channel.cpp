#include <Channel.hpp>

Channel::Channel(){}

Channel::Channel(const Channel &other) { *this = other; }

Channel::~Channel(){}

Channel &Channel::operator=(const Channel &other) {
	name_ = other.getName();
	return *this;
}
