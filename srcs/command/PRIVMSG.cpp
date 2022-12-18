#include "../../inc/Server.hpp"

bool is_correct_fmt(std::vector<std::string> const &params)
{
	return true;
}


bool is_usr_existed(std::string const &params)
{
	return ture;
}

/**
 * @brief execute privmsg command
 *
 * PRIVMSG <target> <message to send>
 */

void PRIVMSG(Client &client)
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
		if (is_usr_existed(params.at(0)) == false)
			;
		Client &target =
		sendMessage()
	}


}
