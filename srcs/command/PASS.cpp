#include <Command.hpp>

/**
 * @brief set a connection password
 *
 * parameters <password>
 * <in short> [PASS CMD] check whether server should pass the client(user).
 */


#define ERR_NEEDMOREPARAMS(nick) ":ft_irc 461 " + nick + " pass :Not enough parameters\n"
#define ERR_ALREADYREGISTRED(nick)	":ft_irc 462 " + nick + " :You may not reregister\n"
#define RPL_NONE(message) ":ft_irc 300 * :" + message + "\n"
#define ERR_PASSWDMISMATCH(nick) ":ft_irc 464 " + nick + " :Password incorrect\n"

void PASS(Client &client, std::string const &server_password)
{
	int const &fd = client.getFd();
	std::string const &nick = client.getNickname();
	std::string const &password = client.getParams()[0];
	if (client.getParams().size() != 1) {
		sendMessage(fd, ERR_NEEDMOREPARAMS(nick), 0);
		return ;
	}
	if (password != server_password)
	{
		sendAuthfail(client);
	} else {
		client.setIsAuth(true);
	}
}
