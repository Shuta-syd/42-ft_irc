#include <Command.hpp>

/**
 * @brief set nickname client
 *
 * NICK <nickname>
 */
void NICK(Client &client, const std::vector<std::string> &params){
	const int &fd = client.getFd();
	const std::string oldNick = client.getNickname();
	const std::string &newNick = params[0];

	client.setNickname(newNick);
	sendMessage(fd, NICK_MESSAGE(oldNick, newNick), 0);
};
