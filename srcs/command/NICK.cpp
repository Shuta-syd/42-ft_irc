#include "Command.hpp"

/**
 * @brief set nickname client
 *
 * NICK <nickname>
 */

//#issue7
//ERR_NONICKNAMEGIVEN
//ERR_ERRONEUSNICKNAME
//ERR_NICKNAMEINUSE
//ERR_ALREADYREGISTRED

void NICK(Client &client, Server &server) {
	const int &fd = client.getFd();
	std::string const oldNick = client.getNickname();
	std::string const &newNick = client.getParams()[0];

	/****** settings map<string, int> *******/
	server.setMp_nick_to_fd(newNick, fd);
	client.setNickname(newNick);
	/****************************************/
	sendMessage(fd, NICK_MESSAGE(oldNick, newNick), 0);
};
