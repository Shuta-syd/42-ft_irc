#include <Command.hpp>

/**
 * @brief
 *
 * CAP LS | CAP END
 */
void CAP(Client &client,  Server &server) {
	const int &fd = client.getFd();

	if (params.at(0) == "LS")
		sendMessage(fd, CAP_LS, 0);
	else if (params.at(0) == "END")
	{
		if (client.getIsAuth() == false)
			QUIT(client, server);
		sendWelcomeMessage(client);
	}

}
