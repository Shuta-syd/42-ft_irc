#pragma once

/**
 * First Connection Response 001 ~ 004
 */
#define RPL_WELCOME(nick) ":ft_irc 001 " + nick + ":Welcome to the Internet Relay Chat Network, " + nick + "\r\n"
#define RPL_YOURHOST(nick) ":ft_irc 002 " + nick + ":Your host is <server name>, running version <version>\r\n"
#define RPL_CREATED(nick) ":ft_irc 003 " + nick + ":This server was created <date>\r\n"
#define RPL_MYINFO(nick) ":ft_irc 004 " + nick + ":<server name> <version> <available user modes> <available channel modes>\r\n"

