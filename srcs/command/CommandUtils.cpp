#include <Command.hpp>
/**
 * A set of generic functions used for command operators
 */

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
					j++, i++)
				channel.append(&param[j], 1);
			channels.push_back(channel);
		}
		else if (param[i] == '0')
		{
			channel.append(&param[i], 1);
			channels.push_back(channel);
		}
		i++;
	}
	return channels;
}
