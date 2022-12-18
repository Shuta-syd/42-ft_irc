#pragma once
#include <Server.hpp>
#include <Colors.hpp>

void sendMessage(int fd, const std::string &msg, int flag);
void sendWelcomeMessage(const Client &client);
void sendAuthfail(const Client &client);

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
#define NICK_MESSAGE(oldNick, newNic) ":" + oldNick + " NICK :"+ newNick + "\r\n"
#define PONG_MESSAGE(serverName) ":ft_irc PONG :" + serverName + "\r\n"
#define JOIN_MESSAGE(nick, channelName) ":" + nick + " JOIN #" + channelName + "\r\n"
#define RPL_TOPIC(channelName, topic) ":ft_irc 332 " + nick + " #" + channelName + " :" + topic + "\r\n"
#define RPL_NAMREPLY(nick, channelName) ":ft_irc 353 " + nick + " = #" + channelName + " :@" + nick + "\r\n"
#define RPL_ENDOFNAMES(nick, channelName) ":ft_irc 366 " + nick + " " + channelName + " :End of /NAMES list\r\n"
