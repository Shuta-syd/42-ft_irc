#include <Client.hpp>

Client::Client() {}

Client::Client(int fd, const std::string  &nick): fd_(fd), nickname_(nick) {}

Client::~Client() {}

/**
 * @brief Parsing irc client messages into three types
	*/
void Client::parse(const std::string &message) {
	int i = 0;

	if (message[i] == ':')
		parsed_msg_.parsePrefix(message, i);
	parsed_msg_.parseCommand(message, i);
	parsed_msg_.parseParams(message, i);

	std::cout << GRN << "-------Parsed Message-------" << RES << std::endl;
	std::cout << "Prefix: " << "[" << parsed_msg_.getPrefix() << "]"<< std::endl;
	std::cout << "Command: " << "["<< parsed_msg_.getCommand() << "]" << std::endl;
	std::cout << "Params: " << std::endl;
	for (size_t i = 0; i < parsed_msg_.getParams().size(); i++)
		std::cout << "["<< parsed_msg_.getParams()[i] << "]" << std::endl;
	std::cout << "End" << std::endl;
	std::cout << GRN << "---------------------------" << RES << std::endl;
}

/**
 * Setter Getter
 */
void Client::addMessage(std::string msg) { this->message_ += msg; }

void Client::clearMessage() { this->message_ = ""; }

void Client::clearParsedMessage() {
	Message new_message;
	parsed_msg_ = new_message;
}
