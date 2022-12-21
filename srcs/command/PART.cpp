#include <Command.hpp>

/*
 *
 * #issue 26
 * @params
 * <channel> [<reason>]
 *
 */

void PART(Client &client, std::map<std::string, Channel> const &channels) {
	int fd = client.getFd();
	std::string nick = client.getNickname();
	if (client.getParams().size() < 1) {
		sendMessage(fd, ERR_NEEDMOREPARAMS(nick, "PART"), 0);
	} else {
		;
	}
}
