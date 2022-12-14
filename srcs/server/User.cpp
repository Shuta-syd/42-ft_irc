#include <User.hpp>

User::User() {}

User::User(int fd, const std::string  &nick): fd_(fd), nickname_(nick) {}

User::~User() {}

/**
 * @brief Parsing irc client messages into three types
 */
void User::parse() {
	int i = 0;

	if (message_[i] == ':')
		parsed_msg_.parsePrefix(message_, i);
	parseCommand(message, i);
	parseParams(message, i);
}

/**
 * Setter Getter
 */

void User::addMessage(std::string msg) {
	this->message_ += msg;
}

const std::string &User::getMessage() const {
	return this->message_;
}
