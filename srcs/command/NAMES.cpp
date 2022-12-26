#include <Command.hpp>

/**
 * @brief a user can list all nicknames that visible to him.
 *
 * NAMES [<channel> *(',' <channel>)]
 */

#include <string>

void NAMES(Client &client, const std::vector<std::string> &params, std::map<std::string, Channel> &allChannels) {
	const int &fd = client.getFd();
	const std::string &nick = client.getNickname();

	if (params.size() == 1)
	{
		const std::vector<std::string> channelNames = splitChannel(params.at(0));
		for (size_t i = 0; i < channelNames.size(); i++)
		{
			const std::string &channelName = channelNames[i];
			std::cout << RED << channelName << RES << std::endl;
			std::string specific_chars("&#+!");
			if (
					(specific_chars.find_first_not_of(channelName[0]) != std::string::npos)
					&& findChannel(allChannels, &channelName[1])
				)
			{
				sendMessage(fd, RPL_NAMREPLY(nick, &channelName[1], "oper"), 0);
				sendMessage(fd, RPL_ENDOFNAMES(nick, &channelName[1]), 0);
			}
			else
				sendMessage(fd, ERR_NOSUCHCHANNEL(nick, channelName), 0);
		}
	}
}
