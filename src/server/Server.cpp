#include <Server.hpp>

Server::Server() {}

Server::Server(int port, std::string password): port_(port), password_(password) {}

Server::~Server() {}

/**
 *@brief 
*/
void Server::start() {
	this->setupSocket();
}

/**
 * @brief to set up a server socket
 */
void Server::setupSocket() {
	int enable = 1;

	/* server socket create */
	this->master_sd_ = socket(AF_INET, SOCK_STREAM, 0);
	if (this->master_sd_ < 0)
	{
		std::cerr << "socket error" << std::endl;
		exit(EXIT_FAILURE);
	}

	/* set socket option to server socket */
	if (setsockopt(this->master_sd_, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable)) < 0)
	{
		std::cerr << "setsockopt error" << std::endl;
		close(this->master_sd_);
		exit(EXIT_FAILURE);
	}

	/* Change server socket fd from blocking IO to non-blocking IO*/
	if (fcntl(this->master_sd_, O_NONBLOCK, &enable))
	{
		std::cerr << "fcntl O_NONBLOCK error" << std::endl;
		close(this->master_sd_);
		exit(EXIT_FAILURE);
	}

	/* create address for server socket fd */
	struct sockaddr_in addr;
	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(port_);

	/* bind address to server socket fd*/
	if (bind(this->master_sd_, (struct sockaddr*)&addr, sizeof(addr)) < 0)
	{
		std::cerr << "bind error" << std::endl;
		close(this->master_sd_);
		exit(EXIT_FAILURE);
	}

	/* try to specify maximum of SOCKET_MAX pending connections for the server socket */
	if (listen(this->master_sd_, BACKLOG) < 0)
	{
		std::cerr << "listen error" << std::endl;
		exit(EXIT_FAILURE);
	}
}
