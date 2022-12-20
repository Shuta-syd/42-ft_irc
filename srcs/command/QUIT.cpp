#include "../../inc/Server.hpp"
#include "../../inc/Reply.hpp"


void clear_client_info(Client &client, Server &server)
{
	std::vector<struct pollfd> &tmp_pollfds = server.get_polldfs();
	for (std::vector<struct pollfd>::iterator it = tmp_pollfds.begin(); it != tmp_pollfds.end(); it++) {
		if (client.getFd() == it->fd)
		{
			tmp_pollfds.erase(it);
			break;
		}
	}
	std::map<int, Client> &tmp_user = server.getUsers();

	std::map<std::string , int > &tmp_nick_to_fd_ = server.getMp_nick_to_fd();
	tmp_user.erase(client.getFd());
	tmp_nick_to_fd_.erase(client.getNickname());

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
