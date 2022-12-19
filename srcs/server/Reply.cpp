#include <Reply.hpp>

/**
 * @brief to send message to client
 * @param fd client fd
 * @param msg message
 * @param flag send option
 */
void sendMessage(int fd, const std::string &msg, int flag)
{
	send(fd, msg.c_str(), msg.size(), flag);
	std::cout << YEL << msg << RES << std::endl;
}

/**
 * @brief to send message to client
 * @param fd client fd
 * @param msg message
 * @param flag send option
 */
void sendERROR(int fd, const std::string &msg, int flag)
{
	send(fd, msg.c_str(), msg.size(), flag);
	throw std::runtime_error(msg.c_str());
	std::cout << YEL << msg << RES << std::endl;
}
/**
 * @brief send welcome message at the first connection
 * @param client
 */
void sendWelcomeMessage(const Client &client)
{
	const int &fd = client.getFd();
	const std::string &nick = client.getNickname();

	sendMessage(fd, RPL_WELCOME(nick), 0);
	sendMessage(fd, RPL_YOURHOST(nick), 0);
	sendMessage(fd, RPL_CREATED(nick), 0);
	sendMessage(fd, RPL_MYINFO(nick), 0);
}


/**
 * @brief send auth fail message to the client
 *
 */
void sendAuthfail(const Client &client) {
	const int &fd = client.getFd();

	sendMessage(fd, "auth fail\r\n", 0);
}
