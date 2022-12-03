#include <Server.hpp>

Server::Server() {}

Server::Server(int port, std::string password): port_(port), password_(password) {}

Server::~Server() {}


/**
 *
 */
void Server::start() {
	int sockfd = socket(PF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
		std::cerr << "socket error: " << __LINE__ << std::endl;
		exit(1);
	}

	// Set server IP address and port information
	struct sockaddr_in serverAddr, clientAddr;
	bzero(&serverAddr, sizeof(serverAddr)); //init by 0
	serverAddr.sin_family = PF_INET; //address family
	serverAddr.sin_port = htons(this->port_); //sin_port's size is uint_16
	serverAddr.sin_addr.s_addr = INADDR_ANY;	// IP 0.0.0.0

	if (bind(sockfd, reinterpret_cast<struct sockaddr *>(&serverAddr), sizeof(serverAddr)) < 0)
	{
		std::cerr << "bind error: " << __LINE__ << std::endl;
		exit(1);
	}

	if (listen(sockfd, BACKLOG) < 0)
	{
		std::cerr << "bind error: " << __LINE__ << std::endl;
		close(sockfd);
		exit(1);
	}

	std::cout << "Waiting for connect... [PORT]: " << port_ << " [PASSWORD]: " << password_ << std::endl;
	while (1)
	{
		std::cout << 1 << std::endl;
		socklen_t addrlen = sizeof(clientAddr);
		int clientSockfd = accept(sockfd, reinterpret_cast<struct sockaddr *>(&clientAddr), &addrlen);
		std::cout << clientSockfd << std::endl;
		if (clientSockfd < 0)
		{
			std::cerr << "accept error: " << __LINE__ << std::endl;
			close(sockfd);
			exit(1);
		}
		std::cout << "Connected: " << clientAddr.sin_addr.s_addr << std::endl;

	while (1)
	{
		char buf[1024];
		int revSize = recv(clientSockfd, buf, 1024, 0);
		std::cout << buf << std::endl;
		if (revSize < 0)
		{
			std::cerr << "recv error: " << __LINE__ << std::endl;
			close(sockfd);
			close(clientSockfd);
			exit(1);
		}
		int sendSize = send(clientSockfd, buf, 1024, 0);
		if (sendSize < -1)
		{
			std::cerr << "send error: " << __LINE__ << std::endl;
			close(sockfd);
			close(clientSockfd);
			exit(1);
		}
	}
	}
}

void Server::startPoll() {
	int sockfd = socket(PF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
		std::cerr << "socket error: " << __LINE__ << std::endl;
		exit(1);
	}
}
