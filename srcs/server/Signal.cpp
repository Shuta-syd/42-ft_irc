#include <Server.hpp>

void Server::signal_handler(int signal)
{
	std::map<int, Client>::iterator it = users_.begin();


	for (;it != users_.end(); it++) {
		std::cout << "close:" << it->second.getNickname()<< "[" << it->second.getFd() << "]" << std::endl;
		FD_CLR(it->second.getFd(), master_sd_);
		close(it->first);
	}
	close(master_sd_);
	std::cout << "SERVER HANG UP." << std::endl;
	exit(signal);
}

void Server::signal_setup(int signal)
{

	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	signal(SIGPIPE, SIG_IGN);
}