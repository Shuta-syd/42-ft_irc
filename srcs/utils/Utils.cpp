#include <Utils.hpp>
#include <iostream>

/**
 * @brief find target from str
 *
 * @param str
 * @param target
 * @return int index
 */
int find(const std::string &str, const std::string &target) {
	size_t i = 0;
	size_t j = 0;

	while (str[i])
	{
		j = 0;
		if (str[i] == target.at(0))
		{
			while (str[i] && target[j] && str[i] == target[j])
			{
				i++;
				j++;
			}
			if (j == target.size())
				return i - (target.size() - 1);
		}
		else
			i++;
	}
	return -1;
}

/**
 * @brief
 */
bool findChannel(std::map<std::string, Channel>channels, const std::string &target) {
	for (
			std::map<std::string, Channel>::const_iterator it = channels.begin();
			it != channels.end();
			it++
			)
	{
		const std::string &channelName = (*it).first;
		std::cout << channelName << std::endl;
		if (channelName == target)
			return true;
	}
	return false;
}

/**
 * @brief Function to split channel names by ','
 */
const std::vector<std::string> splitChannel(const std::string &param)
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
