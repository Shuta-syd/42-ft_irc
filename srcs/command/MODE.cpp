#include <Command.hpp>
bool isCorrectMode(const char &mode);
bool isOper(Channel channel, Client client);
bool isMember(Channel channel, Client client, std::string targetName);
void exec_l(const char isAllow, Channel &channel, const Client &client, const std::vector<std::string> &params);
void exec_t(const char isAllow, Channel &channel, const Client &client);
void exec_k(const char isAllow, Channel &channel, const Client &client, const std::vector<std::string> &params);
void exec_o(const char isAllow, Channel &channel, const Client &client, const std::vector<std::string> &params);
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
			channel.setCreatedTime(getTimestamp());
			sendMessage(
					fd,
					RPL_CHANNELMODEIS(nick, channel.getName(), "+", channel.getMode() + " " + channel.getKey())
					+RPL_CREATIONTIME(nick, channel.getName(), channel.getCreatedTime()),
					0);
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
		exec_o(isAllow, channel, client, params);
	else if (mode == 't')
		exec_t(isAllow, channel, client);
	else if (mode == 'k')
		exec_k(isAllow, channel, client, params);
	else if (mode == 'l')
		exec_l(isAllow, channel, client, params);
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
	const std::vector<std::string> &params
	) {
	std::string target;
	const int clientFd = client.getFd();
	const std::vector<Client> members = channel.getMember();
	const std::string channelName = channel.getName();
	const std::string nick = client.getNickname();
	const std::vector<std::string> opers = channel.getOper();

	 if (isOper(channel, client) == false)
		return;
	else if (params.size() < 3)
	{
		sendMessage(
				clientFd,
				RPL_CHANNELMODEIS(nick, channel.getName(), "+", channel.getMode() + " " + channel.getKey())
				+ RPL_CREATIONTIME(nick, channel.getName(), channel.getCreatedTime()),
				0);
		return;
	}

	if (isAllow == '+')
	{
		channel.addOper(params.at(2));
		channel.addMode('o');
	}
	else if (isAllow == '-')
	{
		channel.delOper(params.at(2));
		channel.delMode('-');
	}

		for (size_t i = 0; i < members.size(); i++)
			sendMessage(members[i].getFd(), MODE_MESSAGE(nick, client.getUsername(), client.getHostname(), target, channel.getName(), isAllow, 'o'), 0);
}


/**
 * @brief set topic right is allowed or disallowed
 */
void exec_t(
	const char isAllow,
	Channel &channel,
	const Client &client
) {
	const std::string nick = client.getNickname();
	const std::vector<Client> members = channel.getMember();

	if (isOper(channel, client) == false)
		return;
	if (isAllow == '+')
	{
		channel.setTopicAllow(false);
		channel.addMode('t');
	}
	else if (isAllow == '-')
	{
		channel.setTopicAllow(true);
		channel.delMode('t');
	}
	for (size_t i = 0; i < members.size(); i++)
		sendMessage(members[i].getFd(), MODE_MESSAGE(nick, client.getUsername(), client.getHostname(), "", channel.getName(), isAllow, 't'), 0);
}

/**
 * @brief set password or not
 *
 */
void exec_k(
	const char isAllow,
	Channel &channel,
	const Client &client,
	const std::vector<std::string> &params
) {
	int fd = client.getFd();
	const std::string nick = client.getNickname();
	const std::vector<Client> members = channel.getMember();

	if (isOper(channel, client) == false)
		return;
	else if (params.size() < 3 && isAllow == '-')
	{
		sendMessage(
			fd,
			RPL_CHANNELMODEIS(nick, channel.getName(), "+", channel.getMode() + " " + channel.getKey())
			+ RPL_CREATIONTIME(nick, channel.getName(), channel.getCreatedTime()),
		 0);
		return;
	}

	if (isAllow == '+' && params.size() > 2)
	{
		channel.setKey(params.at(2));
		channel.addMode('k');
	}
	else if (isAllow == '-')
	{
		channel.setKey("");
		channel.delMode('k');
	}
	for (size_t i = 0; i < members.size(); i++)
		sendMessage(members[i].getFd(), MODE_MESSAGE(nick, client.getUsername(), client.getHostname(), channel.getKey(), channel.getName(), isAllow, 'k'), 0);
}


/**
 * @brief set max members on the channel
 *
 */
void exec_l(
	const char isAllow,
	Channel &channel,
	const Client &client,
	const std::vector<std::string> &params
) {
	std::string maxMember;
	int fd = client.getFd();
	const std::string nick = client.getNickname();
	const std::vector<Client> members = channel.getMember();

	if (isOper(channel, client) == false)
		return;
	else if (params.size() < 3 && isAllow != '-' && is_number(params.at(2)) == false)
	{
		sendMessage(
				fd,
				RPL_CHANNELMODEIS(nick, channel.getName(), "+", channel.getMode() + " " + channel.getKey())
				+ RPL_CREATIONTIME(nick, channel.getName(), channel.getCreatedTime()),
				0);
		return;
	}

	if (isAllow == '+' && params.size() > 2)
	{
		channel.setMaxMember(std::stoi(params.at(2)));
		maxMember = params.at(2);
		channel.addMode('l');
	}
	else if (isAllow == '-')
	{
		channel.setMaxMember(-1);
		channel.delMode('l');
	}
	for (size_t i = 0; i < members.size(); i++)
		sendMessage(members[i].getFd(), MODE_MESSAGE(nick, client.getUsername(), client.getHostname(), "", channel.getName(), isAllow, "l " + maxMember), 0);
}


/**
 * @brief client is operator or not
 */
bool isOper(Channel channel, Client client) {
		bool isOper = false;
		const int clientFd = client.getFd();
		const std::string nick = client.getNickname();
		const std::vector<std::string> opers = channel.getOper();

		for (size_t i = 0; i < opers.size(); i++)
			opers[i] == nick ? isOper = true : isOper;
		if (isOper == false)
			sendMessage(clientFd, ERR_CHANOPRIVSNEEDED(nick, channel.getName()), 0);
		return isOper;
}

/**
 * @brief targetName is channel member or not
 */
bool isMember(Channel channel, Client client, std::string targetName) {
	bool isMember = false;
	const int clientFd = client.getFd();
	const std::string channelName = channel.getName();
	const std::string nick = client.getNickname();

	const std::vector<Client> members = channel.getMember();
	for (size_t i = 0; i < members.size(); i++)
		members[i].getNickname() == targetName ? isMember = true : isMember;
	if (isMember == false)
		sendMessage(clientFd, ERR_NOSUCHNICK(targetName), 0);
	return isMember;
}
