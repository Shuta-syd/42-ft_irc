#include <Command.hpp>

/*
 * rfc 1459.pdf's 21 page(in 54 page)
 * @params
 * <channel> <user> [<comment>]
 * [important point] only channel operator can kick them out
 *
 */

bool is_operator(std::string const &nick, Channel &channel) {
	return true;
}

void KICK(Client &client, std::map<std::string, Channel> channels) {
	int fd = client.getFd();
	std::string nick = client.getNickname();
	Channel channel = channels[client.getParams()[0]];

	if (client.getParams()[0].size() < 2) {
		sendMessage(fd, ERR_NEEDMOREPARAMS(nick, "KICK"), 0);
	}
//	else if (is_operator(nick, )
}
