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
 * @param target (does not include #)
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

std::vector<std::string> split(std::string str, std::string del) {
	uint64_t first = 0;
	uint64_t last = str.find_first_of(del);
	std::vector<std::string> res;
	if (last == std::string::npos) {
		res.push_back(str);
		return res;
	}
	while (first < str.size()) {
		std::string trim_str(str, first, last - first);
		res.push_back(trim_str);
		first = last + 1;
		last = str.find_first_of(del, first);
		if (last == std::string::npos) {
			last = str.size();
		}
	}
	return res;
}
