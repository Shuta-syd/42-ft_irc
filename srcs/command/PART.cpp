#include <Command.hpp>
void leaveChannel(Client &client, std::map<std::string, Channel> &allChannels, const std::string &ch_name, const std::string &message);

/**
 * @brief the user sending the message to be removed from the list of active members for all given allChannels
 *
 * PART <channel> *( "," <channel> ) [ <Part Message> ]
 */
void PART(Client &client, std::map<std::string, Channel> &allChannels, const std::vector<std::string> &params)
{
	std::string message;
	int fd = client.getFd();
	std::string const &nick = client.getNickname();


	if (params.size() < 1) {
		sendMessage(fd, ERR_NEEDMOREPARAMS(nick, "PART"), 0);
		return ;
	}else if (params.size() == 2)
		message = params[1];

	const std::vector<std::string> channels = splitChannel(params[0]);
	std::string ch_name = &params[0][1];

	for (size_t i = 0; i < channels.size(); i++)
	{
		const std::string ch_name = &channels[i][1];
		if (findChannel(allChannels, ch_name) == false)
			sendMessage(fd, ERR_NOSUCHCHANNEL(nick, ch_name), 0);
		else
			leaveChannel(client, allChannels, ch_name, message);
	}
}

void leaveChannel(
	Client &client,
	std::map<std::string, Channel> &allChannels,
	const std::string &ch_name,
	const std::string &message
	) {
	int fd = client.getFd();
	std::string const &nick = client.getNickname();
	Channel &channel = allChannels[ch_name];

	if (channel.is_inChannel(nick) == false)
	{
		sendMessage(fd, ERR_NOTONCHANNEL(nick, ch_name), 0);
		return;
	}

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
