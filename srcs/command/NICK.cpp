#include "Command.hpp"

/**
 * @brief set nickname client
 *
 * NICK <nickname>
 */

//#issue7
#define ERR_NONICKNAMEGIVEN ":ircserv 431 :No nickname given\n"
#define ERR_ERRONEUSNICKNAME(nick) ":ircserv 432 " + nick + " :Erroneus nickname\n"
#define ERR_NICKNAMEINUSE(nick) ":ircserv 433 " + nick + " :Nickname is already in use\n"
#define ERR_ADYREGISTRED(nick) ":ircserv 462 " + nick + " :You may not reregister\n"
//bool should_be_cap = true; ← clientごとに終わらせる
//もし情報が不足していたら、これをfalseにする

void NICK(Client &client, Server &server) {
	const int &fd = client.getFd();
	std::string const oldNick = client.getNickname();
	std::string const &newNick = client.getParams()[0];
	/****** settings map<string, int> *******/
	server.setMp_nick_to_fd(newNick, fd);
	client.setNickname(newNick);
	/****************************************/

	/****** Error handling *******/

	sendMessage(fd, NICK_MESSAGE(oldNick, newNick), 0);
	client.should_be_cap = true;
};
