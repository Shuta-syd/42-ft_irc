#include "../../inc/Server.hpp"

bool is_correct_fmt(std::vector<std::string> const &params)
{
	return true;
}


int get_Targetfd(std::string const &target, std::map<int, Client> const users)
{
	int ret = 0;

	std::map<int, Client>::const_iterator = users.begin();

	return ret;
}

/**
 * @brief execute privmsg command
 *
 * PRIVMSG <target> <message to send>
 */

void PRIVMSG(Client &client, Server &server)
{
	std::vector<std::string> const &params = client.getParams();
	if (is_correct_fmt(params) == false) {
		return;
	}
	/* check if client sends msg to channnel or not  */
	if (params.at(0)[0] == '#') {
		;
	}
	else {
		int fd;
		/* get Target fd but if there is no client that is the same as the Target name, it returns 0  */
		if ((fd = )==0)
			return ;

		sendMessage(fd, " PRIVMSG " + params[0] + " :" + params[1] + "\n", 0)
	}


}
