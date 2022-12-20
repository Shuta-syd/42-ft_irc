#pragma once
#include <Server.hpp>

class Server;
void CAP(Client &client, const std::vector<std::string> &params);
void NICK(Client &client, Server &server);
void USER(Client &client);
void PASS(Client &client, std::string const &server_password);
void PONG(Client &client, const std::vector<std::string> &params);
void JOIN(Client &client, const std::vector<std::string> &params, std::map<std::string, Channel> &allChannel);

void PRIVMSG(Client &client, Server &server, std::map<std::string, Channel> &channels);
std::string create_privmsg(Client const &client);
void QUIT(Client &client, Server &server);
void NAMES(Client &client, const std::vector<std::string> &params, std::map<std::string, Channel> &allChannels);
void KICK(Client &client, std::map<std::string, Channel> channels);
void TOPIC(Client &client, const std::vector<std::string> &params, const std::map<std::string, Channel> &allChannels);
void MODE(Client &client, const std::vector<std::string> &params,std::map<std::string, Channel> &allChannels);
