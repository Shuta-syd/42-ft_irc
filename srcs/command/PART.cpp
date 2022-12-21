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

void drive_out_me_from_channel(std::string const &myname,
							   const Channel& channel,
							   std::map<std::string, Channel> &channels) {
//	/* iteratorがうまく撮れない */
//	std::vector<std::string>::const_iterator itr_begin = channel.getMember().begin();
//	std::vector<std::string>::const_iterator itr_end = channel.getMember().end();
//	for (; itr_begin != itr_end; itr_begin++) {
//		if (*itr_begin == myname) {
			channels.erase(myname);
//		}
//	}
}
void PART(Client &client, std::map<std::string, Channel> &channels) {
	int fd = client.getFd();
	std::string myname = client.getNickname();
	Channel channel = channels[myname];
	if (client.getParams().size() < 1) {
		sendMessage(fd, ERR_NEEDMOREPARAMS(myname, "PART"), 0);
	} else {
		drive_out_me_from_channel(myname, channel, channels);;
	}
}
