#include "Command.hpp"

/**
 * @brief set nickname client
 *
 * NICK <nickname>
 */

//#issue7
#define ERR_NONICKNAMEGIVEN ":ft_irc 431 :No nickname given\n"
#define ERR_ERRONEUSNICKNAME(nick) ":ft_irc 432 " + nick + " :Error one use nickname\n"
#define ERR_NICKNAMEINUSE(nick) ":ft_irc 433 " + nick + " :Nickname is already in use\n"
#define ERR_ADYREGISTRED(nick) ":ft_irc 462 " + nick + " :You may not reregister\n"
//bool should_be_cap = true; ← clientごとに終わらせる
//もし情報が不足していたら、これをfalseにする

bool is_proper_words(std::string const &words) {
	return words.find_first_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") == std::string::npos;
}

bool is_proper_size(std::string const &words) {
	return 1 <= words.size() && words.size() <= 9;
}

void NICK(Client &client, Server &server) {
	client.should_be_cap = false;

	const int &fd = client.getFd();
	std::string const &newNick = client.getParams()[0];
	/********** Error handling **************/
	if (client.getParams().size() < 1) {
		sendMessage(fd, ERR_NONICKNAMEGIVEN, 0);
	} else if (is_proper_words(newNick) == false
	|| is_proper_size(newNick) == false) {
		sendMessage(fd, ERR_ERRONEUSNICKNAME(client.getParams()[0]), 0);
	/****************************************/
	} else {
		/********** Success Case ***************/
		std::string const oldNick = client.getNickname();
		/****** settings map<string, int> *******/
		server.setMp_nick_to_fd(newNick, fd);
		client.setNickname(newNick);
		/****************************************/
		sendMessage(fd, NICK_MESSAGE(oldNick, newNick), 0);
		client.should_be_cap = true;
	}
};
