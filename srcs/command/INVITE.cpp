#include <Command.hpp>


void INVITE(Client &client, const std::map<std::string, Channel> &channels)
{
	const std::vector<std::string> &params = client.getParams();
	const std::string &nick_name = client.getNickname();
	if (params.size() != 2) {
		sendMessage(client.getFd(), ERR_NEEDMOREPARAMS(nick_name, "INVITE"), 0);
		return;
	}
	else if (findChannel(channels, params[1]) == false) {
		sendMessage(client.getFd(), ERR_NOSUCHCHANNEL(nick_name, params[1]), 0);
	}
	else if (!_rooms[params[1]].isin(nick_name)) {
		sendMessage(client.getFd(), ERR_NOTONCHANNEL(nick_name, params[1]), 0);
	}



	else if (!_rooms[params[1]].is_operator(nick_name))
		user.send_err(ERR_CHANOPRIVSNEEDED(nick_name, params[1]));


	else if (!is_user(params[0]))
		user.send_err(ERR_NOSUCHNICK(nick_name));


	else if (_rooms[params[1]].isin(params[0]))
		user.send_err(ERR_ALREADYREGISTRED(nick_name));

}