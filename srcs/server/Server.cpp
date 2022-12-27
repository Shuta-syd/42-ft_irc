#include <Server.hpp>
#include <Command.hpp>

Server::Server() {}

Server::Server(int port, const std::string &password) : port_(port), password_(password) {}

Server::~Server() {}

/**
 *@brief to start IRC Server
 */
void Server::start()
{
	this->signal_setup();
	this->setupServerSocket();
	this->createPoll(master_sd_);

	while (true)
	{
		std::cout << BLU << "-------------Waiting on poll()-------------" << RES << std::endl;
		poll(&(*pollfds_.begin()), pollfds_.size(), TIMEOUT);
		for (size_t i = 0; i < pollfds_.size(); i++)
		{
			// nothing event
			if (pollfds_[i].revents == 0)
				continue;

			// not pollin event
			if (pollfds_[i].revents != POLLIN)
			{
				std::cerr << "error revents " << pollfds_[i].revents << std::endl;
				return;
			}

			// event fd is server fd
			if (pollfds_[i].fd == master_sd_)
			{
				std::cout << "Listening socket is readable" << std::endl;
				this->allow();
			}
			else // This is not the listening socket, therefore an existing connection must be readable
				this->chat(pollfds_[i].fd);
		}
	}
}

/**
 * @brief  for communication between server and client
 * @param fd connected client fd
 */
void Server::chat(int fd)
{
	char message[MSG_MAX] = {0};

	ssize_t bytes = recv(fd, message, sizeof(message), 0);
	if (bytes == 0)
		throw std::exception();

	Client &user = users_[fd];
	std::cout << "-------------Client Message-------------" << std::endl;
	std::cout << "client fd: [" << fd << "]" << std::endl;
	std::cout << "client : " << message << std::endl;
	std::cout << "----------------------------------------" << std::endl;

	size_t i = 0;
	while (find(&message[i], "\r\n") != -1) {
		int len = 0;
		std::string cmd_line;

		while (message[i] != '\r' && message[i] != '\n') {
			i++;
			len++;
		}

		cmd_line.append(&message[i - len], len + 2);
		user.parse(cmd_line);
		this->execute(fd);
		user.clearParsedMessage();
		i += 2;
	}
}

/**
 * @brief command execute func
 */
void Server::execute(int fd)
{
	Client &client = users_[fd];
	const std::string &cmd = client.getCommand();
	const std::vector<std::string> &params = client.getParams();

	if (client.getIsWelcome() == false  && client.getIsConnected() == false && cmd != "NICK" && cmd != "USER" && cmd != "CAP") {
		clearClientInfo(client, pollfds_, users_, mp_nick_to_fd_);
		return ;
	} else if (client.getIsWelcome() == false  && client.getIsConnected() == false && cmd == "NICK") {
		NICK(client, mp_nick_to_fd_, channels_);
		if (client.getIsNick())
			sendWelcomeMessage(client);
		return;
	}

	if (cmd == "CAP")
		CAP(client, pollfds_, users_, mp_nick_to_fd_);
	else if (cmd == "PASS")
		PASS(client, password_);
	else if (cmd == "NICK")
		NICK(client, mp_nick_to_fd_, channels_);
	else if (cmd == "USER")
		USER(client);
	else if (cmd == "JOIN")
		JOIN(client, params, channels_);
	else if (cmd == "TOPIC")
		TOPIC(client, params, channels_);
	else if (cmd == "PING")
		PONG(client, params);
	else if (cmd == "NAMES")
		NAMES(client, params, channels_);
	else if (cmd == "MODE")
		MODE(client, params, channels_);
	else if (cmd == "PRIVMSG")
		PRIVMSG(client, mp_nick_to_fd_, channels_);
	else if (cmd == "QUIT")
		QUIT(client, pollfds_, users_, mp_nick_to_fd_, params);
	else if (cmd == "KICK")
		KICK(client, channels_, params);
	else if (cmd == "INVITE")
		INVITE(client, mp_nick_to_fd_, channels_, users_);
	else if (cmd == "PART")
		PART(client, channels_, params);
	// debugUsers();
}

//--------------Functions related to Socket------------------

/**
 * @brief to accept connections from clients.
 */
void Server::allow() {
	int client_fd = -1;
	do
	{
		client_fd = accept(this->master_sd_, NULL, NULL);
		if (client_fd < 1) { // accept fails with EWOULDBLOCK, then we have accepted all of them.
			if (errno != EWOULDBLOCK)
				throw std::exception();
			else if (client_fd == 0)
				continue;
		}
		else {
			std::cout << "New incoming connection - " << client_fd << std::endl;
			this->createPoll(client_fd);
			setupClient(client_fd);
		}
	} while (client_fd != -1);
}

/**
 * @brief create new user client info
 * @param sockfd client socket descriptor
 */
void Server::setupClient(int sockfd)
{
	const std::string nick = "unknow" + std::to_string(sockfd);
	Client user(sockfd, nick);
	users_[sockfd] = user;
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
}

/**
 * @brief to set up a server socket
 */
void Server::setupServerSocket()
{
	/* server socket create */
	master_sd_ = socket(AF_INET, SOCK_STREAM, 0);

	/* set socket option to server socket */
	int enable = 1;
	setsockopt(master_sd_, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable));
	/* Change server socket fd from blocking IO to non-blocking IO */
	fcntl(master_sd_, O_NONBLOCK, &enable);

	/* create address for server socket fd */
	struct sockaddr_in addr;
	bzero(&addr, sizeof(struct sockaddr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(port_);

	/* bind address to server socket fd*/
	bind(master_sd_, (struct sockaddr *)&addr, sizeof(addr));

	/* try to specify maximum of sockets pending connections for the server socket */
	listen(this->master_sd_, SOMAXCONN);
}

void Server::debugUsers() {
	std::cout<< BLU << "------------poll fd------------" << RES << std::endl;
	for (size_t i = 0; i < pollfds_.size(); i++)
		std::cout << "[" << pollfds_[i].fd << "]" << std::endl;
	std::cout<< BLU << "-------------------------------" << RES << std::endl;

	std::cout << YEL << "------------users------------" << RES << std::endl;
	for (
			std::map<int, Client>::iterator it = users_.begin();
			it != users_.end();
			it++
			)
		std::cout << "[" << it->first << ", " << it->second.getNickname() << "]" << std::endl;
	std::cout << YEL << "-------------------------------" << RES << std::endl;

	std::cout << RED << "------------nick_to_fd------------" << RES << std::endl;
	for (
			std::map<std::string, int>::iterator it = mp_nick_to_fd_.begin();
			it != mp_nick_to_fd_.end();
			it++
			)
		std::cout << "[" << it->first << ", " << it->second << "]" << std::endl;
	std::cout << RED << "-------------------------------" << RES << std::endl;
}
