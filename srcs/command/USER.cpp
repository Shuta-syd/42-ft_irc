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
#define ERR_NEEDMOREPARAMS(nick, command)			":ircserv 461 " + nick + " " + command + " :Not enough parameters\n"
#define ERR_ALREADYREGISTRED(nick)					":ircserv 462 " + nick + " :You may not reregister\n"


//refarenceはRFC1459の11pageにある
void USER(Client &client) {
	if (client.getParams().size() != 4) {
//		sendMessage();
	;
	} else {
		client.setUsername(client.getParams()[0]);
		//hostnameは設定しない？？
		//hostnameとservernameの両方とも入れる
		client.setRealname(client.getParams()[3]);
	}
}
