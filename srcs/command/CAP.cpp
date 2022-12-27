#include <Command.hpp>

/**
 * @brief allows IRC clients and servers to negotiate new features in a backwards-compatible way
 *
 * CAP LS | CAP END
 */
void CAP(Client &client, std::vector<struct pollfd> &pollfds, std::map<int, Client> &users, std::map<std::string, int> &nick_to_fd) {
	const std::string nick = client.getNickname();
	const int &fd = client.getFd();

	if (client.getParams()[0] == "LS")
		sendMessage(fd, CAP_LS, 0);
	else if (client.getParams()[0] == "END") {
		if (client.getIsAuth() == false) {
			sendMessage(fd, ERR_PASSWDMISMATCH(nick), 0);
			sendMessage(fd, PASS_ERROR(client.getHostname()), 0);
			clearClientInfo(client, pollfds, users, nick_to_fd);
			return;
		}
		sendMessage(fd, RPL_NONE((std::string) "Authenticated ..."), 0);
		sendWelcomeMessage(client);
	}
}
