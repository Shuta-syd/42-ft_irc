#include <Command.hpp>


void INVITE(Client &client, const std::map<std::string, Channel> &channels, std::map<std::string, int> mp_nick_to_fd_)
{
	const std::vector< std::string> &params = client.getParams();
	const std::string &nick_name = client.getNickname();
	if (params.size() != 2) {
		sendMessage(client.getFd(), ERR_NEEDMOREPARAMS(nick_name, "INVITE"), 0);
		return;
	}
	else if (findChannel(channels, params[1]) == false) {
		sendMessage(client.getFd(), ERR_NOSUCHCHANNEL(nick_name, params[1]), 0);
	}
	Channel &channel_to_send = channels[&params[1][0]];
	if (channel_to_send.is_inChannel(client.getNickname() == false)) {
		sendMessage(client.getFd(), ERR_NOTONCHANNEL(nick_name, params[1]), 0);
	}
	else if (channel_to_send.getOper() != client.getNickname()){
		sendMessage(client.getFd(), ERR_CHANOPRIVSNEEDED(nick_name, params[1]), 0);
	}
	else if (channel_to_send.is_inChannel(params[0]) == false)
		sendMessage(client.getFd(), ERR_NOSUCHNICK(nick_name), 0);
	else if (_rooms[params[1]].isin(params[0]))
		sendMessage(client.getFd(), ERR_ALREADYREGISTRED(nick_name));

}