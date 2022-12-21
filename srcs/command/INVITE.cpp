#include <Command.hpp>

void INVITE(Client &client, const std::map<std::string, Channel> &channels, Server &server)
{
	/* error check part */
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
	if (channel_to_send.is_inChannel(client.getNickname()) == false)) {
		sendMessage(client.getFd(), ERR_NOTONCHANNEL(nick_name, params[1]), 0);
	}
	else if (channel_to_send.getOper() != client.getNickname()){
		sendMessage(client.getFd(), ERR_CHANOPRIVSNEEDED(nick_name, params[1]), 0);
	}
	else if (channel_to_send.is_inChannel(params[0]) == true)
		sendMessage(client.getFd(), ERR_ALREADYREGISTRED(nick_name), 0);
	else if (server.getFd_from_nick(params[0]) == 0)
		sendMessage(client.getFd(), ERR_NOSUCHNICK(nick_name), 0);
	/* no error happen */
	sendMessage(server.getFd_from_nick(params[0]), RPL_INVITING(client.getNickname(), params[1]), 0);
	std::map<int, Client > &tmp_mp_nick_to_fd_ = server.getUsers();
	std::vector<std::string > &new_params = change_fmt_to_join(params);
	JOIN(tmp_mp_nick_to_fd_[server.getFd_from_nick(params[0])], new_params, server.)
}