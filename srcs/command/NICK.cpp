#include "Command.hpp"

/**
 * @brief set nickname client
 *
 * NICK <nickname>
 */


void NICK(Client &client) {
	const int &fd = client.getFd();
	std::string const oldNick = client.getNickname();
	std::string const &newNick = client.getParams()[0];

	client.setNickname(newNick);
	sendMessage(fd, NICK_MESSAGE(oldNick, newNick), 0);
};
