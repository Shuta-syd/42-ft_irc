#ifndef DEFINE_IRC_UTILS
#define DEFINE_IRC_UTILS

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <ctime>
#include <Channel.hpp>
#include <Colors.hpp>

int find(const std::string &str, const std::string &target);
bool findChannel(std::map<std::string, Channel> channels, const std::string &target);
const std::vector<std::string> splitChannel(const std::string &param);
std::vector<std::string> split(std::string str, std::string del);
void channelDebug(std::map<std::string, Channel> server, std::map<std::string, Channel> client, std::string channelName);
std::string getTimestamp();
bool is_number(const std::string &s);

#endif
