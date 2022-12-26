#include <Server.hpp>
bool isCorrectFmt(std::vector<std::string> const &params, Client &client);

/**
 * @brief execute privmsg command
 *
 * PRIVMSG <target> <message to send>
 */
void PRIVMSG(Client &client, std::map<std::string, int> mp_nick_to_fd, std::map<std::string, Channel> &channels)
{
	std::string nick = client.getNickname();
	std::vector<std::string> const &params = client.getParams();

	if (isCorrectFmt(params, client) == false)
		return;

	const std::string message = params.at(1);

	/* check if client sends msg to channnel or not  */
	if (params.at(0)[0] == '#')
	{
		const std::string channelName = &params[0][1];
		/* in the case of "No such a channel" */
		if (findChannel(channels, channelName) == false)
		{
			sendMessage(client.getFd(), ERR_NOTONCHANNEL(client.getNickname(), params[0]), 0);
			return;
		}
		else
		{
			const Channel &channel = channels[channelName];
			const std::vector<Client> &members = channel.getMember();
			for (std::vector<Client>::const_iterator it = members.begin(); it != members.end(); it++)
			{
				sendMessage(it->getFd(), PRIVMSG_MESSAGE(nick, client.getUsername(), client.getHostname(), "#" + channelName, message), 0);
				return;
			}
		}
	}
	else
	{
		int fd;
		const std::string targetNick = params.at(0);
		/* get Target fd but if there is no client that is the same as the Target name, it returns 0  */
		if ((fd = mp_nick_to_fd[targetNick]) == 0)
		{
			sendMessage(client.getFd(), ERR_NOSUCHNICK(client.getNickname()), 0);
			return;
		}
		sendMessage(fd, PRIVMSG_MESSAGE(nick, client.getUsername(), client.getHostname(), targetNick, message), 0);
	}
}

bool isCorrectFmt(std::vector<std::string> const &params, Client &client)
{
	if (params.size() == 0)
	{
		sendMessage(client.getFd(), ERR_NEEDMOREPARAMS(client.getNickname(), "PRIVMSG"), 0);
		return false;
	}
	else if (params.size() < 2)
	{
		sendMessage(client.getFd(), ERR_NOTEXTTOSEND(client.getNickname()), 0);
		return false;
	}
	return true;
}
