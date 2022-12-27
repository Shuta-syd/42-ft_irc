#ifndef DEFINE_IRC_REPLY
#define DEFINE_IRC_REPLY
#include <Server.hpp>
#include <Colors.hpp>

void sendMessage(int fd, const std::string &msg, int flag);
void sendWelcomeMessage(const Client &client);
void sendAuthfail(const Client &client);
void sendERROR(int fd, const std::string &msg, int flag);
/*
 * CAP LS
 */
#define CAP_LS ":ft_irc CAP * LS\r\n"

/**
 * Connection Welcome Message 001 ~ 004
 */
#define RPL_WELCOME(nick) ":ft_irc 001 " + nick + " :Hello! " + nick +" Welcome to the Internet Relay Chat Network \r\n"
#define RPL_YOURHOST(nick) ":ft_irc 002 " + nick + " :Your host is FT_IRC, running version 1.0\r\n"
#define RPL_CREATED(nick) ":ft_irc 003 " + nick + " :This server was created in C++ [Monday, December 26, 2022]\r\n"
#define RPL_MYINFO(nick) ":ft_irc 004 " + nick + " :FT_IRC 1.0 contributes: Shuta Jack Max \r\n"

/**
 * Command successful Response
 */
#define NICK_MESSAGE(oldNick, newNick) ":" + oldNick + " NICK :" + newNick + "\r\n"
#define PONG_MESSAGE(serverName) ":ft_irc PONG :" + serverName + "\r\n"

#define JOIN_MESSAGE(nick, user, host, channelName) ":" + nick + "!" + user + "@" + host + " JOIN #" + channelName + "\r\n"
#define SETTOPIC_MESSAGE(nick, user, host, channelName, topic) ":" + nick + "!" + user + "@" + host + " TOPIC #" + channelName + " :" + topic + "\r\n"
#define RPL_NOTOPIC(nick, channelName) ":ft_irc 331 " + nick + " TOPIC " + channelName + " :No topic set for #" + channelName + "\r\n"
#define MODE_MESSAGE(operNick, user, host, target, channelName, isAllow, mode) ":" + operNick + "!" + user + "@" + host + " MODE #" + channelName + " " + isAllow + mode + " " + target + "\r\n"
#define QUIT_MESSAGE(nick, user, host, msg) ":" + nick + "!" + user + "@" + host + " QUIT :Quit: " + msg + "\r\n"
#define PRIVMSG_MESSAGE(nick, user, host, target, msg) ":" + nick + "!" + user + "@" + host + " PRIVMSG " + target + " :" + msg + "\r\n"
#define INVITE_MESSAGE(nick, user, host, target, channelName) ":" + nick + "!" + user + "@" + host + " INVITE " + target + " #" + channelName + "\r\n"
#define KICK_MESSAGE(nick, user, host, channelName, target, message) ":" + nick + "!" + user + "@" + host + " KICK #" + channelName + " " + target + " " + message + "\r\n"
#define PART_MESSAGE(nick, user, host, channelName, message) ":" + nick + "!" + user + "@" + host + " PART #" + channelName + "" + message + "\r\n"

#define RPL_NONE(message) ":ft_irc 300 * :" + message + "\n"
#define RPL_TOPIC(nick, channelName, topic) ":ft_irc 332 " + nick + " #" + channelName + " :" + topic + "\r\n"
#define RPL_NAMREPLY(nick, channelName, memberNames) ":ft_irc 353 " + nick + " = #" + channelName + " :" + memberNames + "\r\n"
#define RPL_ENDOFNAMES(nick, channelName) ":ft_irc 366 " + nick + " #" + channelName + " :End of /NAMES list\r\n"
#define RPL_INVITING(nick, target, channelName) ":ft_irc 341 " + nick + " " + target + " #" + channelName + "\r\n"
#define RPL_CHANNELMODEIS(nick, channelName, isAllow, mode) ":ft_irc 324 " + nick + " #" + channelName + " " + isAllow + mode + "\r\n"
#define RPL_CREATIONTIME(nick, channelName, nowTime) ":ft_irc 329 " + nick + " #" + channelName + " " + nowTime + "\r\n"

/**
 * ERROR Response
 */
#define ERR_NOSUCHCHANNEL(nick, channelName) ":ft_irc 403 " + nick + " #" + channelName + " :No such channel\r\n"
#define ERR_TOOMANYCHANNELS(nick, channelName) ":ft_irc 405 " + nick + " #" + channelName + " :Too many channel\r\n"
#define ERR_BADCHANNELKEY(nick, channelName) ":ft_irc 457 " + nick + " #" + channelName + " :Cannot join channel (+k) - bad key\r\n"
#define ERR_NEEDMOREPARAMS(nick, cmdName) ":ft_irc 461 " + nick + " " + cmdName + " :Not enough parameters\r\n"
#define ERR_NOPRIVILEGES(nick) ":ft_irc 481 " + nick + " :Permission Denied- You're not an IRC operator\r\n"
#define ERR_NOCHANMODES(nick, mode) ":ft_irc 472 " + nick + " " + mode + " :is an unknown mode character to me\r\n"
#define ERR_CHANOPRIVSNEEDED(channelName) ":ft_irc 482 #" + channelName + " :You're not a channel operator\r\n"
#define ERR_NOSUCHNICK(nick, target) ":ft_irc 401 " + nick + " " + target  + " :No such nick\r\n"
#define ERR_NOTJOIN(nick, channelName) ":ft_irc #" + channelName + " You're not on that channel\r\n"
#define ERR_NOTONCHANNEL(nick, channel) ":ft_irc 442 " + nick + " #" + channel + " :You're not on that channel\r\n"
#define ERR_USERONCHANNEL(nick, target, channelName) ":ft_irc 443 " + nick + " " + target + " #" + channelName + " :User is already on that channel\r\n"
#define ERR_ALREADYREGISTRED(nick) ":ft_irc 462 " + nick + " :You may not reregister\r\n"
#define ERR_CHANNELISFULL(nick, channelName) ":ft_irc 471 " + nick + " #" + channelName + " :Cannot join channel (+l)\r\n"
#define ERR_INVITEONLYCHAN(nick, channelName) ":ft_irc 473 " + nick + " #" + channelName + " :Cannot join channel (+i)\r\n"
#define ERR_NORECIPIENT(nick, command) ":ft_irc 411 " + nick + " :No recipient given " + command + "\r\n"
#define ERR_NOTEXTTOSEND(nick) ":ft_irc 412 " + nick + " :No text to send\r\n"
#define ERR_NONICKNAMEGIVEN ":ft_irc 431 :No nickname given\r\n"
#define ERR_ERRONEUSNICKNAME(nick) ":ft_irc 432 " + nick + " :Error one use nickname\r\n"
#define ERR_NICKNAMEINUSE(nick, target) ":ft_irc 433 " + nick + " " +  target + " :Nickname is already in use\r\n"
#define ERR_PASSWDMISMATCH(nick) ":ft_irc 464 " + nick + " :Password incorrect\r\n"
#define PASS_ERROR(host) "ERROR :Closing Link: " + host + "(Bad Password)\r\n"

#endif
