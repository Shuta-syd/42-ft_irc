#include <Server.hpp>
void sendPrivmsg(std::string target, std::string message, Client &client, std::map<std::string, Channel> &channels, std::map<std::string, int> mp_nick_to_fd);
bool isCorrectFmt(std::vector<std::string> const &params, Client &client);

/**
 * @brief execute privmsg command
 * PRIVMSG <target> <message to send>
 */

void PRIVMSG(Client &client, std::map<std::string, int> mp_nick_to_fd, std::map<std::string, Channel> &channels) {
	std::string const &nick = client.getNickname();
	std::vector<std::string> const &params = client.getParams();

	if (isCorrectFmt(params, client) == false)
		return;
	const std::vector<std::string> targets = splitBycomma(params[0]);
	const std::string message = params[1];

	for (size_t i = 0; i < targets.size(); i++) {
		sendPrivmsg(targets[i], message, client, channels, mp_nick_to_fd);
	}
}

bool isCorrectFmt(std::vector<std::string> const &params, Client &client) {
	if (params.empty()) {
		sendMessage(client.getFd(), ERR_NEEDMOREPARAMS(client.getNickname(), "PRIVMSG"), 0);
		return false;
	}
	else if (params.size() < 2) {
		sendMessage(client.getFd(), ERR_NOTEXTTOSEND(client.getNickname()), 0);
		return false;
	}
	else {
		return true;
	}
}

void sendPrivmsg(
	std::string target,
	std::string message,
	Client &client,
	std::map<std::string, Channel> &channels,
	std::map<std::string, int> mp_nick_to_fd
	) {
	std::string const &nick = client.getNickname();
		/* check if client sends msg to channel or not  */
	if (target[0] == '#') {
		const std::string channelName = &target[1];
		/* in the case of "No such a channel" */
		if (findChannelForServer(channels, channelName) == false) {
			sendMessage(client.getFd(), ERR_NOTONCHANNEL(client.getNickname(), channelName), 0);
		}
		else {
			const Channel &channel = channels[channelName];
			const std::vector<Client *> &members = channel.getMember();
			for (std::vector<Client *>::const_iterator it = members.begin(); it != members.end(); it++
			) {
				if ((*it)->getNickname() != nick)
					sendMessage((*it)->getFd(), PRIVMSG_MESSAGE(nick, client.getUsername(), client.getHostname(), "#" + channelName, message), 0);
			}
		}
	}
	else {
		int fd;
		const std::string target_nick = target;
		/* get Target fd but if there is no client that is the same as the Target name, it returns 0  */
		if ((fd = mp_nick_to_fd[target_nick]) == 0) {
			sendMessage(client.getFd(), ERR_NOSUCHNICK(client.getNickname(), target_nick), 0);
			return;
		}
		sendMessage(fd, PRIVMSG_MESSAGE(nick, client.getUsername(), client.getHostname(), target_nick, message), 0);
	}
};
