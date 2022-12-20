#include <Server.hpp>
bool is_correct_fmt(std::vector<std::string> const &params, Client &client) {
	if (params.size() == 0) {
		sendMessage(client.getFd(), ERR_NORECIPIENT(client.getNickname(), client.getCommand()), 0);
		return false;
	}
	else if (params.size() < 2)
	{
		sendMessage(client.getFd(), ERR_NOTEXTTOSEND(client.getNickname()), 0);
		return  false;
	}
	return true;

}



/**
 * @brief execute privmsg command
 *
 * PRIVMSG <target> <message to send>
 */
void PRIVMSG(Client &client, Server &server, std::map<std::string, Channel> &channels)
{
	std::vector<std::string> const &params = client.getParams();
	if  (is_correct_fmt(params, client) == false )
		return ;
	/* check if client sends msg to channnel or not  */
	if (params.at(0)[0] == '#') {

		const Channel &channel_to_send = channels[params[0]];

		/* in the case of "No such a channel" */
		if (channel_to_send.getName().empty()) {

			sendMessage(client.getFd(), ERR_NOTONCHANNEL(client.getNickname(), params[0]), 0);
			std::cout << "No such a channel" << std::endl;
			return ;
		}
		else {

			const std::vector<Client> &members = channel_to_send.getMember();
			for (std::vector<Client>::const_iterator it = members.begin(); it != members.end(); it++) {
				if (it->getNickname() != client.getNickname()) {

					sendMessage(it->getFd(), , 0);
				}

			}
			return ;
		}
	}
	else {
		int fd;
		/* get Target fd but if there is no client that is the same as the Target name, it returns 0  */
		if ((fd = server.getFd_from_nick(params[0]))==0)
		{
			sendMessage(client.getFd(), ERR_NOSUCHNICK(client.getNickname()), 0);
			return ;
		}
		sendMessage(fd, " PRIVMSG " + params[0] + " :" + params[1] + "\n", 0);
	}

}
