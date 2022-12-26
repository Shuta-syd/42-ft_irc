#include <Server.hpp>
#include <stdlib.h>

Server *server;
void terminate(int signal)
{
	std::map<int, Client>::iterator it = server->getUsers().begin();

	for (;it != server->getUsers().end(); it++) {
		std::cout << "close:" << it->second.getNickname()<< "[" << it->second.getFd() << "]" << std::endl;
		close(it->first);
	}
	close(server->getMstersd());
	std::cout << "SERVER HANG UP." << std::endl;
	std::exit(signal);


}

void signal_handler(int signal)
{
	terminate(signal);
}


int main(int argc, char const *argv[])
{


	if (argc == 3)
	{
		int port = atoi(argv[1]);
		std::string password(argv[2]);

		Server Irc(port, password);

		server = &Irc;
		try	{
			Irc.start();
		} catch (const std::exception &e) {
			std::cout << "ERROR:" << e.what() << std::endl;
			terminate(1);
		}
	}
	else
	{
		std::cerr << "[Usage] ./ircserv [Port] [Password]" << std::endl;
		return 1;
	}
	return 0;
}
