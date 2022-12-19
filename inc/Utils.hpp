#pragma once

#include <map>
#include <string>
#include <vector>
#include <Channel.hpp>

int find(const std::string &str, const std::string &target);
bool findChannel(std::map<std::string, Channel> channels, const std::string &target);
const std::vector<std::string> splitChannel(const std::string &param);
std::vector<std::string> split(std::string str, std::string del);
