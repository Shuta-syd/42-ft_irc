#include "../../inc/Server.hpp"
#include "../../inc/Reply.hpp"


void clear_client_info(Client &client, Server &server)
{
	std::vector<struct pollfd> &tmp = server.get_polldfs();
	for (std::vector<struct pollfd>::iterator it = tmp.begin(); it != tmp.end(); it++) {
		if (client.getFd() == it->fd)
		{
			tmp.erase(it);
			break;
		}
	}

}
void QUIT(Client &client, Server &server)
{
	/* once  funcs of channel have been created there shoud be more funcs */

	sendMessage(client.getFd(), RPL_NONE((std::string)"You Quit"), 0);

	close(client.getFd());
	std::cout << client.getNickname() <<"lef" << std::endl;

	/* delete info as for this client  */
	clear_client_info(client, server);
}
