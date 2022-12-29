#ifndef DEFINE_IRC_BOTREPLY
#define DEFINE_IRC_BOTREPLY

#include <string>
#include <iostream>
#include <sys/socket.h>

/**
 * color code
 */
#define RED "\033[31m"
#define GRN "\033[32m"
#define YEL "\033[33m"
#define BLU "\033[34m"
#define MGN "\033[35m"
#define CYN "\033[36m"
#define RES "\033[m"

#define CAP_MESSAGE "CAP LS\r\n"
#define PASS_MESSAGE(pass) "PASS " + pass + "\r\n"
#define NICK_MESSAGE(nick) "NICK " + nick + "\r\n"
#define USER_MESSAGE(user, host, server, real) "USER " + user + " " + host + " " + server + " :" + real + "\r\n"


void sendMessage(int fd, const std::string &msg, int flag);

#endif
