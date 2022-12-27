#include <Command.hpp>
void kickMember(Client &client, std::map<std::string, Channel> &allChannels, const std::string &ch_name, const std::vector<std::string> &targets, const std::string &message);

/**
 * @brief request the forced removal of a user from a channel.
 * KICK <channel> *( "," <channel> ) <user> *( "," <user> ) [<comment>]
 */

void KICK(Client &client, std::map<std::string, Channel> &allChannels, const std::vector<std::string> &params)
{
	int fd = client.getFd();
	std::string const &nick = client.getNickname();
	std::string message = nick;

	if (params.size() < 2) {
		sendMessage(fd, ERR_NEEDMOREPARAMS(nick, "KICK"), 0);
		return;
	}	else if (params.size() == 3)
		message = params[2];

	const std::vector<std::string> channels = splitChannel(params[0]);
	const std::vector<std::string> targets = splitChannel(params[1]);

	for (size_t i = 0; i < channels.size(); i++) {
		const std::string ch_name = &channels[i][1];
		if (findChannelForServer(allChannels, ch_name) == false)
			sendMessage(fd, ERR_NOSUCHCHANNEL(nick, ch_name), 0);
		else
			kickMember(client, allChannels, ch_name, targets, message);
	}
}

void kickMember(
	Client &client,
	std::map<std::string, Channel> &allChannels,
	const std::string &ch_name,
	const std::vector<std::string> &targets,
	const std::string &message
	) {
	int fd = client.getFd();
	std::string const &nick = client.getNickname();
	Channel &channel = allChannels[ch_name];

	if (channel.is_operator(nick) == false)
	{
		sendMessage(fd, ERR_CHANOPRIVSNEEDED(ch_name), 0);
		return ;
	}

	for (size_t i = 0; i < targets.size(); i++)
	{
		std::string const &target = targets[i];
		if (channel.is_inChannel(target) == false)
				sendMessage(fd, ERR_NOSUCHNICK(target), 0);
		else {
				const std::vector<Client *> members = channel.getMember();
				for (
						std::vector<Client *>::const_iterator it = members.begin();
						it != members.end();
						it++)
				{
					const int targetFd = (*it)->getFd();
					const std::string &targetNick = (*it)->getNickname();
					sendMessage(targetFd, KICK_MESSAGE(nick, client.getUsername(), client.getHostname(), ch_name, target, message), 0);
					if (targetNick == target)
					{
						channel.eraseMember(**it);
						if (channel.is_operator(targetNick))
							channel.delOper(targetNick);
					}
				}
		}
	}
}
