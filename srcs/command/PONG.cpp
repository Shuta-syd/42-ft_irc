#include <Command.hpp>

/**
 * @brief a reply to PING command
 *
 * PONG <server1> [ <server2> ]
 */
void PONG(Client &client, const std::vector<std::string> &params) {
	const int &fd = client.getFd();
	const std::string &serverName = params.at(0);

	sendMessage(fd, PONG_MESSAGE(serverName), 0);
}
