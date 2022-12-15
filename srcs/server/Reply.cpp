#include <Reply.hpp>

/**
 * @brief to send message to client
 * @param fd client fd
 * @param msg message
 * @param flag send option
 */
void sendMessage(int fd, std::string msg, int flag)
{
	send(fd, msg.c_str(), msg.size(), flag);
}
