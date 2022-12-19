#include <Command.hpp>

/**
 * @brief the beginning of connection to specify the username,
 * hostname, and realname of new user
 *
 * USER <username> <hostname> <servername> <realname>
 *
 * [Note]: <realname> may contain space characters
 */

//#issue8
#define ERR_NEEDMOREPARAMS(nick, command) ":ft_irc 461 " + nick + " " + command + " :Not enough parameters\n"
#define ERR_ALREADYREGISTRED(nick) ":ft_irc 462 " + nick + " :You may not reregister\n"

//refarenceはRFC1459の11pageにある
void USER(Client &client) {
	int fd = client.getFd();
	std::string nick = client.getNickname();

	if (client.getParams().size() != 4) {
		sendMessage(fd, ERR_NEEDMOREPARAMS(nick, "USER "), 0);
	} else {
		client.setUsername(client.getParams()[0]);
		client.setRealname(client.getParams()[3]);
	}
}
