#include <Server.hpp>
bool is_correct_fmt(std::vector<std::string> const &params, Client &client)
{
	if (params.size() == 0) {
		sendMessage(client.getFd(), ERR_NORECIPIENT(client.getNickname(), client.getCommand()), 0);
		throw std::runtime_error(params[0].c_str());
	}



	return true;
}



/**
 * @brief execute privmsg command
 *
 * PRIVMSG <target> <message to send>
 */
void PRIVMSG(Client &client, Server &server)
{
	std::vector<std::string> const &params = client.getParams();
	if (is_correct_fmt(params, client) == false) {
		return;
	}
	/* check if client sends msg to channnel or not  */
	if (params.at(0)[0] == '#') {
		;
	}
	else {
		int fd;
		/* get Target fd but if there is no client that is the same as the Target name, it returns 0  */
		if ((fd = server.getFd_from_nick(params[0]))==0)
		{
			sendMessage(client.getFd(), ERR_NOSUCHNICK(client.getNickname()), 0);
			throw std::runtime_error(params[0].c_str());
		}
		sendMessage(fd, " PRIVMSG " + params[0] + " :" + params[1] + "\n", 0);
	}

}
