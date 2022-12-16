#pragma once
#include <Server.hpp>

void CAP(Client &client, const std::vector<std::string> &params);
void NICK(Client &client, const std::vector<std::string> &params);
void USER(Client &client, const std::vector<std::string> &params);
void PASS(Client &client, const std::vector<std::string> &params, const std::string &server_password);
void PONG(Client &client, const std::vector<std::string> &params);
void JOIN(Client &client, const std::vector<std::string> &params);
