#include <Command.hpp>

/**
 * @brief request to start listening to the specific channel
 *
 * JOIN (<channel> *(',' <channel>) [<key> *(',' <key>)]) / "0"
 *
 * client ex) JOIN #foo,&bar fubar
 * server ex)
 * :shuta!~u@reiuegdfpbf8q.oragono JOIN #test\r\n
 * :testnet.ergo.chat 353 shuta = #test :kylef Palaver shuta apetresc\r\n
 * :testnet.ergo.chat 366 shuta #test :End of NAMES list\r\n
 */
void JOIN(Client &client, const std::vector<std::string> &params)
{
	const int &fd = client.getFd();
	const std::string &nick = client.getNickname();
	const std::string &channels = params.at(0);

	
}
