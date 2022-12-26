#include <Command.hpp>

/*
 *
 * PART commandは自分がチャンネルから退出するためのもので、
 *  vs
 * KICK commandは他の人をoperatorであるクライアントが特定のチャンネルから退出させるためのコマンド
 * #issue 26
 * @params
 * <channel> [<reason>]
 */

void PART(Client &client, std::map<std::string, Channel> &channels, Server &server) {
	int fd = client.getFd();
	std::string ch_name = client.getParams()[0];
	ch_name.erase(ch_name.begin());
	Channel &channel = channels[ch_name];
	std::string const &my_name = client.getNickname();

	if (client.getParams().size() < 1) {
		sendMessage(fd, ERR_NEEDMOREPARAMS(my_name, "PART"), 0);
	} else if (channel.is_inChannel(my_name) == false) {
		sendMessage(fd, ERR_NOTONCHANNEL(my_name, ch_name), 0);
	} else if (findChannel(channels, ch_name) == false) {
			sendMessage(fd, ERR_NOSUCHCHANNEL(my_name, channel.getName()), 0);
	} else {
		/* messageをclientに送って、userをeraseする処理 */
		std::string reply_message = client.getNickname()
				+ " PART "
				+ ch_name
				+ "\n";
		sendMessage(fd, reply_message, 0);
		int my_fd = server.getFd_from_nick(my_name);
		std::map<int, Client> mp = server.getUsers();
		Client my_account = mp[my_fd];
		channel.eraseMember(my_account);
	}
}
