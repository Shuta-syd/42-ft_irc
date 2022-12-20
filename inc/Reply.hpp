#pragma once
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
#define RPL_WELCOME(nick) ":ft_irc 001 " + nick + " :Welcome to the Internet Relay Chat Network, " + nick + "\r\n"
#define RPL_YOURHOST(nick) ":ft_irc 002 " + nick + " :Your host is <server name>, running version <version>\r\n"
#define RPL_CREATED(nick) ":ft_irc 003 " + nick + " :This server was created <date>\r\n"
#define RPL_MYINFO(nick) ":ft_irc 004 " + nick + " :<server name> <version> <available user modes> <available channel modes>\r\n"

/**
 * Command successful Response
 */
#define NICK_MESSAGE(oldNick, newNick) ":" + oldNick + " NICK :"+ newNick + "\r\n"
#define PONG_MESSAGE(serverName) ":ft_irc PONG :" + serverName + "\r\n"
#define JOIN_MESSAGE(nick, channelName) ":" + nick + " JOIN " + channelName + "\r\n"
#define RPL_NONE(message) ":ircserv 300 * :" + message + "\n"


# define ERR_NOSUCHNICK(nick)						":ircserv 401 " + nick + " :No such nick/channel\n"
# define ERR_NORECIPIENT(nick, command)				":ircserv 411 " + nick + " :No recipient given " + command + "\n"
# define ERR_NOTEXTTOSEND(nick)						":ircserv 412 " + nick + " :No text to send\n"

#define RPL_TOPIC(channelName, topic) ":ft_irc 332 " + nick + " #" + channelName + " :" + topic + "\r\n"
#define RPL_NAMREPLY(nick, channelName, operName) ":ft_irc 353 " + nick + " = #" + channelName + " :@" + operName + "\r\n"
#define RPL_ENDOFNAMES(nick, channelName) ":ft_irc 366 " + nick + " #" + channelName + " :End of /NAMES list\r\n"

/**
 * ERROR Response
 */
#define ERR_NOSUCHCHANNEL(nick, channelName) ":ft_irc 403 " + nick + " #" + channelName + " :No such channel\r\n"
#define ERR_TOOMANYCHANNELS(nick, channelName) ":ft_irc 405 " + nick + " #" + channelName + " :Too many channel\r\n"
#define ERR_BADCHANNELKEY(nick, channelName) ":ft_irc 457 " + nick + " #" + channelName + " :Cannot join channel (+k) - bad key\r\n"
#define ERR_NEEDMOREPARAMS(nick, cmdName) ":ft_irc 461 " + nick + " " + cmdName + " :Not enough parameters\r\n"
#define ERR_NOPRIVILEGES(nick) ":ircserv 481 " + nick + " :Permission Denied- You're not an IRC operator\n"
#define ERR_NOTONCHANNEL(nick, channel) ":ircserv 442 " + nick + " " + channel + " :You're not on that channel\n"
