#pragma once
#include <Server.hpp>

void NICK(Client &client, const std::vector<std::string> &params);
void CAP(Client &client, const std::vector<std::string> &params);
