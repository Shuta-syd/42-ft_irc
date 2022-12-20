#include <Command.hpp>

/*
 * rfc 1459.pdf's 21 page(in 54 page)
 * @params
 * <channel> <user> [<comment>]
 * [important point] only channel operator can kick them out
 *
 */


void KICK(Client &client) {
	int fd = client.getFd();
	std::string nick = client.getNickname();
	if (client.getParams()[0].size() < 2) {
		sendMessage(fd, ERR_NEEDMOREPARAMS(nick, "KICK"), 0);
	} else {
		;
	}
}
