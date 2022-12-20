#include <Command.hpp>

/**
 * @brief changes which affect either how the client is seen by others or what 'extra'
 * MODE <channel> *(('-'/'+')*<mode> *<modeparams>)
 *
 * '+': allow specified mode
 * '-': disallow specified mode
 */
void MODE(
	Client &client,
	const std::vector<std::string> &params,
	std::map<std::string, Channel> &allChannels
) {
	const int &fd = client.getFd();
	const std::string &nick = client.getNickname();

	if (params.size() < 2)
	{
		sendMessage(fd, ERR_NEEDMOREPARAMS(nick, "MODE"), 0);
		return;
	}

	const std::string &channelName = params.at(0);
	if (findChannel(allChannels, channelName) == false){
		sendMessage(fd, ERR_NOSUCHCHANNEL(nick, channelName), 0);
		return;
	}

	
}
