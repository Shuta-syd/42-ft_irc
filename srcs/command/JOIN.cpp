#include <Command.hpp>
const std::vector<std::string> splitChannel(const std::string &param);
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
		std::map<std::string, Channel> &allChannel,
		Client &client,
		const std::vector<std::string> &params)
{
	const int &fd = client.getFd();
	const std::string &nick = client.getNickname();
	std::vector<std::string> keys;
	std::string keyParam = "";

	if (params.size() < 1 || params.size() > 2) // error
		sendMessage(fd, "ERROR\r\n", 0);
	else if (params.size() == 2)
		keyParam = params.at(1);

	const std::vector<std::string> channels = splitChannel(params.at(0));
	keys = splitKeys(keyParam, channels.size());

	for (size_t i = 0; i < channels.size(); i++) // 0対応必要
		enterChannel(allChannel ,client, channels[i], keys[i]);
}

/**
 * @brief Processes password verification and joining a channel
 *
 * @param allChannel
 * @param client
 * @param channelName
 * @param key
 */
void enterChannel(
	std::map<std::string, Channel> &allChannel,
	Client &client,
	const std::string &channelName,
	const std::string &key
){
	const int &fd = client.getFd();
	const std::string &nick = client.getNickname();
	Channel &channel= allChannel[channelName];
	const std::string &channelKey = channel.getKey();
	const std::vector<Client> &members = channel.getMember();

	if (channelName == "0") {

	}
	// create new channel
	else if (channelName != channel.getName() && (key == channelKey || channelKey == "")) {
		channel.setName(channelName);
		channel.setMember(client);
		client.setChannel(channelName, channel);
		sendMessage(fd, JOIN_MESSAGE(nick, channelName), 0);
		//sendMessage(fd, MODE_MESSAGE(channelName, "+nt"), 0);
		// sendMessage(fd, RPL_NAMREPLY(nick, channelName), 0);
		// sendMessage(fd, RPL_ENDOFNAMES(nick, channelName), 0);
	}
	else if (key == channelKey || channelKey == "") { // already exist
		channel.setMember(client);
		client.setChannel(channelName, channel);
		std::cout << MGN << "channel already exist. JOIN [" << channelName << "]" << RES << std::endl;
		for (size_t i = 0; i < members.size(); i++) {
			const int &fd = members.at(i).getFd();
			sendMessage(fd, JOIN_MESSAGE(nick, channelName), 0);
			sendMessage(fd, RPL_TOPIC(channelName, "TOPIC TEST"), 0);
			// sendMessage(fd, RPL_NAMREPLY(nick, channelName), 0);
			// sendMessage(fd, RPL_ENDOFNAMES(nick, channelName), 0);
		}
	}
	else { // ERROR
		std::cout << MGN << "ERROR ZONE" << RES << std::endl;
	}
}


/**
 * @brief Function to split key names by ','
 */
const std::vector<std::string> splitKeys(const std::string &param, int size) {
	std::vector<std::string> keys;

	int i = 0;
	while (param[i] && param[i] != '\r' && param[i] != '\n') {
		std::string key;
			for (
					size_t j = i;
					param[j] != ',' && param[j] && param[j] != '\r' && param[j] != '\n';
					j++, i++
					)
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
