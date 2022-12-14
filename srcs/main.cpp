#include <Server.hpp>
#include <stdlib.h>

int main(int argc, char const *argv[])
{

	if (argc == 3)
	{
		int port = atoi(argv[1]);
		std::string password(argv[2]);

		Server Irc(port, password);
		Irc.start();
	}
	else
	{
		std::cerr << "[Usage] ./ircserv [Port] [Password]" << std::endl;
		return 1;
	}
	return 0;
}
