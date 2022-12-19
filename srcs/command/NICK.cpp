#include "Command.hpp"

/**
 * @brief set nickname client
 *
 * NICK <nickname>
 */

//#issue7

void NICK(Client &client, Server &server) {
	const int &fd = client.getFd();
	std::string const oldNick = client.getNickname();
	std::string const &newNick = client.getParams()[0];
	server.setMp_nick_to_fd(newNick, client.getFd());

	client.setNickname(newNick);
	sendMessage(fd, NICK_MESSAGE(oldNick, newNick), 0);
};
