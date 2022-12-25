#include <Server.hpp>

void Server::signal_setup(int signal)
{
	std::map<int, Client>::iterator it = users_.begin();

	for (;it != users_.end(); it++) {
		std::cout << "close:" << it->second.getNickname()<< "[" << it->second.getFd() << "]" << std::endl;
		close(it->first);
	}
	close(master_sd_);
	std::cout << "SERVER HANG UP." << std::endl;
	exit(signal);
}