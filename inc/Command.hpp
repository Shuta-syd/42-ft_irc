#pragma once
#include <Server.hpp>

class Server;
void CAP(Client &client, const std::vector<std::string> &params);
void NICK(Client &client, Server &server);
void USER(Client &client);
void PASS(Client &client, const std::vector<std::string> &params, const std::string &server_password);
void PONG(Client &client, const std::vector<std::string> &params);
void JOIN( std::map<std::string, Channel> &allChannel, Client &client, const std::vector<std::string> &params);

void PRIVMSG(Client &client, Server &server, std::map<std::string, Channel> &channels);
void QUIT(Client &client, Server &server);