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
