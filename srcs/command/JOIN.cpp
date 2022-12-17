#include <Command.hpp>
const std::vector<std::string> splitChannel(const std::string &param);
const std::vector<std::string> splitKeys(const std::string &param);

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
void JOIN(Client &client, const std::vector<std::string> &params)
{
	const int &fd = client.getFd();
	const std::string &nick = client.getNickname();
	std::vector<std::string> keys;

	if (params.size() < 1 || params.size() > 2) // error
		sendMessage(fd, "ERROR\r\n", 0);
	else if (params.size() == 2) // there is keys
		keys = splitKeys(params.at(1));

	const std::vector<std::string> channels = splitChannel(params.at(0));
}

/**
 * @brief Function to split channel names by ','
 */
const std::vector<std::string> splitChannel(const std::string &param) {
	std::vector<std::string> channels;

	int i = 0;
	while (param[i] && param[i] != '\r' && param[i] != '\n')
	{
		std::string channel;
		if (param[i] == '&' || param[i] == '#' || param[i] == '+' || param[i] == '!')
		{
			for (
				size_t j = i + 1;
				param[j] != ',' && param[j] && param[j] != '\r' && param[j] != '\n';
				j++, i++
			 )
				channel.append(&param[j], 1);
			channels.push_back(channel);
		}
		i++;
	}
	return channels;
}

/**
 * @brief Function to split key names by ','
 */
const std::vector<std::string> splitKeys(const std::string &param) {
	
}
