#include <Bot.hpp>

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
		if (str[i] == target[0]) {
			while (str[i] && target[j] && str[i] == target[j]) {
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
