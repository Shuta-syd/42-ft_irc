#include <Server.hpp>

Server::Server() {}

Server::Server(int port, const std::string &password) : port_(port), password_(password) {}

Server::~Server() {}

/**
 *@brief to start IRC Server
 */
void Server::start() {

	this->setupSocket();
	this->createPoll(master_sd_);

	while (1) {
		std::cout << "-------------Waiting on poll()-------------" << std::endl;
		if (poll(&(*pollfds_.begin()), pollfds_.size(), TIMEOUT) < 0) {
			std::cerr << "poll error" << std::endl;
			break;
		}
		for (int i = 0; i < pollfds_.size(); i++) {
			// nothing event
			if (pollfds_[i].revents == 0)
				continue;

			// not pollin event (SIGINT -> loop発生)
			if (pollfds_[i].revents != POLLIN) {
				std::cerr << "error revents " << pollfds_[i].revents << std::endl;
				return;
			}

			// event fd is server fd
			if (pollfds_[i].fd == master_sd_) {
				std::cout << "Listening socket is readable" << std::endl;
				this->allow();
			}
			else // This is not the listening socket, therefore an existing connection must be readable
				this->chat(pollfds_[i].fd);
		}
	}
}

/**
 * @brief to send message to client
 *
 * @param fd client fd
 * @param msg message
 * @param flag send option
 */
void Server::sendMessage(int fd, std::string msg, int flag) {
	send(fd, msg.c_str(), msg.size(), flag);
}

/**
 * @brief  for communication between server and client
 * @param fd connected client fd
 */
void Server::chat(int fd) {
	char buf[MSG_MAX];
	int bytes = 0;

	bzero(&buf, sizeof(buf));

	bytes = recv(fd, buf, sizeof(buf), 0);
	if (bytes < 0) { // exception
		if (errno != EWOULDBLOCK)
			std::cerr << "recv error" << std::endl;
		return;
	}
	else if (bytes == 0) { //quit
		std::cout << "Connection closed" << std::endl;
		return;
	}

	User &user = users_[fd];
	user.addMessage(buf);
	const std::string message = user.getMessage();

	std::cout << "-------------Client Message-------------" << std::endl;
	std::cout << "client fd: [" << fd << "]" << std::endl;
	std::cout << "client : " << message << std::endl;
	std::cout << "----------------------------------------" << std::endl;

	// find CR-LF (end point)
	if (message.find_first_of("\r\n"))
		user.parse();
}

/**
 * Functions related to Socket
 */

/**
 * @brief to accept connections from clients.
 */
void Server::allow() {
	int connect = -1;

	connect = accept(this->master_sd_, NULL, NULL);
	if (connect < 0) {
		// accept fails with EWOULDBLOCK, then we have accepted all of them.
		if (errno != EWOULDBLOCK) {
			std::cerr << "accept error" << std::endl;
			close(this->master_sd_);
		}
	}
	std::cout << "New incoming connection - " << connect << std::endl;
	this->createPoll(connect);
}

/**
 * @brief to create polling method corresponding to the num of fds (include server socket fd)
 * @param sockfd An indication of which fd for which PollMethod to create
 *
 */
void Server::createPoll(int sockfd)
{
	struct pollfd pollfd;

	pollfd.fd = sockfd;
	pollfd.events = POLLIN;
	pollfd.revents = 0;
	pollfds_.push_back(pollfd);

	/* server maintain client info(nick fd etc..) if fd isn't server fd */
	if (sockfd != master_sd_) {
		const std::string nick = "unknow" + std::to_string(sockfd);
		User user(sockfd, nick);
		users_[sockfd] = user;
	}
}

/**
 * @brief to set up a server socket
 */
void Server::setupSocket()
{
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

	/* Change server socket fd from blocking IO to non-blocking IO */
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
	if (bind(master_sd_, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		std::cerr << "bind error" << std::endl;
		close(this->master_sd_);
		exit(EXIT_FAILURE);
	}

	/* try to specify maximum of sockets pending connections for the server socket */
	if (listen(this->master_sd_, BACKLOG) < 0)
	{
		std::cerr << "listen error" << std::endl;
		exit(EXIT_FAILURE);
	}
}
