#include <Command.hpp>

/**
 * @brief set a connection password
 *
 * parameters <password>
 * <in short> [PASS CMD] check whether server should pass the client(user).
 */
//#issue 10

#define ERR_NEEDMOREPARAMS(nick) ":ft_irc 461 " + nick + " pass :Not enough parameters\n"
#define ERR_ALREADYREGISTRED(nick)	":ft_irc 462 " + nick + " :You may not register the password same as other person!\n"
#define RPL_NONE(message) ":ft_irc 300 * :" + message + "\n"
#define ERR_PASSWDMISMATCH(nick) ":ft_irc 464 " + nick + " :Password incorrect\n"

void PASS(Client &client, std::string const &server_password)
{
	int const &fd = client.getFd();
	std::string const &nick = client.getNickname();
	std::string const &password = client.getParams()[0];


	/******* Error handling ********/
	if (client.getParams().size() != 1) {
		sendMessage(fd, ERR_NEEDMOREPARAMS(nick), 0);
	} else if (client.getIsAuth() == true) {
		sendMessage(fd, ERR_ALREADYREGISTRED(nick), 0);
	} else if (password != server_password) {
		sendMessage(fd, ERR_PASSWDMISMATCH(nick), 0);
	/*********************************/
	} else {
		client.setIsAuth(true);
		std::cout << "[PASS Success!]" << " ";
		sendMessage(fd, RPL_NONE((std::string)"Authenticated ..."), 0);
	}
}
