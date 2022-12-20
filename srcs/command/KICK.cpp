#include <Command.hpp>

/*
 * rfc 1459.pdf's 21 page(in 54 page)
 * @params
 * <channel> <user> [<comment>]
 * [important point] only channel operator can kick them out
 * #issue 22
 */

bool is_nick_in_channel(std::string const &nick, Channel &channel) {
	std::vector<Client> const &members = channel.getMember();

	for (std::vector<Client>::const_iterator it = members.begin(); it != members.end(); it++) {
		if (nick == it->getNickname()) {
			return true;
		}
	}
	return false;
}

void KICK(Client &client, std::map<std::string, Channel> channels) {
	int fd = client.getFd();
	std::string const &nick = client.getNickname();
	Channel channel = channels[client.getParams()[0]];
	std::string const &frightened_person = client.getParams()[1];

	if (client.getParams()[0].size() < 2) {
		sendMessage(fd, ERR_NEEDMOREPARAMS(nick, "KICK"), 0);
	} else if (channel.getOper() != nick) {
		sendMessage(fd, ERR_NOPRIVILEGES(nick), 0);
	} else if (is_nick_in_channel(frightened_person, channel) == false) {
		sendMessage(fd, ERR_NOSUCHNICK(frightened_person), 0);
	} else if (is_nick_in_channel(nick, channel) == false) {
		sendMessage(fd, ERR_NOTONCHANNEL(nick, channel.getName()), 0);
	}
}
