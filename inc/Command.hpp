#pragma once
#include <Server.hpp>

class Server;
void CAP(Client &client,  Server &server);
void NICK(Client &client, Server &server);
void USER(Client &client);
void PASS(Client &client, std::string const &server_password);
void PONG(Client &client, const std::vector<std::string> &params);
void JOIN(Client &client, const std::vector<std::string> &params, std::map<std::string, Channel> &allChannel);

void PRIVMSG(Client &client, std::map<std::string, int> mp_nick_to_fd, std::map<std::string, Channel> &channels);
void QUIT(Client &client, Server &server, const std::vector<std::string> &params);
void NAMES(Client &client, const std::vector<std::string> &params, std::map<std::string, Channel> &allChannels);
void KICK(Client &client, std::map<std::string, Channel> &channels, Server &server);
void TOPIC(Client &client, const std::vector<std::string> &params, std::map<std::string, Channel> &allChannels);
void MODE(Client &client, const std::vector<std::string> &params,std::map<std::string, Channel> &allChannels);
void INVITE(Client &client, std::map<std::string, int> mp_nick_to_fd, std::map<std::string, Channel> &channels);
void PART(Client &client, std::map<std::string, Channel> &channels);
void debug_member_in_channel(Channel const &channel);
void debug_channel_in_user(Client &client);
