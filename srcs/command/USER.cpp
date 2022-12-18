#include <Command.hpp>

/**
 * @brief the beginning of connection to specify the username,
 * hostname, and realname of new user
 *
 * USER <username> <hostname> <servername> <realname>
 *
 * [Note]: <realname> may contain space characters
 */
void USER(Client &client, const std::vector<std::string> &params) {
	client.setUsername(params.at(0));
	client.setRealname(params.at(3));

	std::cout << YEL << "Username: "<< client.getUsername() << RES << std::endl;
	std::cout << YEL << "Realname: "<< client.getRealname() << RES << std::endl;
}
