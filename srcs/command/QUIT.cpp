#include <Command.hpp>

/**
 * @brief a client session is terminated with a quit message
 *
 * QUIT [<Quit Message>]
 */
void QUIT(
	Client &client,
	std::vector<struct pollfd> &pollfds,
	std::map<int, Client> &users,
	std::map<std::string, int> &nick_to_fd,
	const std::vector<std::string> &params
	) {
	/* once  funcs of channel have been created there should be more funcs */
	const std::string nick = client.getNickname();
	const int &clientFd = client.getFd();
	std::string quitMessage = "leaving";

	if (!params.empty())
		quitMessage = params[0];

	if (client.getChannels().empty() == false)
	{
		std::map<std::string, Channel*> &channels = client.getChannels();
		std::cout << 4 << std::endl;
		for (
				std::map<std::string, Channel*>::iterator it = channels.begin();
				it != channels.end();
				it++
				) {
			const std::vector<Client *> &members = it->second->getMember();
			for (
					std::vector<Client *>::const_iterator mem_it = members.begin();
					mem_it != members.end();
					mem_it++
					) {
				const int memFd = (*mem_it)->getFd();
				if (memFd == clientFd)
					it->second->eraseMember(client);
				else
				{
					sendMessage(memFd, QUIT_MESSAGE(nick, client.getUsername(), client.getHostname(), quitMessage), 0);
					std::cout << 10 << std::endl;
				}
			}
		}
	}
	/* delete info as for this client  */
	clearClientInfo(client, pollfds, users, nick_to_fd);
	std::cout << RED << nick << " LEAVE" << RES << std::endl;
}

void clearClientInfo(
	Client &client,
	std::vector<struct pollfd> &pollfds,
	std::map<int, Client> &users,
	std::map<std::string, int> &nick_to_fd
	) {
	for (std::vector<struct pollfd>::iterator it = pollfds.begin(); it != pollfds.end(); it++)
	{
		if (client.getFd() == it->fd)
		{
			pollfds.erase(it);
			break;
		}
	}
	users.erase(client.getFd());
	nick_to_fd.erase(client.getNickname());
	close(client.getFd());
}
