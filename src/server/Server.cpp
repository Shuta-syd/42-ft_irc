#include <Server.hpp>

Server::Server() {}

Server::Server(int port, std::string password): port_(port), password_(password) {}

Server::~Server() {}

/**
 *@brief to start IRC Server
*/
void Server::start() {

	this->setupSocket();
	this->makePoll(master_sd_);

	while (1)
	{
		std::cout << "Waiting on poll()" << std::endl;
		if (poll(pollfds_.data(), pollfds_.size(), TIMEOUT) < 0)
		{
			std::cerr << "poll error" << std::endl;
			break ;
		}
		for (int i = 0; i < pollfds_.size(); i++)
		{
			// nothing event
			if (pollfds_[i].revents == 0)
				continue;

			// not pollin event (SIGINT -> loop発生)
			if (pollfds_[i].revents != POLLIN)
			{
				std::cerr << "error revents " << pollfds_[i].revents << std::endl;
				return ;
			}

			// event fd is server fd
			if (pollfds_[i].fd == master_sd_)
			{
				std::cout << "Listening socket is readable" << std::endl;
				this->allow();
			}
			else // This is not the listening socket, therefore an existing connection must be readable
			{
				std::cout << "Descriptor " << pollfds_[i].fd << " is readable" << std::endl;
				this->chat(pollfds_[i].fd);
			}
		}
	}
}


/**
 * @brief
 * @param fd connected client fd
 */
void Server::chat(int fd)
{
	char buf[MSG_MAX];
	int bytes = 0;

	bzero(&buf, sizeof(buf));

	while (bytes < 1)
	{
		bytes = recv(fd, buf, sizeof(buf), 0);
		if (bytes < 0)
		{
			if (errno != EWOULDBLOCK)
			{
				std::cerr << "recv error" << std::endl;
			}
			return ;
		}
		else if (bytes == 0)
		{
			std::cout << "Connection closed" << std::endl;
			return ;
		}
	}
	std::cout << bytes << " bytes received" << std::endl;

	buf[bytes] = '\0';
	std::cout << "Message from " << fd << std::endl;
	std::cout << "message: " << buf << std::endl;
}

/**
 * @brief to accept connections from clients.
 */
void Server::allow() {
	int connect = -1;

	do
	{
		connect = accept(this->master_sd_, NULL, NULL);
		if (connect < 0)
		{
			// accept fails with EWOULDBLOCK, then we have accepted all of them.
			if (errno != EWOULDBLOCK)
			{
				std::cerr << "accept error" << std::endl;
				close(this->master_sd_);
			}
			break;
		}
		std::cout << "New incoming connection - " << connect << std::endl;
		this->makePoll(connect);

	} while (connect != -1);
}


/**
 * @brief to create polling method corresponding to the num of fds (include server socket fd)
 * @param sockfd An indication of which fd for which PollMethod to create
 *
 */
void Server::makePoll(int sockfd)
{
	struct pollfd pollfd;

	pollfd.fd = sockfd;
	pollfd.events = POLLIN;
	pollfd.revents = 0;

	pollfds_.push_back(pollfd);
}


/**
 * @brief to set up a server socket
 */
void Server::setupSocket() {
	int enable = 1;

	/* server socket create */
	master_sd_ = socket(AF_INET, SOCK_STREAM, 0);
	if (master_sd_ < 0)
	{
		std::cerr << "socket error" << std::endl;
		exit(EXIT_FAILURE);
	}

	/* set socket option to server socket */
	if (setsockopt(master_sd_, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable)) < 0)
	{
		std::cerr << "setsockopt error" << std::endl;
		close(master_sd_);
		exit(EXIT_FAILURE);
	}

	/* Change server socket fd from blocking IO to non-blocking IO*/
	if (fcntl(master_sd_, O_NONBLOCK, &enable))
	{
		std::cerr << "fcntl O_NONBLOCK error" << std::endl;
		close(master_sd_);
		exit(EXIT_FAILURE);
	}

	/* create address for server socket fd */
	struct sockaddr_in addr;
	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(port_);

	/* bind address to server socket fd*/
	if (bind(master_sd_, (struct sockaddr*)&addr, sizeof(addr)) < 0)
	{
		std::cerr << "bind error" << std::endl;
		close(this->master_sd_);
		exit(EXIT_FAILURE);
	}

	/* try to specify maximum of sockets pending connections for the server socket */
	if (listen(this->master_sd_, MAX_SOCKET) < 0)
	{
		std::cerr << "listen error" << std::endl;
		exit(EXIT_FAILURE);
	}
}
