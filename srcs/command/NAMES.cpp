#include <Command.hpp>

/**
 * @brief a user can list all nicknames that visible to him.
 *
 * NAMES [<channel> *(',' <channel>) [target]]
 */
void NAME(Client &client, const std::vector<std::string> &params) {
	const std::map<std::string, Channel> &channels = client.getChannels();

	if (params.size() == 0) {
		// send name list to all channel
		for (
			std::map<std::string, Channel>::const_iterator it = channels.begin();
			it != channels.end();
			it++
			)
		{
			
		}

	}
	else if (params.size() == 1 || params.size() == 2) {
		// send names list to selected channels

	}
}
