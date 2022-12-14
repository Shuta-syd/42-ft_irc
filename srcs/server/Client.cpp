#include <Client.hpp>

Client::Client() {}

Client::Client(int fd, const std::string  &nick): fd_(fd), nickname_(nick) {}

Client::~Client() {}

/**
 * @brief Parsing irc client messages into three types
 */
void Client::parse() {
	int i = 0;

	if (message_[i] == ':')
		parsed_msg_.parsePrefix(message_, i);
	parsed_msg_.parseCommand(message_, i);
	parsed_msg_.parseParams(message_, i);
}

/**
 * Setter Getter
 */

void Client::addMessage(std::string msg) {
	this->message_ += msg;
}

const std::string &Client::getMessage() const {
	return this->message_;
}
