#include <Command.hpp>

/**
 * @brief set nickname client
 *
 * NICK <nickname>
 */
void NICK(Client &client, const std::vector<std::string> &params){
	const int &fd = client.getFd();
	const std::string &nick = params[0];

	client.setNickname(nick);
	sendMessage(fd, NICK_MESSAGE(nick), 0);
};
