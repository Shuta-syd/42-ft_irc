#include <Command.hpp>
bool isCorrectMode(const char &mode);
void exec_t(const char isAllow, Channel &channel, const Client &client);
void exec_o(const char isAllow, Channel &channel, const Client &client, const std::string &target);
void executeMode(const char isAllow, const char &mode, const std::vector<std::string> &params, Channel &channel, const Client &client);

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
		std::map<std::string, Channel> &allChannels)
{
	const int &fd = client.getFd();
	const std::string &nick = client.getNickname();

	if (params.size() > 0 & params.at(0)[0] != '#')
		return ;
	else if (params.size() == 0)
	{
			sendMessage(fd, ERR_NEEDMOREPARAMS(nick, "MODE"), 0);
			return;
	}

	const std::string &channelName = &params.at(0)[1];
	if (findChannel(allChannels, channelName) == false) {
			sendMessage(fd, ERR_NOSUCHCHANNEL(nick, channelName), 0);
			return;
	}
	Channel &channel = allChannels[channelName];

	if (params.size() == 1) {
			sendMessage(fd, RPL_CHANNELMODEIS(nick, channelName, "+", "nt"), 0);
			sendMessage(fd, RPL_CREATIONTIME(nick, channelName, getTimestamp()), 0);
	}
	else if (params.size() > 1) {
		const char isAllow = params.at(1)[0]; // + or -
		const std::string &mode = &params.at(1)[1];
		for (size_t i = 0; i < mode.size(); i++)
		{
			if (isCorrectMode(mode[i]))
				executeMode(isAllow, mode[i], params, channel, client);
			else
				sendMessage(fd, ERR_NOCHANMODES(nick, mode[i]), 0);
		}
	}
}

/**
 * @brief execute specified mode
 *
 * can execute mode -> o, t, k, l
 */
void executeMode(
	const char isAllow,
	const char &mode,
	const std::vector<std::string> &params,
	Channel &channel,
	const Client &client
	) {
	if (mode == 'o')
		exec_o(isAllow, channel, client, params.at(2));
	else if (mode == 't') {}
	else if (mode == 'k') {}
	else if (mode == 'l') {}
}

/**
 * @brief Judge mode is correct format or wrong
 *
 */
bool isCorrectMode(const char &mode) {
	if (
		mode == 'O' || mode == 'o' || mode == 'v' || mode == 'a' || mode == 'i'
		|| mode == 'm' || mode == 'n' || mode == 'q' || mode == 'p' || mode == 's'
		|| mode == 'r' || mode == 't' || mode == 'k' || mode == 'l' || mode == 'b'
		|| mode == 'e' || mode == 'I'
	)
		return true;
	return false;
}

/**
 * @brief give operator status
 */
void exec_o(
	const char isAllow,
	Channel &channel,
	const Client &client,
	const std::string &target
	) {
	bool isOper = false;
	bool isMember = false;
	const int operFd = client.getFd();
	const std::string nick = client.getNickname();
	const std::vector<std::string> opers = channel.getOper();

	for (size_t i = 0; i < opers.size(); i++)
		opers[i] == nick ? isOper = true : isOper;
	if (isOper == false) {
		sendMessage(operFd, ERR_CHANOPRIVSNEEDED(nick, channel.getName()), 0);
		return;
	}

	const std::vector<Client> members = channel.getMember();
	for (size_t i = 0; i < members.size(); i++)
		members[i].getNickname() == target ? isMember = true : isMember;
	if (isMember == false)
	{
		sendMessage(operFd, ERR_NOSUCHNICK(nick), 0);
		return;
	}

	if (isAllow == '+')
		channel.addOper(target);
	else if (isAllow == '-')
		channel.delOper(target); // SEGV

		for (size_t i = 0; i < members.size(); i++)
			sendMessage(members[i].getFd(), MODE_MESSAGE(nick, client.getUsername(), "host", target, channel.getName(), isAllow, 'o'), 0);
}


/**
 * @brief set topic right is allowed or disallowed
 */
void exec_t(
	const char isAllow,
	Channel &channel,
	const Client &client
) {

}
