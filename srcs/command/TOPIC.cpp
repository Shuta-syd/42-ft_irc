#include <Command.hpp>

/**
 * @brief change or view the topic of a channel
 *
 * TOPIC <channel> [<topic>]
 */
void TOPIC(
		Client &client,
		const std::vector<std::string> &params,
		std::map<std::string, Channel> &allChannels)
{
	bool isOper = false;
	bool isSetTopicAllow = false;
	int fd = client.getFd();
	const std::string &nick = client.getNickname();
	std::map<std::string, Channel*> channels = client.getChannels();

	if (params.size() < 1)
	{
		sendMessage(fd, ERR_NEEDMOREPARAMS(nick, "TOPIC"), 0);
		return;
	}

	const std::string channelName = &params[0][1];
	const bool joinedChannel = findChannel(channels, channelName);
	const bool existChannel = findChannelForServer(allChannels, channelName);

	if (existChannel)
	{
		Channel &channel = allChannels[channelName];
		const std::vector<std::string> operNames = channel.getOper();
		isOper = channel.is_operator(nick);
		isSetTopicAllow = channel.getTopicAllow();
	}

	if (joinedChannel == false && existChannel)
		sendMessage(fd, ERR_NOTJOIN(nick, channelName), 0);
	else if (existChannel == false)
		sendMessage(fd, ERR_NOSUCHCHANNEL(nick, channelName), 0);
	else if (params.size() == 1 && joinedChannel && existChannel)
	{
		// show specific channel topic
		const Channel &channel = allChannels[channelName];
		const std::string topic = channel.getTopic();
		sendMessage(fd, RPL_TOPIC(nick, channelName, topic), 0);
	}
	else if (isOper == false && isSetTopicAllow == false)
		sendMessage(fd, ERR_CHANOPRIVSNEEDED(channelName), 0);
	else
	{ // change topic to specific topic
		const std::string &newTopic = params.at(1);
		Channel &channel = allChannels[channelName];
		channel.setTopic(newTopic);
		const std::vector<Client> members = channel.getMember();
		for (
			std::vector<Client>::const_iterator it = members.begin(); it != members.end(); it++)
		{
			fd = it->getFd();
			sendMessage(fd, SETTOPIC_MESSAGE(nick, client.getUsername(), client.getHostname(), channelName, newTopic), 0);
		}
	}
}
