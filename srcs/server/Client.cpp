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
	std::cout << "-------parsed msg-------" << std::endl;
	std::cout << parsed_msg_.getPrefix() << std::endl;
	std::cout << parsed_msg_.getCommand() << std::endl;
	for (size_t i = 0; i < parsed_msg_.getParams().size(); i++)
		std::cout << parsed_msg_.getParams()[i] << std::endl;
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
