#include "Command.hpp"
bool is_proper_words(std::string const &words);
bool is_proper_size(std::string const &words);
bool is_already_registered(std::string const &nick, std::map<std::string, int> mp_nick_to_fd);

/**
 * @brief set nickname client
 * NICK <nickname>
 *
 * bool should_be_cap_nick = true; ← clientごとに終わらせる
 * もし情報が不足していたら、これをfalseにする
 */
void NICK(Client &client, std::map<std::string, int> &mp_nick_to_fd) {
	client.should_be_cap_nick = false;
	const int &fd = client.getFd();

	if (client.getParams().size() < 1)
	{
		sendMessage(fd, ERR_NONICKNAMEGIVEN, 0);
		return ;
	}
	std::string const &newNick = client.getParams()[0];

	/********** Error handling **************/
	if (is_proper_size(newNick) == false) {
		sendMessage(fd, ERR_ERRONEUSNICKNAME(client.getParams()[0]), 0);
	} else if (is_already_registered(newNick, mp_nick_to_fd) == true) {
		sendMessage(fd, ERR_NICKNAMEINUSE(newNick), 0);
	/****************************************/
	} else {
		/********** Success Case ***************/
		std::string const oldNick = client.getNickname();
		mp_nick_to_fd[newNick] = fd;
		client.setNickname(newNick);
		sendMessage(fd, NICK_MESSAGE(oldNick, newNick), 0);
		client.should_be_cap_nick = true;
	}
};


bool is_proper_words(std::string const &words)
{
	return words.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") == std::string::npos;
}

bool is_proper_size(std::string const &words)
{
	return 1 <= words.size() && words.size() <= 9;
}

bool is_already_registered(std::string const &nick, std::map<std::string, int> mp_nick_to_fd)
{
	return mp_nick_to_fd[nick] > 0;
}
