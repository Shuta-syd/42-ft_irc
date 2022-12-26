#include <Command.hpp>

/**
 * @brief the user sending the message to be removed from the list of active members for all given channels
 *
 * PART <channel> *( "," <channel> ) [ <Part Message> ]
 */
void PART(Client &client, std::map<std::string, Channel> &channels, const std::vector<std::string> &params)
{
	int fd = client.getFd();
	std::string message;
	std::string const &nick = client.getNickname();

	if (params.size() < 1)
	{
		sendMessage(fd, ERR_NEEDMOREPARAMS(nick, "PART"), 0);
		return ;
	}

	std::string ch_name = &params[0][1];
	if (findChannel(channels, ch_name) == false)
	{
		sendMessage(fd, ERR_NOSUCHCHANNEL(nick, ch_name), 0);
		return ;
	}

	Channel &channel = channels[ch_name];
	if (channel.is_inChannel(nick) == false) {
		sendMessage(fd, ERR_NOTONCHANNEL(nick, ch_name), 0);
	} else {
		const std::vector<Client> members = channel.getMember();
		for (
				std::vector<Client>::const_iterator it = members.begin();
				it != members.end();
				it++)
		{
			const int targetFd = (*it).getFd();
			const std::string &targetNick = (*it).getNickname();
			sendMessage(targetFd, PART_MESSAGE(nick, client.getUsername(), client.getHostname(), ch_name, message), 0);
			if (targetNick == nick)
				channel.eraseMember(*it);
		}
	}
}
