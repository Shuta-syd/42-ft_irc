#include <Command.hpp>

/**
 * @brief
 *
 * CAP LS | CAP END
 */
void CAP(Client &client, const std::vector<std::string> &params) {
	const int &fd = client.getFd();

	if (params.at(0) == "LS")
		sendMessage(fd, CAP_LS, 0);
	else if (params.at(0) == "END")
		sendWelcomeMessage(client);
}
