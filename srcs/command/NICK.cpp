#include "Command.hpp"
bool is_proper_size(std::string const &words);
bool is_already_registered(std::string const &nick, std::map<std::string, int> mp_nick_to_fd);

/**
 * @brief set nickname client
 * NICK <nickname>
 *
 */

void NICK(Client &client, std::map<std::string, int> &mp_nick_to_fd, std::map<std::string, Channel> &server_channels) {
	const int &fd = client.getFd();

	if (client.getParams().size() < 1) {
		sendMessage(fd, ERR_NONICKNAMEGIVEN, 0);
		return ;
	}
	std::string const &newNick = client.getParams()[0];

	if (is_proper_size(newNick) == false) {
		sendMessage(fd, ERR_ERRONEUSNICKNAME(client.getParams()[0]), 0);
	} else if (is_already_registered(newNick, mp_nick_to_fd) == true) {
		sendMessage(fd, ERR_NICKNAMEINUSE(newNick), 0);
	} else {
		std::string const oldNick = client.getNickname();
		mp_nick_to_fd[newNick] = fd;
		mp_nick_to_fd.erase(oldNick);

		std::map<std::string, Channel> &channels = server_channels;
		std::map<std::string, Channel>::iterator it = channels.begin();
		for (; it != channels.end(); it++) {
			if (it->second.is_operator(oldNick) == true) {
				it->second.delOper(oldNick);
				it->second.addOper(newNick);
			}
		}
		client.setNickname(newNick);
		if (client.getIsAuth())
			sendMessage(fd, NICK_MESSAGE(oldNick, newNick), 0);
	}
}

bool is_proper_size(std::string const &words)
{
	return 1 <= words.size() && words.size() <= 9;
}

bool is_already_registered(std::string const &nick, std::map<std::string, int> mp_nick_to_fd)
{
	return mp_nick_to_fd[nick] > 0;
}
