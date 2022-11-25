#include <iostream>
#include <Client.hpp>

int main(int argc, char const *argv[])
{
	std::cout << "Welcome to ft_irc project!!!" << std::endl;
	Client client;
	client.sendInput((char *)argv[1]);
	return 0;
}
