#include "../../inc/Server.hpp"

bool is_correct_fmt(std::vector<std::string> const &params)
{
	return true;
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

}
