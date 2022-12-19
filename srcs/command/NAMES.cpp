#include <Command.hpp>
const std::vector<std::string> splitChannelForNames(const std::string &param);

/**
 * @brief a user can list all nicknames that visible to him.
 *
 * NAMES [<channel> *(',' <channel>)]
 */
void NAMES(
	Client &client,
	const std::vector<std::string> &params,
	std::map<std::string, Channel> &allChannels
	) {
	const int &fd = client.getFd();
	const std::string &nick = client.getNickname();

	if (params.size() == 0) {} // ?
	else if (params.size() == 1)
	{
		const std::vector<std::string> channelNames = splitChannelForNames(params.at(0));
		for (size_t i = 0; i < channelNames.size(); i++)
		{
			const std::string &channelName = channelNames[i];
			std::cout << RED << channelName << RES << std::endl;
			if (
					(channelName[0] == '&' || channelName[0] == '#'
					|| channelName[0] == '+' || channelName[0] == '!')
					&& findChannel(allChannels, &channelName[1])
				)
			{
				const Channel &channel = allChannels[channelName];
				// const std::string &operName = channel.getOper()->getNickname();
				sendMessage(fd, RPL_NAMREPLY(nick, &channelName[1], "oper"), 0);
				sendMessage(fd, RPL_ENDOFNAMES(nick, &channelName[1]), 0);
			}
			else
				sendMessage(fd, ERR_NOSUCHCHANNEL(nick, channelName), 0);
		}
	}
}


/**
 * @brief Function to split channel names by ','
 */
const std::vector<std::string> splitChannelForNames(const std::string &param)
{
	std::vector<std::string> channels;

	int i = 0;
	while (param[i] && param[i] != '\r' && param[i] != '\n')
	{
		std::string channel;
		for (
				size_t j = i;
				param[j] != ',' && param[j] && param[j] != '\r' && param[j] != '\n';
				j++, i++)
			channel.append(&param[j], 1);
		channels.push_back(channel);
		i++;
	}
	return channels;
}
