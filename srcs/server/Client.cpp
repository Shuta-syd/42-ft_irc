#include <Client.hpp>
#include <Channel.hpp>

Client::Client() {}

Client::Client(int fd, const std::string  &nick): fd_(fd), nickname_(nick), is_auth_(false) {}

Client::~Client() {}


/**
 * @brief Parsing irc client messages into three types
	*/
void Client::parse(const std::string &message) {
	int i = 0;

	if (message[i] == ':')
		this->parsePrefix(message, i);
	this->parseCommand(message, i);
	this->parseParams(message, i);

	std::cout << GRN << "-------Parsed Message-------" << RES << std::endl;
	std::cout << "Prefix: " << "[" << this->getPrefix() << "]"<< std::endl;
	std::cout << "Command: " << "["<< this->getCommand() << "]" << std::endl;
	std::cout << "Params: " << std::endl;
	for (size_t i = 0; i < this->getParams().size(); i++)
		std::cout << "["<< this->getParams()[i] << "]" << std::endl;
	std::cout << "End" << std::endl;
	std::cout << GRN << "---------------------------" << RES << std::endl;
}

/**
 * @brief Parse prefix from client message
 *
 * @param message client message
 * @param i index of message
 */
void Client::parsePrefix(const std::string &message, int &i)
{
	i = 1;

	while (message[i] != ' ') // prefix
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
void Client::parseCommand(const std::string &message, int &i)
{

	while (message[i] != ' ' && message[i] != '\r' && message[i] != '\n')
	{
		command_.append(&message[i], 1);
		i++;
	}

	while (message[i] == ' ')
		i++;
}

/**
 * @brief Parse params from client message
 *
 * @param message client message
 * @param i index of message
 */
void Client::parseParams(const std::string &message, int &i)
{

	while (message[i] != '\r' && message[i] != '\n')
	{
		std::string param;

		if (message[i] == ':')
		{
			i += 1;
			while (message[i] != '\r' && message[i] != '\n')
			{
				param.append(&message[i], 1);
				i++;
			}
		}
		while (message[i] != ' ' && message[i] != '\r' && message[i] != '\n')
		{
			param.append(&message[i], 1);
			i++;
		}
		i++;
		params_.push_back(param);
	}
}


void Client::clearParsedMessage() {
	prefix_.clear();
	command_.clear();
	params_.clear();
}

std::map<std::string, Channel> &Client::getChannels() {
	return channels_;
}

void Client::setChannel(const std::string &name, Channel &channel) {
	channels_[name] = channel;
}
