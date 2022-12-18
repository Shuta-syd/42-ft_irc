#pragma once
#include <Server.hpp>

void CAP(Client &client, const std::vector<std::string> &params);
void NICK(Client &client, const std::vector<std::string> &params);
void USER(Client &client, const std::vector<std::string> &params);
void PASS(Client &client, const std::vector<std::string> &params, const std::string &server_password);
void PONG(Client &client, const std::vector<std::string> &params);
void JOIN( std::map<std::string, Channel> &allChannel, Client &client, const std::vector<std::string> &params);

/**
 * A set of generic functions used for command operators
 */
const std::vector<std::string> splitChannel(const std::string &param);
