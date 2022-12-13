#include <User.hpp>

User::User() {}

User::User(int fd, std::string nick): fd_(fd), nickname_(nick) {}

User::~User() {}

/**
 * @brief Parsing irc client messages into three types
 */
void User::parse() {

}


/**
 * Setter Getter
 */

void User::setMessage(std::string msg) {
	this->message_ += msg;
}
