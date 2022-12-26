#include <Command.hpp>

/**
 * @brief set a connection password
 *
 * parameters <password>
 * <in short> [PASS CMD] check whether server should pass the client(user).
 */

void PASS(Client &client, std::string const &server_password){
	int const &fd = client.getFd();
	std::string const &nick = client.getNickname();
	std::string const &password = client.getParams()[0];


	//defaultでshould_be_capをfalseにしておいて、
	//Errorでない時に、trueにする仕様にした
	client.should_be_cap_pass = false;
	if (client.getParams().size() != 1) {
		sendMessage(fd, ERR_NEEDMOREPARAMS(nick, "PASS"), 0);
	} else if (password != server_password) {
		sendMessage(fd, ERR_PASSWDMISMATCH(nick), 0);
	} else {
		client.should_be_cap_pass = true;
		sendMessage(fd, RPL_NONE((std::string)"Authenticated ..."), 0);
	}
}
