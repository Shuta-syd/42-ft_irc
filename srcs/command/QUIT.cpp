#include <Server.hpp>
void clearClientInfo(Client &client, Server &server);

/**
 * @brief a client session is terminated with a quit message
 *
 * QUIT [<Quit Message>]
 */
void QUIT(Client &client, Server &server, const std::vector<std::string> &params)
{
	/* once  funcs of channel have been created there should be more funcs */
	const std::string nick = client.getNickname();
	const int &clientFd = client.getFd();
	std::string quitMessage = "leaving";

	if (params.size() > 0)
		quitMessage = params.at(0);

	if (client.getChannels().empty() != true)
	{
		std::map<std::string, Channel> &channels = client.getChannels();
		for (
				std::map<std::string, Channel>::iterator it = channels.begin();
				it != channels.end();
				it++)
		{
			const std::vector<Client> &members = it->second.getMember();
			for (
					std::vector<Client>::const_iterator mem_it = members.begin();
					mem_it != members.end();
					mem_it++)
			{
				const int memFd = (*mem_it).getFd();
				if (memFd == clientFd)
					(*it).second.eraseMember(client);
				else
					sendMessage(memFd, QUIT_MESSAGE(nick, client.getUsername(), client.getHostname(), quitMessage), 0);
			}
		}
	}
	/* delete info as for this client  */
	clearClientInfo(client, server);
	std::cout << RED << nick << " LEAVE" << RES << std::endl;
}

void clearClientInfo(Client &client, Server &server)
{
	std::vector<struct pollfd> &pollfds = server.get_polldfs();
	for (std::vector<struct pollfd>::iterator it = pollfds.begin(); it != pollfds.end(); it++)
	{
		if (client.getFd() == it->fd)
		{
			pollfds.erase(it);
			break;
		}
	}
	std::map<int, Client> &user = server.getUsers();

	std::map<std::string, int> &nick_to_fd = server.getMp_nick_to_fd();
	user.erase(client.getFd());
	nick_to_fd.erase(client.getNickname());
	close(client.getFd());
}
