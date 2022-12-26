#include <Command.hpp>

/**
 * @brief allows IRC clients and servers to negotiate new features in a backwards-compatible way
 *
 * CAP LS | CAP END
 */
void CAP(Client &client) {
	const int &fd = client.getFd();

	if (client.getParams().at(0) == "LS")
		sendMessage(fd, CAP_LS, 0);
	else if (client.getParams()[0] == "END")
	{
		if (client.should_be_cap == false) {
			QUIT(client, server, {});
			return ;
		}
		sendWelcomeMessage(client);
}
