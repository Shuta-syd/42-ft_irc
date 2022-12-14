#include <Message.hpp>

Message::Message() {}

Message::~Message() {}

/**
 * @brief Parse prefix from client message
 *
 * @param message client message
 * @param i index of message
 */
void Message::parsePrefix(const std::string &message, int &i) {
	i = 1;

	while (message[i] != ' ') //prefix
	{
		prefix_.append(&message[i], 1);
		i++;
	}
	while (message[i] == ' ')
		i++;
}

/**
 * @brief Parse command from client message
 *
 * @param message client message
 * @param i index of message
 */
void Message::parseCommand(const std::string &message, int &i) {

	while (message[i] != '\r' && message[i] != '\n' && message[i] != ' ')
		command_.append(&message[i], 1);

	while (message[i] == ' ')
		i++;
}

/**
 * @brief Parse params from client message
 *
 * @param message client message
 * @param i index of message
 */
void Message::parseParams(const std::string &message, int &i) {
	std::string param;

	while (message[i] != '\r' && message[i] != '\n')
	{
		while (message[i] == ' ')
			i++;
		while (message[i] != ':' && message[i] != ' '
						&& message[i] != '\r' && message[i] != '\n')
		{
			param.append(message[i], 1);
			i++;
		}
		
	}
}
