#include <Command.hpp>

/**
 * @brief change or view the topic of a channel
 *
 * TOPIC <channel> [<topic>]
 */
void TOPIC(
	Client &client,
	const std::vector<std::string> &params,
	std::map<std::string, Channel> &allChannels
	) {
	bool isOper = false;
	const int &fd = client.getFd();
	const std::string &nick = client.getNickname();
	std::map<std::string, Channel> channels = client.getChannels();

	if (params.size() < 1)
	{
		sendMessage(fd, ERR_NEEDMOREPARAMS(nick, "TOPIC"), 0);
		return ;
	}

	const std::string channelName = &params.at(0)[1];
	const bool joinedChannel = findChannel(channels, channelName);
	const bool existChannel = findChannel(allChannels, channelName);

	if (existChannel) {
		const Channel &channel = allChannels[channelName];
		const std::vector<std::string> operNames = channel.getOper();
		for (size_t i = 0; i < operNames.size(); i++)
			operNames[i] == nick ? isOper = true : isOper;
	}

	if (isOper == false)
		sendMessage(fd, ERR_CHANOPRIVSNEEDED(nick, channelName), 0);
	else if (params.size() == 1 && joinedChannel && existChannel) {
		// show specific channel topic
		const Channel &channel = channels[channelName];
		const std::string topic = channel.getTopic();
		sendMessage(fd, RPL_TOPIC(nick, channelName, topic), 0);
	}
	else if (joinedChannel == false && existChannel)
		sendMessage(fd, ERR_NOTJOIN(nick, channelName), 0);
	else if (existChannel == false)
		sendMessage(fd, ERR_NOSUCHCHANNEL(nick, channelName), 0);
	else { // change topic to specific topic
		const std::string &newTopic = params.at(1);
		Channel &channel = allChannels[channelName];
		channel.setTopic(newTopic);
		sendMessage(fd, SETTOPIC_MESSAGE(nick, client.getUsername(), "host", channelName, newTopic), 0);
		channelDebug(allChannels, channels, channelName);
	}
}
