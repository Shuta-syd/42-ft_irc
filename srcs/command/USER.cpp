#include <Command.hpp>

/**
 * @brief the beginning of connection to specify the username,
 * hostname, and realname of new user
 *
 * USER <username> <hostname> <servername> <realname>
 *
 * [Note]: <realname> may contain space characters
 */

//#issue8
//refarenceはRFC1459の11pageにある
void USER(Client &client) {
	client.setUsername(client.getParams()[0]);
	//hostnameは設定しない？？
	//hostnameとservernameの両方とも入れる
	client.setRealname(client.getParams()[3]);

	std::cout << YEL << "Username: "<< client.getUsername() << RES << std::endl;
	std::cout << YEL << "Realname: "<< client.getRealname() << RES << std::endl;
}
