#include <Command.hpp>
void debug_channel_in_user(Client &client);
void debug_member_in_channel(Channel const &channel);

/**
 * @brief request the forced removal of a user from a channel.
 * KICK <channel> *( "," <channel> ) <user> *( "," <user> ) [<comment>]
 *
 * [NOTE] 複数のチャンネル、ユーザーに対応するようにする。コメントも残せるようにする
 */
void KICK(Client &client, std::map<std::string, Channel> &channels, const std::vector<std::string> &params)
{
	int fd = client.getFd();
	std::string const &nick = client.getNickname();

	if (params.size() < 2) {
		sendMessage(fd, ERR_NEEDMOREPARAMS(nick, "KICK"), 0);
		return;
	}

	std::string ch_name = &params[0][1];
	if (findChannel(channels, ch_name) == false) {
		sendMessage(fd, ERR_NOSUCHCHANNEL(nick, ch_name), 0);
	}

	Channel &channel = channels[ch_name];
	std::string const &frightened_person = params[1];

	if (channel.is_operator(nick) == false) {
		sendMessage(fd, ERR_NOPRIVILEGES(nick), 0);
	} else if (channel.is_inChannel(frightened_person) == false) {
		sendMessage(fd, ERR_NOSUCHNICK(frightened_person), 0);
	} else if (channel.is_inChannel(nick) == false) {
		sendMessage(fd, ERR_NOTONCHANNEL(nick, channel.getName()), 0);
	} else {
		const std::vector<Client>members = channel.getMember();
		for (
				std::vector<Client>::const_iterator it = members.begin();
				it != members.end();
				it++
				) {
			const int targetFd = (*it).getFd();
			const std::string &targetNick = (*it).getNickname();
			sendMessage(targetFd, KICK_MESSAGE(nick, client.getUsername(), client.getHostname(), ch_name, frightened_person), 0);
			if (targetNick == frightened_person)
				channel.eraseMember(*it);
		}
	}
}

void debug_member_in_channel(Channel const &channel) {
	std::cerr << "<<<members in channel>>>\n";
	for (auto member : channel.getMember())
	{
		std::cerr << member.getNickname() << std::endl;
	}
	std::cout << "_____________________________________\n";
}

void debug_channel_in_user(Client &client) {
	std::cerr << "<<<channel joined by the user>>>\n";
	std::cerr << "THE USER : " << client.getNickname() << "\n";
	if (client.getChannels().empty())
	{
		std::cerr << "now this use is not belong to any channel!\n";
		return;
	}
	else
	{
		for (auto ch : client.getChannels())
		{
			std::cerr << ch.first << std::endl;
		}
	}
	std::cout << "_____________________________________\n";
}
