#include <Command.hpp>

/**
 * @brief set a connection password
 *
 * PASS <password>
 */
void PASS(Client &client, const std::vector<std::string> &params, const std::string &server_password)
{
	const int &fd = client.getFd();
	const std::string &nick = client.getNickname();
	const std::string &password = params.at(0);

	if (password != server_password)
	{
		// ERR_NEEDMOREPARAMS ERR_ALREADYREGISTERED
		sendMessage(fd, GRN, 0);
		sendMessage(fd, "auth fail\r\n", 0);
		sendMessage(fd, RES, 0);
		return ;
	}
	client.setIsAuth(true);
	sendMessage(fd, PASS_MESSAGE(nick), 0);
}
