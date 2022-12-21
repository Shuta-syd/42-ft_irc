#include <Command.hpp>

const std::string getMemberNames(std::vector<Client> members, std::vector<std::string> opers);
bool isChannel(const Client &client, const std::string &channelName);
const std::vector<std::string> splitKeys(const std::string &param, int size);
void enterChannel(std::map<std::string, Channel> &allChannel, Client &client, const std::string &channelName, const std::string &key);

/**
 * @brief request to start listening to the specific channel
 *
 * JOIN (<channel> *(',' <channel>) [<key> *(',' <key>)]) / "0"
 *
 * client ex) JOIN #foo,&bar fubar
 * server ex)
 * :shuta!~u@reiuegdfpbf8q.oragono JOIN #test\r\n
 * :testnet.ergo.chat 353 shuta = #test :kylef Palaver shuta apetresc\r\n
 * :testnet.ergo.chat 366 shuta #test :End of NAMES list\r\n
 */
void JOIN(
		Client &client,
		const std::vector<std::string> &params,
		std::map<std::string, Channel> &allChannel)
{
	const int &fd = client.getFd();
	const std::string &nick = client.getNickname();
	std::vector<std::string> keys;
	std::string keyParam = "";

	if (params.size() < 1)
		sendMessage(fd, ERR_NEEDMOREPARAMS(nick, "JOIN"), 0);
	else if (params.size() == 2)
		keyParam = params.at(1);

	const std::vector<std::string> channels = splitChannel(params.at(0));
	keys = splitKeys(keyParam, channels.size());

	for (size_t i = 0; i < channels.size(); i++)
	{
		if (isChannel(client, channels[i]))
			enterChannel(allChannel, client, &channels[i][1], keys[i]);
	}
}


	/**
	 * @brief channel name is true or false
	 */
bool isChannel(const Client &client, const std::string &channelName)
{
	const int &fd = client.getFd();
	const std::string &nick = client.getNickname();

	if (channelName[0] == '#' || channelName[0] == '&' || channelName[0] == '!' || channelName[0] == '+')
		return true;
	else if (channelName.size() > 50)
	{
		sendMessage(fd, ERR_NOSUCHCHANNEL(nick, channelName), 0);
		return false;
	}
	return true;
}


	/**
	 * @brief Processes password verification and joining a channel
	 *
	 * @param allChannel All channels in server
	 * @param client client to join a channel
	 * @param channelName channel name
	 * @param key channel key to join the channel
	 */
void enterChannel(
		std::map<std::string, Channel> & allChannel,
		Client & client,
		const std::string &channelName,
		const std::string &key)
{
	const int &fd = client.getFd();
	const std::string &nick = client.getNickname();
	Channel &channel = allChannel[channelName];
	const std::string &channelKey = channel.getKey();
	const std::vector<Client> &members = channel.getMember();

	// create new channel
	if (channelName != channel.getName() && (key == channelKey || channelKey == ""))
	{
		channel.setName(channelName);
		channel.setMember(client);
		channel.addOper(nick);
		client.setChannel(channelName, channel);
		sendMessage(fd, JOIN_MESSAGE(nick, channelName), 0);
		sendMessage(fd, RPL_NAMREPLY(nick, channelName, "@" + nick), 0);
		sendMessage(fd, RPL_ENDOFNAMES(nick, channelName), 0);
	}
	else if (key == channelKey || channelKey == "")
	{ // already exist
		channel.setMember(client);
		client.setChannel(channelName, channel);
		const std::string names = getMemberNames(channel.getMember(), channel.getOper());

		for (size_t i = 0; i < members.size(); i++)
				sendMessage(members.at(i).getFd(), JOIN_MESSAGE(nick, channelName), 0);

		if (channel.getTopic() != "")
				sendMessage(fd, RPL_TOPIC(nick, channelName, channel.getTopic()), 0);
		sendMessage(fd, RPL_NAMREPLY(nick, channelName, names), 0);
		sendMessage(fd, RPL_ENDOFNAMES(nick, channelName), 0);
		channelDebug(allChannel, client.getChannels(), channelName);
	}
	else
		sendMessage(fd, ERR_BADCHANNELKEY(nick, channelName), 0);
}

	/**
	 * @brief Function to split key names by ','
	 */
const std::vector<std::string> splitKeys(const std::string &param, int size)
{
	std::vector<std::string> keys;
	int i = 0;

	while (param[i] && param[i] != '\r' && param[i] != '\n')
	{
		std::string key;
		for (
				size_t j = i;
				param[j] != ',' && param[j] && param[j] != '\r' && param[j] != '\n';
				j++, i++)
			key.append(&param[j], 1);
		i++;
		size -= 1;
		keys.push_back(key);
	}

	while (size > 0)
	{
		keys.push_back("");
		size -= 1;
	}

	return keys;
}

/**
 * @brief Get the Oper Names string
 *
 */
const std::string getMemberNames(std::vector<Client>members,std::vector<std::string> opers) {
	std::string names;

	for (size_t i = 0; i < members.size(); i++)
	{
		bool isOper = false;
		const std::string nick = members[i].getNickname();
		for (size_t j = 0; j < opers.size(); j++)
			nick == opers[j] ? isOper = true : isOper;

		if (isOper == false)
			names += nick + " ";
		else
			names += "@" + nick + " ";
	}
	return names;
}
