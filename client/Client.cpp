#include <Client.hpp>

Client::Client()
{
}

Client::~Client()
{
}

/**
 * Socket Programing
 */

#include <sys/fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <iostream>
#include <arpa/inet.h>

void Client::sendInput(char *arg) {
	int sockfd;
	struct sockaddr_in client_addr;
	char *dest = "127.0.0.1";

	// std::cout << "Connect to ?: (name of IP address)";
	// std::cin >> dest;

	sockfd = socket(PF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
		std::cerr << "[ERROR] Socket Error" << std::endl;
		exit(1);
	}

	bzero(&client_addr, sizeof(client_addr));
	client_addr.sin_family = PF_INET;
	client_addr.sin_addr.s_addr = inet_addr(dest);
	client_addr.sin_port = htons(8000);
vh	std::cout << "Trying to connect to " << dest << std::endl;
	if (connect(sockfd, (sockaddr *)&client_addr, sizeof(client_addr)) < 0)
	{
		std::cerr << "[ERROR] Socket Error" << std::endl;
		close(sockfd);
		exit(1);
	}

	while (1)
	{
		std::string str;
		getline(std::cin, str);
		int sendSize = send(sockfd, str.c_str(), 1024, 0);
		char buf[1024];
		int revSize = recv(sockfd, buf, 1024, 0);
		std::cout << buf << std::endl;
	}
	close(sockfd);
}
