#pragma once

/**
 * Command Responses
 */
# define RPL_WELCOME(nick) ":ircserv 001 " + nick + ": Welcome to the Internet Relay Chat Network, " + nick
# define RPL_MOTDSTART(nick) ":ircserv 375 " + nick + " :- IRC Message of the day - \n"
# define RPL_ENDOFMOTD(nick) ":ircserv 376 " + nick + " :End of MOTD command\n"
