#include <Command.hpp>

bool validate_msg(Client &client, const std::vector< std::string> &params, const std::string &nick_name, Server &server) {
	if (params.size() != 2) {
		sendMessage(client.getFd(), ERR_NEEDMOREPARAMS(nick_name, "INVITE"), 0);
		return false;
	}
	else if (findChannel(server.getChannels(), params[1]) == false) {
		sendMessage(client.getFd(), ERR_NOSUCHCHANNEL(nick_name, params[1]), 0);
		return false;
	}
	Channel &channel_to_send = server.getChannels()[&params[1][0]];
	if (channel_to_send.is_inChannel(client.getNickname()) == false) {
		sendMessage(client.getFd(), ERR_NOTONCHANNEL(nick_name, params[1]), 0);
		return false;
	}
	else if (channel_to_send.is_operator(client.getNickname()) == false){
		sendMessage(client.getFd(), ERR_CHANOPRIVSNEEDED(nick_name, params[1]), 0);
		return false;
	}
	else if (channel_to_send.is_inChannel(params[0]) == true) {
		sendMessage(client.getFd(), ERR_ALREADYREGISTRED(nick_name), 0);
		return false;
	}
	else if (server.getFd_from_nick(params[0]) == 0) {
		sendMessage(client.getFd(), ERR_NOSUCHNICK(nick_name), 0);
		return false;
	}
	return true;
}

void INVITE(Client &client, const std::map<std::string, Channel> &channels, Server &server)
{
	/* error check part */
	const std::vector< std::string> &params = client.getParams();
	const std::string &nick_name = client.getNickname();
	if (validate_msg(client, params, nick_name, server) == false) {
		return ;
	}
	/* no error happen */
	sendMessage(server.getFd_from_nick(params[0]), RPL_INVITING(client.getNickname(), params[1]), 0);
	std::map<int, Client > &tmp_mp_nick_to_fd_ = server.getUsers();
	// nick  #chennnel
	// #channel
	/* skip params[0] */
	std::vector<std::string >tmp_params = params;
	tmp_params.erase(tmp_params.begin());
	JOIN(tmp_mp_nick_to_fd_[server.getFd_from_nick(params[0])], tmp_params,  server.getChannels());
	// sendMessage(server.getFd_from_nick(params[0]), create_privmsg(tmp_mp_nick_to_fd_[server.getFd_from_nick(params[0])]), 0);
}
