#include <Command.hpp>
bool validateMessage(Client &client, const std::vector<std::string> &params, std::map<std::string, Channel> channels, std::map<std::string, int> nick_to_fd);

/**
 * @brief invite a user to a channel
 *
 * INVITE <nickname> <channel>
 */
void INVITE(Client &client, std::map<std::string, int> nick_to_fd, std::map<std::string, Channel> &channels)
{
	const int fd = client.getFd();
	const std::vector<std::string> &params = client.getParams();
	const std::string &nick = client.getNickname();

	/* error check part */
	if (validateMessage(client, params, channels, nick_to_fd) == false) {
		return ;
	}
	const std::string channelName = &params[1][1];
	/* no error happen */
	sendMessage(fd, RPL_INVITING(nick, params[0], channelName), 0);
	sendMessage(nick_to_fd[params[0]], INVITE_MESSAGE(nick, client.getUsername(), client.getHostname(), params[0], channelName), 0);

	client.addInvited(channelName);
}

bool validateMessage(Client &client, const std::vector<std::string> &params, std::map<std::string, Channel> channels, std::map<std::string, int> nick_to_fd)
{
	const std::string nick = client.getNickname();

	if (params.size() != 2)
	{
		sendMessage(client.getFd(), ERR_NEEDMOREPARAMS(nick, "INVITE"), 0);
		return false;
	}
	else if (findChannel(channels, &params[1][1]) == false)
	{
		sendMessage(client.getFd(), ERR_NOSUCHCHANNEL(nick, &params[1][1]), 0);
		return false;
	}

	Channel &channel = channels[&params[1][1]];

	if (nick_to_fd[params[0]] == 0)
	{
		sendMessage(client.getFd(), ERR_NOSUCHNICK(nick), 0);
		return false;
	}
	else if (channel.is_inChannel(nick) == false)
	{
		sendMessage(client.getFd(), ERR_NOTONCHANNEL(nick, &params[1][1]), 0);
		return false;
	}
	else if (channel.is_operator(nick) == false)
	{
		sendMessage(client.getFd(), ERR_CHANOPRIVSNEEDED(nick, &params[1][1]), 0);
		return false;
	}
	else if (channel.is_inChannel(params[0]) == true)
	{
		sendMessage(client.getFd(), ERR_USERONCHANNEL(nick, params.at(0), &params.at(0)[1]), 0);
		return false;
	}
	return true;
}
