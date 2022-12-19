#pragma once

#include <map>
#include <string>
#include <Channel.hpp>

int find(const std::string &str, const std::string &target);
bool findChannel(std::map<std::string, Channel> channels, const std::string &target);
